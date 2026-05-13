import { useState, useRef, useEffect, useCallback } from 'react';
import TurnManager from '@trascendence/shared/TurnManager';
import { createScaledTerritories } from '@trascendence/shared/Territories';
import { FACTIONS, NEUTRAL_TERRITORIES } from '@trascendence/shared/Factions';
import mapPicking from '../assets/map_picking.png';
import { calculateScore } from '@trascendence/shared/Victory';
import { api } from '../api.js';
import AchievementNotification from './AchievementNotification.jsx';
import Chat from './Chat.jsx';
import useGameSocket from '../hooks/useGameSocket.js';
import { checkAchievements } from '@trascendence/shared/Achievements';

const CANVAS_WIDTH = 1100;
const CANVAS_HEIGHT = 700;
const TERRITORIES = createScaledTerritories(CANVAS_WIDTH, CANVAS_HEIGHT);

// ========== INITIALIZATION HELPERS ==========
function initializeTerritoryOwners() {
	const owners = {};
	Object.entries(FACTIONS).forEach(([factionId, faction]) => {
		faction.territories.forEach((territoryId) => {
			owners[territoryId] = factionId;
		});
	});
	NEUTRAL_TERRITORIES.forEach((territoryId) => {
		owners[territoryId] = null;
	});
	return owners;
}

// ========== INITIAL TROOP COUNT: REGIONAL CAPITALS = 3, OTHERS = 2 ==========
function initializeTroopCount() {
	const counts = {};
	Object.keys(TERRITORIES).forEach((territoryId) => {
		const isRegionalCapital = TERRITORIES[territoryId].isRegCapital;
		counts[territoryId] = isRegionalCapital ? 3 : 2;
	});
	return counts;
}

// export default function GameBoard({ players }) {
export default function GameBoard({ roomId, playerId }) {
	console.log('GameBoard props:', { roomId, playerId });
	// ========== GAME SETUP ==========
	const MAX_TURNS = 100;

	// ========== CANVAS REFS ==========
	const canvasRef = useRef(null);
	const pickingCanvasRef = useRef(null);
	const territoryCanvasRef = useRef(null);
	const territoryPixelsRef = useRef({});
	// const initializedRef = useRef(false);

	// ========== GAME STATE ==========
	const [currentPlayer, setCurrentPlayer] = useState(null);
	const [phase, setPhase] = useState(null);
	const [turn, setTurn] = useState(0);
	const [winner, setWinner] = useState(null);

	// ========== UI STATE ==========
	const [selectedTerritory, setSelectedTerritory] = useState(null);
	const [hoveredTerritory, setHoveredTerritory] = useState(null);
	const [battleReport, setBattleReport] = useState(null);

	// ========== ACHIEVEMENT STATE ==========
	const [visibleAchievements, setVisibleAchievements] = useState([]);
	const [playerUnlockedAchievements, setPlayerUnlockedAchievements] = useState({});

	// ========== TERRITORY STATE ==========
	const [territoryOwners, setTerritoryOwners] = useState(initializeTerritoryOwners);
	const [troopCount, setTroopCount] = useState(initializeTroopCount);

	// ========== REINFORCE PHASE ==========
	const [reinforcementsLeft, setReinforcementsLeft] = useState(0);

	// ========== ATTACK PHASE ==========
	const [attackFrom, setAttackFrom] = useState(null);
	const [attackTo, setAttackTo] = useState(null);
	const [attackTroops, setAttackTroops] = useState(1);

	// ========== FORTIFY PHASE ==========
	const [fortifyFrom, setFortifyFrom] = useState(null);
	const [fortifyTo, setFortifyTo] = useState(null);
	const [fortifyTroops, setFortifyTroops] = useState(1);

	// ========== PLAYER STATS STATE ==========
	const [playerStats, setPlayerStats] = useState({});

	// ========== CHAT STATE ==========
	const [chatMessages, setChatMessages] = useState([]);

	const applyState = useCallback((state) => {
		setCurrentPlayer(state.currentPlayer);
		setPhase(state.phase);
		setTurn(state.turn);
		setWinner(state.winner);
		setTerritoryOwners(state.territoryOwners);
		setTroopCount(state.troopCount);
		setReinforcementsLeft(state.reinforcementsLeft);
		if (state.playerStats) {
			setPlayerStats(state.playerStats);
		}
	}, []);

	const handleChat = useCallback((msg) => {
		setChatMessages((prev) => [...prev, msg]);
	}, []);

	// ========== INITIAL SNAPSHOT (one-shot before WS pushes take over) ==========
	useEffect(() => {
		if (!roomId) return;
		api.getState(roomId).then((res) => {
			if (res.ok) applyState(res.state);
		});
	}, [roomId, applyState]);

	// ========== REAL-TIME (WebSocket) ==========
	const { status: wsStatus, sendChat } = useGameSocket({
		roomId,
		playerId,
		onState: applyState,
		onChat: handleChat,
	});

	// ========== ACHIEVEMENT CHECKING ==========
	useEffect(() => {
		if (!playerStats || Object.keys(playerStats).length === 0) return;

		Object.entries(playerStats).forEach(([playerId, playerStat]) => {
			const playerUnlockedSet = playerUnlockedAchievements[playerId] || new Set();
			const newAchievements = checkAchievements(
				playerStat,
				territoryOwners,
				Array.from(playerUnlockedSet)
			);

			newAchievements.forEach((achievementId) => {
				setVisibleAchievements((prev) => [...prev, { id: achievementId, playerId }]);
				setPlayerUnlockedAchievements((prev) => ({
					...prev,
					[playerId]: new Set([...playerUnlockedSet, achievementId]),
				}));
			});
		});
	}, [territoryOwners, playerStats, playerUnlockedAchievements]);

	function handleAchievementDismiss(achievementId) {
		setVisibleAchievements((prev) => prev.filter((item) => item.id !== achievementId));
	}

	// ========== CANVAS SETUP ==========
	useEffect(() => {
		const pickingCanvas = pickingCanvasRef.current;
		const pCtx = pickingCanvas.getContext('2d', { willReadFrequently: true });
		const img = new Image();
		img.src = mapPicking;

		// ========== PIXEL DATA EXTRACTION & CACHING ==========
		img.onload = () => {
			// Draw color circles on picking canvas
			Object.entries(TERRITORIES).forEach(([, territory]) => {
				pCtx.beginPath();
				pCtx.arc(territory.cx, territory.cy, 15, 0, Math.PI * 2);
				pCtx.fillStyle = territory.colorKey;
				pCtx.fill();
			});

			// Draw the picking image on top
			pCtx.drawImage(img, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);

			// Process pixel data and cache it
			const imageData = pCtx.getImageData(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);
			const data = imageData.data;

			const colorMap = {};
			Object.entries(TERRITORIES).forEach(([id, t]) => {
				colorMap[t.colorKey] = id;
				territoryPixelsRef.current[id] = [];
			});

			for (let i = 0; i < data.length; i += 4) {
				const hex =
					'#' +
					[data[i], data[i + 1], data[i + 2]].map((c) => c.toString(16).padStart(2, '0')).join('');
				const id = colorMap[hex];
				if (id) {
					territoryPixelsRef.current[id].push([i / 4]);
				}
			}

			// ========== TERRITORY FILL CACHE ==========
			const terrCanvas = document.createElement('canvas');
			terrCanvas.width = CANVAS_WIDTH;
			terrCanvas.height = CANVAS_HEIGHT;
			const tCtx = terrCanvas.getContext('2d');
			territoryCanvasRef.current = terrCanvas;

			// Fill provinces with initial faction colors
			Object.entries(TERRITORIES).forEach(([id]) => {
				let factionColor;
				if (id === 'mountains') {
					factionColor = '#000000'; // Black for mountains
				} else {
					const factionId = territoryOwners[id];
					factionColor =
						factionId === 'neutral' ? '#888888' : FACTIONS[factionId]?.color ?? '#888888';
				}

				const pixels = territoryPixelsRef.current[id];

				if (pixels && pixels.length > 0) {
					pixels.forEach(([pixelIndex]) => {
						const x = pixelIndex % CANVAS_WIDTH;
						const y = Math.floor(pixelIndex / CANVAS_WIDTH);
						tCtx.fillStyle = factionColor;
						tCtx.fillRect(x, y, 1, 1);
					});
				}
			});
		};
	}, [territoryOwners]);

	// ========== FILL PROVINCES CACHE ==========
	useEffect(() => {
		if (!territoryCanvasRef.current) return;

		const tCtx = territoryCanvasRef.current.getContext('2d');
		tCtx.clearRect(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);

		// Refill provinces with updated faction colors when ownership changes
		Object.entries(TERRITORIES).forEach(([id]) => {
			let factionColor;
			if (id === 'mountains') {
				factionColor = '#000000'; // Black for mountains
			} else {
				const factionId = territoryOwners[id];
				factionColor =
					factionId === 'neutral' ? '#888888' : FACTIONS[factionId]?.color ?? '#888888';
			}

			const pixels = territoryPixelsRef.current[id];

			if (pixels && pixels.length > 0) {
				pixels.forEach(([pixelIndex]) => {
					const x = pixelIndex % CANVAS_WIDTH;
					const y = Math.floor(pixelIndex / CANVAS_WIDTH);
					tCtx.fillStyle = factionColor;
					tCtx.fillRect(x, y, 1, 1);
				});
			}
		});
	}, [territoryOwners]);

	// ========== MAIN DRAWING EFFECT ==========
	useEffect(() => {
		const canvas = canvasRef.current;
		const ctx = canvas.getContext('2d', { willReadFrequently: true });

		// ========== WATER BACKGROUND ==========
		ctx.fillStyle = '#1A3A52';
		ctx.fillRect(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);

		// Draw cached territory fills (includes mountains in black)
		if (territoryCanvasRef.current) {
			ctx.drawImage(territoryCanvasRef.current, 0, 0);
		}

		// Draw territory borders first (so they appear underneath)
		Object.entries(TERRITORIES).forEach(([, territory]) => {
			territory.neighbors.forEach((neighborId) => {
				const neighbor = TERRITORIES[neighborId];
				if (!neighbor) return;

				ctx.beginPath();
				ctx.moveTo(territory.cx, territory.cy);
				ctx.lineTo(neighbor.cx, neighbor.cy);
				ctx.strokeStyle = 'rgba(0,0,0,1)';
				ctx.lineWidth = 1;
				ctx.stroke();
			});
		});

		// Draw halo for hovered territory
		if (hoveredTerritory && hoveredTerritory !== 'mountains') {
			const territory = TERRITORIES[hoveredTerritory];
			const pixels = territoryPixelsRef.current[hoveredTerritory];
			if (territory && pixels) {
				pixels.forEach((pixelIndex) => {
					const x = pixelIndex % CANVAS_WIDTH;
					const y = Math.floor(pixelIndex / CANVAS_WIDTH);
					ctx.fillStyle = 'rgba(255, 255, 255, 0.5)';
					ctx.fillRect(x, y, 1, 1);
				});
			}
		}

		// Highlight selected territories
		const highlighted = [attackFrom, attackTo, fortifyFrom, fortifyTo].filter(Boolean);
		highlighted.forEach((territoryId) => {
			const territory = TERRITORIES[territoryId];
			const pixels = territoryPixelsRef.current[territoryId];
			if (!territory || !pixels) return;

			pixels.forEach((pixelIndex) => {
				const x = pixelIndex % CANVAS_WIDTH;
				const y = Math.floor(pixelIndex / CANVAS_WIDTH);
				ctx.fillStyle = 'rgba(255, 255, 255, 0.3)';
				ctx.fillRect(x, y, 1, 1);
			});

			ctx.beginPath();
			ctx.arc(territory.cx, territory.cy, 18, 0, Math.PI * 2);
			ctx.fillStyle = 'rgba(255, 255, 0, 0.3)';
			ctx.fill();
			ctx.strokeStyle = 'yellow';
			ctx.lineWidth = 3;
			ctx.stroke();
		});

		// Draw territories on canvas (circles + names + troops) - rendered last so they appear on top
		Object.entries(TERRITORIES).forEach(([id, territory]) => {
			// Skip mountains - rendered in black as part of fills
			if (id === 'mountains') return;

			const factionId = territoryOwners[id];
			const factionColor =
				factionId === 'neutral' ? '#888888' : FACTIONS[factionId]?.color ?? '#888888';
			ctx.fillStyle = factionColor;
			ctx.beginPath();
			ctx.arc(territory.cx, territory.cy, 10, 0, Math.PI * 2);
			ctx.fill();
			ctx.strokeStyle = 'black';
			ctx.stroke();

			// Draw troop count inside the circle
			ctx.fillStyle = 'black';
			ctx.font = 'bold 12px Arial';
			ctx.textAlign = 'center';
			ctx.textBaseline = 'middle';
			ctx.fillText(troopCount[id], territory.cx, territory.cy);

			// Draw territory name below
			ctx.fillStyle = 'black';
			ctx.font = '11px Arial';
			ctx.textAlign = 'center';
			ctx.fillText(territory.name, territory.cx, territory.cy + 20);
		});
	}, [territoryOwners, troopCount, attackFrom, attackTo, fortifyFrom, fortifyTo, hoveredTerritory]);

	// ========== TURN MANAGEMENT ==========
	async function handleNextTurn() {
		if (winner) return;
	if (!currentPlayer || currentPlayer.id !== playerId) return;

	setAttackFrom(null);
		setAttackTo(null);
		setFortifyFrom(null);
		setFortifyTo(null);

		const res = await api.nextTurn(roomId);
		if (res.ok) applyState(res.state);
	}

	// ========== REINFORCE ACTIONS ==========
	async function handleReinforce(territoryId) {
		const res = await api.reinforce(roomId, territoryId);
		if (res.ok) applyState(res.state);
	}

	// ========== FORTIFY ACTIONS ==========
	async function handleFortify(destinationId) {
		const res = await api.fortify(roomId, fortifyFrom, destinationId, fortifyTroops);
		if (res.ok) {
			applyState(res.state);
			setFortifyFrom(null);
			setFortifyTo(null);
			setFortifyTroops(1);
		}
	}

	// ========== COMBAT ACTIONS ==========
	async function handleAttack() {
		const res = await api.attack(roomId, attackFrom, attackTo, attackTroops);
		if (res.ok) {
			applyState(res.state);
			setBattleReport(res.battleReport);
			setAttackFrom(null);
			setAttackTo(null);
		}
	}

	// ========== CANVAS INTERACTION ==========
	function getClickedTerritory(e) {
		const canvas = canvasRef.current;
		const rect = canvas.getBoundingClientRect();
		const x = e.clientX - rect.left;
		const y = e.clientY - rect.top;

		const pickingCanvas = pickingCanvasRef.current;
		const pCtx = pickingCanvas.getContext('2d', { willReadFrequently: true });
		const pixel = pCtx.getImageData(x, y, 1, 1).data;
		const colorKey =
			'#' + [pixel[0], pixel[1], pixel[2]].map((c) => c.toString(16).padStart(2, '0')).join('');

		const found = Object.entries(TERRITORIES).find(
			([id, t]) => t.colorKey === colorKey && id !== 'mountains'
		);
		return found ? found[0] : null;
	}

	// ========== MOUSE HANDLERS ==========
	function handleCanvasMouseMove(e) {
		if (!currentPlayer || currentPlayer.id !== playerId) return;
		const territoryId = getClickedTerritory(e);
		setHoveredTerritory(territoryId);
	}

	function handleCanvasMouseLeave() {
		if (!currentPlayer || currentPlayer.id !== playerId) return;
		setHoveredTerritory(null);
	}

	// ========== CLICK HANDLERS ==========
	function handleCanvasClick(e) {
		if (!currentPlayer || currentPlayer.id !== playerId) return;
		const clickedId = getClickedTerritory(e);
		if (!clickedId) {
			// Clicked outside a territory, clear selection
			setSelectedTerritory(null);
			setFortifyFrom(null);
			setAttackFrom(null);
			setFortifyTo(null);
			setAttackTo(null);
			return;
		}

		const clickedTerritory = TERRITORIES[clickedId];

		// If clicking the same territory that's selected, deselect it
		if (selectedTerritory && selectedTerritory.id === clickedId) {
			setSelectedTerritory(null);
			return;
		}

		// Select the new territory
		setSelectedTerritory({ id: clickedId, ...clickedTerritory });

		// Game logic for REINFORCE phase
		if (phase === TurnManager.PHASES.REINFORCE) {
			if (territoryOwners[clickedId] !== currentPlayer.faction) return;
			if (reinforcementsLeft <= 0) return;
			handleReinforce(clickedId);
			return;
		}

		// Game logic for ATTACK phase
		if (phase === TurnManager.PHASES.ATTACK) {
			// 1er clic en fase ATTACK: selecciona el territorio de origen
			if (!attackFrom) {
				if (territoryOwners[clickedId] !== currentPlayer.faction) {
					console.log('No puedes atacar desde un territorio que no posees:', clickedTerritory.name);
					return;
				}
				if (troopCount[clickedId] <= 1) {
					console.log(
						'No puedes atacar desde un territorio con 1 tropa o menos:',
						clickedTerritory.name
					);
					return;
				}
				setAttackFrom(clickedId);
				console.log('Seleccionado para atacar desde:', clickedTerritory.name);
				return;
			}

			// 2do clic en fase ATTACK: selecciona el territorio de destino
			if (clickedId === attackFrom) {
				console.log('Deseleccionando origen de ataque:', clickedTerritory.name);
				setAttackFrom(null);
				setAttackTo(null);
				return;
			}
			if (clickedId === attackTo) {
				console.log('Deseleccionando destino de ataque:', clickedTerritory.name);
				setAttackTo(null);
				return;
			}

			if (territoryOwners[clickedId] === currentPlayer.faction) {
				console.log('No puedes atacar a un territorio que ya posees:', clickedTerritory.name);
				return;
			}
			if (!TERRITORIES[attackFrom].neighbors.includes(clickedId)) {
				console.log('Solo puedes atacar territorios vecinos:', clickedTerritory.name);
				return;
			}

			setAttackTo(clickedId);
			console.log('Seleccionado para atacar a:', clickedTerritory.name);
			setAttackTroops(1); // Reset slider to minimum on new target selection
			return;
		}

		// Game logic for FORTIFY phase
		if (phase === TurnManager.PHASES.FORTIFY) {
			// 1er clic en fase FORTIFY: selecciona el territorio de origen
			if (!fortifyFrom) {
				if (territoryOwners[clickedId] !== currentPlayer.faction) return;
				if (troopCount[clickedId] <= 1) return;
				setFortifyFrom(clickedId);
				console.log('Fortificación: origen seleccionado -', clickedTerritory.name);
				return;
			}

			// 2do clic en fase FORTIFY: selecciona el territorio de destino (SIN mover tropas aún)
			if (clickedId === fortifyFrom) {
				setFortifyFrom(null);
				setFortifyTo(null);
				console.log('Fortificación: origen deseleccionado');
				return;
			}
			if (clickedId === fortifyTo) {
				setFortifyTo(null);
				console.log('Fortificación: destino deseleccionado');
				return;
			}
			if (territoryOwners[clickedId] !== currentPlayer.faction) return;
			if (!TERRITORIES[fortifyFrom].neighbors.includes(clickedId)) return;

			// Solo establecer el destino, dejar que el botón "Mover" haga el cambio
			setFortifyTo(clickedId);
			console.log('Fortificación: destino seleccionado -', clickedTerritory.name);
		}
	}

	return (
		<div
			style={{
				position: 'relative',
				width: '100%',
				minHeight: '100vh',
				margin: '0',
				padding: '20px 0',
				backgroundColor: '#0d0d0d',
			}}
		>
			{/* Achievement Notifications */}
			{visibleAchievements.map((achievement) => (
				<AchievementNotification
					key={`${achievement.playerId}-${achievement.id}`}
					achievementId={achievement.id}
					onDismiss={() => handleAchievementDismiss(achievement.id)}
				/>
			))}

			{/* Chat panel (fixed bottom-right) */}
			<div
				style={{
					position: 'fixed',
					bottom: '20px',
					right: '20px',
					width: '280px',
					zIndex: 20,
				}}
			>
				<Chat
					messages={chatMessages}
					onSend={sendChat}
					status={wsStatus}
					playerId={playerId}
				/>
			</div>


			<h1
				style={{
					textAlign: 'center',
					margin: '10px 0',
					color: '#FF6B6B',
					fontFamily: 'monospace',
					fontSize: '32px',
					letterSpacing: '2px',
					textShadow: '0 0 10px rgba(255, 107, 107, 0.3)',
				}}
			>
				GREAT RISK
			</h1>

			{/* Main container: 80% map, 20% UI */}
			<div
				style={{
					width: `${CANVAS_WIDTH}px`,
					margin: '0 auto',
					display: 'flex',
					flexDirection: 'column',
					minHeight: '80vh',
				}}
			>
				{/* Canvas area - 80% */}
				<div style={{ position: 'relative', display: 'inline-block', flex: '0 0 80%' }}>
					<canvas
						ref={canvasRef}
						width={CANVAS_WIDTH}
						height={CANVAS_HEIGHT}
						style={{
							border: '3px solid #FF6B6B',
							display: 'block',
							width: '100%',
							height: '100%',
							boxShadow: '0 0 20px rgba(255, 107, 107, 0.3)',
						}}
						onClick={handleCanvasClick}
						onMouseMove={handleCanvasMouseMove}
						onMouseLeave={handleCanvasMouseLeave}
					/>
					<canvas
						ref={pickingCanvasRef}
						width={CANVAS_WIDTH}
						height={CANVAS_HEIGHT}
						style={{
							position: 'absolute',
							top: 0,
							left: 0,
							display: 'none',
							width: '100%',
							height: '100%',
							zIndex: -1,
							opacity: 0.9,
						}}
					/>

					{/* Territory info box (bottom-left of canvas) */}
					{(selectedTerritory || hoveredTerritory) && (
						<div
							style={{
								position: 'absolute',
								bottom: '20px',
								left: '20px',
								backgroundColor: 'rgba(0, 0, 0, 0.9)',
								color: '#E0E0E0',
								padding: '12px',
								borderRadius: '6px',
								maxWidth: '250px',
								fontSize: '12px',
								fontFamily: 'monospace',
								zIndex: 10,
								border: '2px solid #6496FF',
								boxShadow: '0 0 15px rgba(100, 150, 255, 0.3)',
							}}
						>
							{(() => {
								const territory =
									selectedTerritory || (hoveredTerritory && TERRITORIES[hoveredTerritory]);
								const territoryId = selectedTerritory?.id || hoveredTerritory;
								if (!territory) return null;
								return (
									<>
										<div style={{ fontWeight: 'bold', color: '#6496FF', marginBottom: '6px' }}>
											{territory.name}
										</div>
										<div style={{ fontSize: '11px' }}>Capital: {territory.capital}</div>
										<div style={{ fontSize: '11px' }}>
											Propietario:{' '}
											{territoryOwners[territoryId]
												? FACTIONS[territoryOwners[territoryId]]?.name || 'Desconocido'
												: 'Neutral'}
										</div>
										<div style={{ fontSize: '11px', color: '#FFD700', marginTop: '4px' }}>
											Tropas: {troopCount[territoryId]}
										</div>
									</>
								);
							})()}
						</div>
					)}
				</div>

				{/* UI Bottom section - 20% - Three-way layout */}
				<div
					style={{
						flex: '0 0 20%',
						backgroundColor: '#0f0f0f',
						borderTop: '3px solid #FF6B6B',
						padding: '12px',
						display: 'flex',
						justifyContent: 'space-between',
						alignItems: 'center',
						gap: '12px',
						fontFamily: 'monospace',
						boxShadow: '0 -5px 15px rgba(255, 107, 107, 0.2)',
					}}
				>
					{/* LEFT: Player data */}
					<div style={{ color: '#E0E0E0', fontSize: '13px', flex: 1 }}>
						{(() => {
							const myFaction = playerStats?.[playerId]?.faction;
							const isMyTurn = currentPlayer?.id === playerId;
							return (
								<>
									<div>
										Facción:{' '}
										<span style={{ color: '#FFD700' }}>
											{myFaction ? FACTIONS[myFaction]?.name : '—'}
										</span>
									</div>
									<div style={{ marginTop: '4px' }}>
										Fase: <span style={{ color: '#FF6B6B', fontWeight: 'bold' }}>{phase}</span>
									</div>
									{currentPlayer && (
										<div
											style={{
												marginTop: '6px',
												fontSize: '11px',
												color: isMyTurn ? '#4CAF50' : '#888',
											}}
										>
											Turno:{' '}
											<span style={{ color: isMyTurn ? '#4CAF50' : '#bbb' }}>
												{isMyTurn
													? 'Tu turno'
													: `${currentPlayer.name} — ${FACTIONS[currentPlayer.faction]?.name || '?'}`}
											</span>
										</div>
									)}
									{isMyTurn && phase === TurnManager.PHASES.REINFORCE && (
										<div style={{ marginTop: '4px', color: '#4CAF50', fontWeight: 'bold' }}>
											Refuerzos: {reinforcementsLeft}
										</div>
									)}
								</>
							);
						})()}
					</div>

					{/* CENTER: Turn info and button */}
					<div
						style={{
							display: 'flex',
							flexDirection: 'column',
							alignItems: 'center',
							gap: '8px',
							flex: 1,
						}}
					>
						<div style={{ color: 'white', fontSize: '13px', textAlign: 'center' }}>
							<div>Turno</div>
							<div style={{ fontSize: '16px', fontWeight: 'bold', color: '#FFD700' }}>
								{turn} / {MAX_TURNS}
							</div>
						</div>
						<button
							onClick={handleNextTurn}
							style={{
								padding: '8px 16px',
								fontSize: '12px',
								backgroundColor: '#FF6B6B',
								color: 'white',
								border: 'none',
								borderRadius: '4px',
								cursor: 'pointer',
								fontWeight: 'bold',
								minWidth: '140px',
								transition: 'all 0.2s ease',
								boxShadow: '0 0 10px rgba(255, 107, 107, 0.3)',
							}}
							onMouseEnter={(e) => {
								e.target.style.backgroundColor = '#FF5252';
								e.target.style.boxShadow = '0 0 20px rgba(255, 107, 107, 0.6)';
							}}
							onMouseLeave={(e) => {
								e.target.style.backgroundColor = '#FF6B6B';
								e.target.style.boxShadow = '0 0 10px rgba(255, 107, 107, 0.3)';
							}}
						>
							Siguiente turno
						</button>
					</div>

					{/* RIGHT: Action controls (Fortify/Attack) */}
					<div style={{ flex: 1, minHeight: '60px' }}>
						{phase === TurnManager.PHASES.FORTIFY && fortifyFrom && fortifyTo && (
							<div style={{ color: 'white', fontSize: '12px' }}>
								<div style={{ fontWeight: 'bold', marginBottom: '6px' }}>
									{TERRITORIES[fortifyFrom].name} '&gt;' {TERRITORIES[fortifyTo].name}
								</div>
								<input
									type="range"
									min={1}
									max={troopCount[fortifyFrom] - 1}
									value={fortifyTroops}
									onChange={(e) => setFortifyTroops(Number(e.target.value))}
									style={{ width: '100%', marginBottom: '4px' }}
								/>
								<div style={{ marginBottom: '6px', fontSize: '11px' }}>Tropas: {fortifyTroops}</div>
								<button
									onClick={() => handleFortify(fortifyTo)}
									disabled={currentPlayer?.id !== playerId}
									style={{
										width: '100%',
										padding: '4px',
										marginBottom: '3px',
										backgroundColor: '#4CAF50',
										color: 'white',
										border: 'none',
										borderRadius: '3px',
										cursor: 'pointer',
										fontSize: '11px',
										fontWeight: 'bold',
										transition: 'all 0.2s ease',
									}}
									onMouseEnter={(e) => {
										e.target.style.backgroundColor = '#45a049';
										e.target.style.boxShadow = '0 0 10px rgba(76, 175, 80, 0.4)';
									}}
									onMouseLeave={(e) => {
										e.target.style.backgroundColor = '#4CAF50';
										e.target.style.boxShadow = 'none';
									}}
								>
									Mover
								</button>
								<button
									onClick={() => {
										setFortifyFrom(null);
										setFortifyTo(null);
										setFortifyTroops(1);
									}}
									style={{
										width: '100%',
										padding: '4px',
										backgroundColor: '#FF6B6B',
										color: 'white',
										border: 'none',
										borderRadius: '3px',
										cursor: 'pointer',
										fontSize: '11px',
										fontWeight: 'bold',
										transition: 'all 0.2s ease',
									}}
									onMouseEnter={(e) => {
										e.target.style.backgroundColor = '#FF5252';
										e.target.style.boxShadow = '0 0 10px rgba(255, 107, 107, 0.4)';
									}}
									onMouseLeave={(e) => {
										e.target.style.backgroundColor = '#FF6B6B';
										e.target.style.boxShadow = 'none';
									}}
								>
									Cancelar
								</button>
							</div>
						)}

						{phase === TurnManager.PHASES.ATTACK && attackFrom && attackTo && (
							<div style={{ color: 'white', fontSize: '12px' }}>
								<div style={{ fontWeight: 'bold', marginBottom: '6px' }}>
									{TERRITORIES[attackFrom].name} → {TERRITORIES[attackTo].name}
								</div>
								<input
									type="range"
									min={1}
									max={Math.min(3, troopCount[attackFrom] - 1)}
									value={attackTroops}
									onChange={(e) => setAttackTroops(Number(e.target.value))}
									style={{ width: '100%', marginBottom: '4px' }}
								/>
								<div style={{ marginBottom: '6px', fontSize: '11px' }}>Tropas: {attackTroops}</div>
								<button
									onClick={handleAttack}
									disabled={currentPlayer?.id !== playerId}
									style={{
										width: '100%',
										padding: '4px',
										marginBottom: '3px',
										backgroundColor: '#FF6B6B',
										color: 'white',
										border: 'none',
										borderRadius: '3px',
										fontSize: '11px',
										fontWeight: 'bold',
										transition: 'all 0.2s ease',
										opacity: currentPlayer?.id !== playerId ? 0.5 : 1,
										cursor: currentPlayer?.id !== playerId ? 'not-allowed' : 'pointer',
									}}
									onMouseEnter={(e) => {
										e.target.style.backgroundColor = '#FF5252';
										e.target.style.boxShadow = '0 0 10px rgba(255, 107, 107, 0.4)';
									}}
									onMouseLeave={(e) => {
										e.target.style.backgroundColor = '#FF6B6B';
										e.target.style.boxShadow = 'none';
									}}
								>
									¡Atacar!
								</button>
								<button
									onClick={() => {
										setAttackFrom(null);
										setAttackTo(null);
										setAttackTroops(1);
									}}
									style={{
										width: '100%',
										padding: '4px',
										backgroundColor: '#FF6B6B',
										color: 'white',
										border: 'none',
										borderRadius: '3px',
										cursor: 'pointer',
										fontSize: '11px',
										fontWeight: 'bold',
										transition: 'all 0.2s ease',
									}}
									onMouseEnter={(e) => {
										e.target.style.backgroundColor = '#FF5252';
										e.target.style.boxShadow = '0 0 10px rgba(255, 107, 107, 0.4)';
									}}
									onMouseLeave={(e) => {
										e.target.style.backgroundColor = '#FF6B6B';
										e.target.style.boxShadow = 'none';
									}}
								>
									Cancelar
								</button>
							</div>
						)}
					</div>
				</div>
			</div>

			{winner && (
				<div
					style={{
						position: 'fixed',
						top: '50%',
						left: '50%',
						transform: 'translate(-50%, -50%)',
						backgroundColor: 'rgba(0,0,0,0.95)',
						color: 'white',
						padding: '30px',
						borderRadius: '10px',
						textAlign: 'center',
						zIndex: 30,
						fontFamily: 'monospace',
						border: '3px solid #FF6B6B',
						boxShadow: '0 0 30px rgba(255, 107, 107, 0.5)',
					}}
				>
					<h2 style={{ color: '#FF6B6B', marginTop: 0, marginBottom: '16px' }}>
						¡{FACTIONS[winner.factionId].name} gana!
					</h2>
					<p style={{ color: '#E0E0E0', marginBottom: '20px' }}>
						{winner.reason === 'capitals'
							? 'Ha conquistado todas las capitales enemigas'
							: `Victoria por puntos — ${calculateScore(winner.factionId, territoryOwners)} pts`}
					</p>
					<button
						onClick={() => window.location.reload()}
						style={{
							padding: '10px 20px',
							fontSize: '14px',
							backgroundColor: '#4CAF50',
							color: 'white',
							border: 'none',
							borderRadius: '4px',
							cursor: 'pointer',
							fontWeight: 'bold',
							transition: 'all 0.2s ease',
						}}
						onMouseEnter={(e) => {
							e.target.style.backgroundColor = '#45a049';
							e.target.style.boxShadow = '0 0 15px rgba(76, 175, 80, 0.5)';
						}}
						onMouseLeave={(e) => {
							e.target.style.backgroundColor = '#4CAF50';
							e.target.style.boxShadow = 'none';
						}}
					>
						Nueva partida
					</button>
				</div>
			)}

			{battleReport && (
				<div
					style={{
						position: 'fixed',
						top: '50%',
						left: '50%',
						transform: 'translate(-50%, -50%)',
						backgroundColor: 'rgba(0,0,0,0.95)',
						color: 'white',
						padding: '24px',
						borderRadius: '10px',
						textAlign: 'center',
						zIndex: 25,
						fontFamily: 'monospace',
						border: '2px solid #FF6B6B',
						maxWidth: '400px',
						boxShadow: '0 0 20px rgba(255, 107, 107, 0.5)',
					}}
				>
					<h2 style={{ color: '#FF6B6B', marginTop: 0, marginBottom: '16px' }}>Battle Report</h2>

					<div
						style={{
							backgroundColor: 'rgba(255, 107, 107, 0.1)',
							padding: '12px',
							borderRadius: '6px',
							marginBottom: '12px',
						}}
					>
						<div style={{ fontSize: '14px', marginBottom: '8px' }}>
							<strong>{battleReport.attackFrom}</strong> <span style={{ color: '#FFD700' }}>→</span>{' '}
							<strong>{battleReport.attackTo}</strong>
						</div>
					</div>

					<div
						style={{
							display: 'grid',
							gridTemplateColumns: '1fr 1fr',
							gap: '12px',
							marginBottom: '16px',
						}}
					>
						{/* Attacker Column */}
						<div
							style={{
								backgroundColor: 'rgba(100, 150, 255, 0.2)',
								padding: '12px',
								borderRadius: '6px',
								borderLeft: '3px solid #6496FF',
							}}
						>
							<div style={{ fontSize: '12px', color: '#6496FF', marginBottom: '8px' }}>
								ATTACKER
							</div>
							<div style={{ fontSize: '14px', marginBottom: '6px' }}>
								Troops: <strong>{battleReport.attackerTroops}</strong>
							</div>
							<div style={{ fontSize: '11px', color: '#CCC' }}>
								Dice: {battleReport.attackDice.join(', ')}
							</div>
						</div>

						{/* Defender Column */}
						<div
							style={{
								backgroundColor: 'rgba(255, 107, 107, 0.2)',
								padding: '12px',
								borderRadius: '6px',
								borderLeft: '3px solid #FF6B6B',
							}}
						>
							<div style={{ fontSize: '12px', color: '#FF6B6B', marginBottom: '8px' }}>
								DEFENDER
							</div>
							<div style={{ fontSize: '14px', marginBottom: '6px' }}>
								Troops: <strong>{battleReport.defenderTroops}</strong>
							</div>
							<div style={{ fontSize: '11px', color: '#CCC' }}>
								Dice: {battleReport.defenseDice.join(', ')}
							</div>
						</div>
					</div>

					{/* Reinforcement Bonus Display */}
					{battleReport.troopBonus > 0 && (
						<div
							style={{
								backgroundColor: 'rgba(76, 175, 80, 0.15)',
								padding: '10px',
								borderRadius: '6px',
								marginBottom: '16px',
								borderLeft: '3px solid #4CAF50',
							}}
						>
							<div style={{ fontSize: '12px', color: '#4CAF50', fontWeight: 'bold' }}>
								✦ Reinforcements increased attack in +{battleReport.troopBonus}
							</div>
						</div>
					)}

					{/* Losses */}
					<div
						style={{
							backgroundColor: 'rgba(0, 0, 0, 0.5)',
							padding: '12px',
							borderRadius: '6px',
							marginBottom: '16px',
						}}
					>
						<div style={{ fontSize: '12px', marginBottom: '6px' }}>CASUALTIES</div>
						<div style={{ display: 'grid', gridTemplateColumns: '1fr 1fr', gap: '12px' }}>
							<div>
								<div style={{ color: '#6496FF', fontSize: '13px' }}>Attacker Losses</div>
								<div style={{ fontSize: '16px', fontWeight: 'bold', color: '#FF9999' }}>
									-{battleReport.attackerLosses}
								</div>
							</div>
							<div>
								<div style={{ color: '#FF6B6B', fontSize: '13px' }}>Defender Losses</div>
								<div style={{ fontSize: '16px', fontWeight: 'bold', color: '#FF9999' }}>
									-{battleReport.defenderLosses}
								</div>
							</div>
						</div>
					</div>

					{/* Result */}
					<div
						style={{
							backgroundColor: battleReport.conquered
								? 'rgba(76, 175, 80, 0.2)'
								: 'rgba(255, 107, 107, 0.2)',
							padding: '12px',
							borderRadius: '6px',
							marginBottom: '16px',
							borderLeft: `3px solid ${battleReport.conquered ? '#4CAF50' : '#FF6B6B'}`,
						}}
					>
						<div
							style={{
								fontSize: '14px',
								fontWeight: 'bold',
								color: battleReport.conquered ? '#4CAF50' : '#FF9999',
							}}
						>
							{battleReport.conquered ? '✓ TERRITORY CONQUERED!' : '✗ Attack Failed'}
						</div>
					</div>

					{/* Close Button */}
					<button
						onClick={() => setBattleReport(null)}
						style={{
							width: '100%',
							padding: '10px',
							fontSize: '13px',
							backgroundColor: '#FF6B6B',
							color: 'white',
							border: 'none',
							borderRadius: '4px',
							cursor: 'pointer',
							fontWeight: 'bold',
							transition: 'all 0.2s ease',
						}}
						onMouseEnter={(e) => {
							e.target.style.backgroundColor = '#FF5252';
							e.target.style.boxShadow = '0 0 15px rgba(255, 107, 107, 0.5)';
						}}
						onMouseLeave={(e) => {
							e.target.style.backgroundColor = '#FF6B6B';
							e.target.style.boxShadow = 'none';
						}}
					>
						Continue
					</button>
				</div>
			)}
		</div>
	);
}
