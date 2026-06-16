import { useState, useRef, useEffect, useCallback } from 'react';
import TurnManager from '@trascendence/shared/TurnManager';
import { createScaledTerritories } from '@trascendence/shared/Territories';
import { FACTIONS, NEUTRAL_TERRITORIES } from '@trascendence/shared/Factions';
import mapPicking from '../assets/map_picking.png';
import { calculateScore } from '@trascendence/shared/Victory';
import { api } from '../api.js';
import AchievementNotification from './AchievementNotification.jsx';
import Chat from './Chat.jsx';
import Profile from './Profile.jsx';
import useGameSocket from '../hooks/useGameSocket.js';
import { checkAchievements } from '@trascendence/shared/Achievements';

const CANVAS_WIDTH = 1100;
const CANVAS_HEIGHT = 700;
const TERRITORIES = createScaledTerritories(CANVAS_WIDTH, CANVAS_HEIGHT);

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

function initializeTroopCount() {
	const counts = {};
	Object.keys(TERRITORIES).forEach((territoryId) => {
		const isRegionalCapital = TERRITORIES[territoryId].isRegCapital;
		counts[territoryId] = isRegionalCapital ? 3 : 2;
	});
	return counts;
}

export default function GameBoard({ roomId, playerId, onLogout, onExitGame }) {
	console.log('GameBoard props:', { roomId, playerId });

	const canvasRef = useRef(null);
	const pickingCanvasRef = useRef(null);
	const [mapReady, setMapReady] = useState(false);
	const territoryCanvasRef = useRef(null);
	const territoryPixelsRef = useRef({});

	const [currentPlayer, setCurrentPlayer] = useState(null);
	const [phase, setPhase] = useState(null);
	const [turn, setTurn] = useState(0);
	const [winner, setWinner] = useState(null);

	const [selectedTerritory, setSelectedTerritory] = useState(null);
	const [hoveredTerritory, setHoveredTerritory] = useState(null);
	const [battleReport, setBattleReport] = useState(null);

	const [visibleAchievements, setVisibleAchievements] = useState([]);
	const [playerUnlockedAchievements, setPlayerUnlockedAchievements] = useState({});

	const [territoryOwners, setTerritoryOwners] = useState(initializeTerritoryOwners);
	const [troopCount, setTroopCount] = useState(initializeTroopCount);

	const [reinforcementsLeft, setReinforcementsLeft] = useState(0);

	const [attackFrom, setAttackFrom] = useState(null);
	const [attackTo, setAttackTo] = useState(null);
	const [attackTroops, setAttackTroops] = useState(1);

	const [fortifyFrom, setFortifyFrom] = useState(null);
	const [fortifyTo, setFortifyTo] = useState(null);
	const [fortifyTroops, setFortifyTroops] = useState(1);

	const [playerStats, setPlayerStats] = useState({});
	const [activeFactions, setActiveFactions] = useState([]);
	const [maxTurns, setMaxTurns] = useState(100);

	const [chatMessages, setChatMessages] = useState([]);
	const [showControls, setShowControls] = useState(false);
	const [profileUsername, setProfileUsername] = useState(null);

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
		if (state.activeFactions) {
			setActiveFactions(state.activeFactions);
		}
		if (state.maxTurns) {
			setMaxTurns(state.maxTurns);
		}
	}, []);

	const handleChat = useCallback((msg) => {
		setChatMessages((prev) => [...prev, msg]);
	}, []);

	useEffect(() => {
		if (!roomId) return;
		api.getState(roomId).then((res) => {
			if (res.ok) applyState(res.state);
		});
	}, [roomId, applyState]);

	const { status: wsStatus, sendChat } = useGameSocket({
		roomId,
		playerId,
		onState: applyState,
		onChat: handleChat,
	});

	useEffect(() => {
		if (!playerStats || Object.keys(playerStats).length === 0) return;

		Object.entries(playerStats).forEach(([pid, playerStat]) => {
			const playerUnlockedSet = playerUnlockedAchievements[pid] || new Set();
			const newAchievements = checkAchievements(
				playerStat,
				territoryOwners,
				Array.from(playerUnlockedSet)
			);

			newAchievements.forEach((achievementId) => {
				setVisibleAchievements((prev) => [...prev, { id: achievementId, playerId: pid }]);
				setPlayerUnlockedAchievements((prev) => ({
					...prev,
					[pid]: new Set([...playerUnlockedSet, achievementId]),
				}));
				if (pid === playerId) {
					api.unlockAchievement(playerId, achievementId).catch(() => {});
				}
			});
		});
	}, [territoryOwners, playerStats, playerUnlockedAchievements]);

	function handleAchievementDismiss(achievementId) {
		setVisibleAchievements((prev) => prev.filter((item) => item.id !== achievementId));
	}

	useEffect(() => {
		const pickingCanvas = pickingCanvasRef.current;
		const pCtx = pickingCanvas.getContext('2d', { willReadFrequently: true });
		const img = new Image();
		img.src = mapPicking;

		img.onload = () => {
			Object.entries(TERRITORIES).forEach(([, territory]) => {
				pCtx.beginPath();
				pCtx.arc(territory.cx, territory.cy, 15, 0, Math.PI * 2);
				pCtx.fillStyle = territory.colorKey;
				pCtx.fill();
			});

			pCtx.drawImage(img, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);

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

			const terrCanvas = document.createElement('canvas');
			terrCanvas.width = CANVAS_WIDTH;
			terrCanvas.height = CANVAS_HEIGHT;
			const tCtx = terrCanvas.getContext('2d');
			territoryCanvasRef.current = terrCanvas;
			setMapReady(true);

			Object.entries(TERRITORIES).forEach(([id]) => {
				let factionColor;
				if (id === 'mountains') {
					factionColor = '#000000';
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

	useEffect(() => {
		if (!territoryCanvasRef.current) return;

		const tCtx = territoryCanvasRef.current.getContext('2d');
		tCtx.clearRect(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);

		Object.entries(TERRITORIES).forEach(([id]) => {
			let factionColor;
			if (id === 'mountains') {
				factionColor = '#000000';
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

	useEffect(() => {
		const canvas = canvasRef.current;
		const ctx = canvas.getContext('2d', { willReadFrequently: true });

		ctx.fillStyle = '#1A3A52';
		ctx.fillRect(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);

		if (territoryCanvasRef.current) {
			ctx.drawImage(territoryCanvasRef.current, 0, 0);
		}

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

		Object.entries(TERRITORIES).forEach(([id, territory]) => {
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

			ctx.fillStyle = 'black';
			ctx.font = 'bold 12px Arial';
			ctx.textAlign = 'center';
			ctx.textBaseline = 'middle';
			ctx.fillText(troopCount[id], territory.cx, territory.cy);

			ctx.fillStyle = 'black';
			ctx.font = '11px Arial';
			ctx.textAlign = 'center';
			ctx.fillText(territory.name, territory.cx, territory.cy + 20);
		});
	}, [territoryOwners, troopCount, attackFrom, attackTo, fortifyFrom, fortifyTo, hoveredTerritory, mapReady]);

	async function handleSurrender() {
		if (winner) return;
		if (!window.confirm('Are you sure you want to surrender? You will be eliminated from the game.')) return;
		const res = await api.surrender(roomId, playerId);
		if (res.ok) applyState(res.state);
	}

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

	async function handleReinforce(territoryId) {
		const res = await api.reinforce(roomId, territoryId);
		if (res.ok) applyState(res.state);
	}

	async function handleFortify(destinationId) {
		const res = await api.fortify(roomId, fortifyFrom, destinationId, fortifyTroops);
		if (res.ok) {
			applyState(res.state);
			setFortifyFrom(null);
			setFortifyTo(null);
			setFortifyTroops(1);
		}
	}

	async function handleAttack() {
		const res = await api.attack(roomId, attackFrom, attackTo, attackTroops);
		if (res.ok) {
			applyState(res.state);
			setBattleReport(res.battleReport);
			setAttackFrom(null);
			setAttackTo(null);
		}
	}

	function getTerritoryAt(clientX, clientY) {
		const canvas = canvasRef.current;
		const rect = canvas.getBoundingClientRect();
		const scaleX = canvas.width / rect.width;
		const scaleY = canvas.height / rect.height;
		const x = (clientX - rect.left) * scaleX;
		const y = (clientY - rect.top) * scaleY;

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

	function handleCanvasMouseMove(e) {
		if (!currentPlayer || currentPlayer.id !== playerId) return;
		const territoryId = getTerritoryAt(e.clientX, e.clientY);
		setHoveredTerritory(territoryId);
	}

	function handleCanvasMouseLeave() {
		if (!currentPlayer || currentPlayer.id !== playerId) return;
		setHoveredTerritory(null);
	}

	function handleCanvasTouchEnd(e) {
		if (!currentPlayer || currentPlayer.id !== playerId) return;
		const touch = e.changedTouches[0];
		if (!touch) return;
		e.preventDefault();
		processSelection(getTerritoryAt(touch.clientX, touch.clientY));
	}

	function handleCanvasClick(e) {
		if (!currentPlayer || currentPlayer.id !== playerId) return;
		processSelection(getTerritoryAt(e.clientX, e.clientY));
	}

	function processSelection(clickedId) {
		if (!clickedId) {
			setSelectedTerritory(null);
			setFortifyFrom(null);
			setAttackFrom(null);
			setFortifyTo(null);
			setAttackTo(null);
			return;
		}

		const clickedTerritory = TERRITORIES[clickedId];

		if (selectedTerritory && selectedTerritory.id === clickedId) {
			setSelectedTerritory(null);
			return;
		}

		setSelectedTerritory({ id: clickedId, ...clickedTerritory });

		if (phase === TurnManager.PHASES.REINFORCE) {
			if (territoryOwners[clickedId] !== currentPlayer.faction) return;
			if (reinforcementsLeft <= 0) return;
			handleReinforce(clickedId);
			return;
		}

		if (phase === TurnManager.PHASES.ATTACK) {
			if (!attackFrom) {
				if (territoryOwners[clickedId] !== currentPlayer.faction) {
					return;
				}
				if (troopCount[clickedId] <= 1) {
					return;
				}
				setAttackFrom(clickedId);
				return;
			}

			if (clickedId === attackFrom) {
				setAttackFrom(null);
				setAttackTo(null);
				return;
			}
			if (clickedId === attackTo) {
				setAttackTo(null);
				return;
			}

			if (territoryOwners[clickedId] === currentPlayer.faction) {
				return;
			}

			if (!TERRITORIES[attackFrom].neighbors.includes(clickedId)) {
				return;
			}

			setAttackTo(clickedId);
			setAttackTroops(1); // Reset slider to minimum on new target selection
			return;
		}

		if (phase === TurnManager.PHASES.FORTIFY) {
			if (!fortifyFrom) {
				if (territoryOwners[clickedId] !== currentPlayer.faction) return;
				if (troopCount[clickedId] <= 1) return;
				setFortifyFrom(clickedId);
				return;
			}

			if (clickedId === fortifyFrom) {
				setFortifyFrom(null);
				setFortifyTo(null);
				return;
			}
			if (clickedId === fortifyTo) {
				setFortifyTo(null);
				return;
			}
			if (territoryOwners[clickedId] !== currentPlayer.faction) return;
			if (!TERRITORIES[fortifyFrom].neighbors.includes(clickedId)) return;

			setFortifyTo(clickedId);
		}
	}

	const isMyTurn = currentPlayer?.id === playerId;
	const myFaction = playerStats?.[playerId]?.faction;
	const isAlive = !myFaction || activeFactions.length === 0 || activeFactions.includes(myFaction);

	return (
		<div className="relative flex h-screen w-full flex-col overflow-hidden bg-[#0d0d0d]">
			{visibleAchievements.map((achievement) => (
				<AchievementNotification
					key={`${achievement.playerId}-${achievement.id}`}
					achievementId={achievement.id}
					onDismiss={() => handleAchievementDismiss(achievement.id)}
				/>
			))}

			<Chat
				messages={chatMessages}
				onSend={sendChat}
				status={wsStatus}
				playerId={playerId}
				onOpenProfile={setProfileUsername}
			/>

			{profileUsername && (
				<div className="fixed inset-0 z-50 flex items-start justify-center overflow-y-auto bg-black/70 p-2 sm:p-4">
					<Profile
						username={profileUsername}
						currentUser={playerId}
						onBack={() => setProfileUsername(null)}
					/>
				</div>
			)}

			<header className="relative flex-none py-1 sm:py-2">
				<h1 className="m-0 text-center font-mono text-base tracking-[2px] text-[#FF6B6B] [text-shadow:0_0_10px_rgba(255,107,107,0.3)] sm:text-2xl lg:text-[32px]">
					GREAT RISK
				</h1>
				<div className="absolute top-1 left-2 flex gap-1.5 sm:top-2 sm:left-5 sm:gap-2.5">
					<button
						onClick={onExitGame}
						className="cursor-pointer rounded border border-[#555] bg-[#333] px-2 py-0.5 font-mono text-[10px] text-[#aaa] sm:px-2.5 sm:py-1 sm:text-[11px]"
					>
						&larr; Exit
					</button>
					<button
						onClick={onLogout}
						className="cursor-pointer rounded border border-[#FF6B6B] bg-transparent px-2 py-0.5 font-mono text-[10px] text-[#FF6B6B] sm:px-2.5 sm:py-1 sm:text-[11px]"
					>
						Logout
					</button>
				</div>
			</header>

			<main className="flex min-h-0 flex-1 items-center justify-center px-1 sm:px-2">
				<div className="relative mx-auto aspect-[1100/700] h-full max-h-full w-auto max-w-full">
					<canvas
						ref={canvasRef}
						width={CANVAS_WIDTH}
						height={CANVAS_HEIGHT}
						className="block h-full w-full touch-none border-[3px] border-[#FF6B6B] shadow-[0_0_20px_rgba(255,107,107,0.3)]"
						onClick={handleCanvasClick}
						onTouchEnd={handleCanvasTouchEnd}
						onMouseMove={handleCanvasMouseMove}
						onMouseLeave={handleCanvasMouseLeave}
					/>
					<canvas
						ref={pickingCanvasRef}
						width={CANVAS_WIDTH}
						height={CANVAS_HEIGHT}
						className="absolute top-0 left-0 -z-10 hidden h-full w-full opacity-90"
					/>

					{(selectedTerritory || hoveredTerritory) && (
						<div className="absolute bottom-2 left-2 z-10 max-w-[200px] rounded-md border-2 border-[#6496FF] bg-black/90 p-2 font-mono text-[11px] text-[#E0E0E0] shadow-[0_0_15px_rgba(100,150,255,0.3)] sm:bottom-5 sm:left-5 sm:max-w-[250px] sm:p-3 sm:text-xs">
							{(() => {
								const territory =
									selectedTerritory || (hoveredTerritory && TERRITORIES[hoveredTerritory]);
								const territoryId = selectedTerritory?.id || hoveredTerritory;
								if (!territory) return null;
								return (
									<>
										<div className="mb-1.5 font-bold text-[#6496FF]">{territory.name}</div>
										<div className="text-[11px]">Capital: {territory.capital}</div>
										<div className="text-[11px]">
											Propietario:{' '}
											{territoryOwners[territoryId]
												? FACTIONS[territoryOwners[territoryId]]?.name || 'Desconocido'
												: 'Neutral'}
										</div>
										<div className="mt-1 text-[11px] text-[#FFD700]">
											Tropas: {troopCount[territoryId]}
										</div>
									</>
								);
							})()}
						</div>
					)}
				</div>
			</main>

			<footer
				className={`absolute bottom-9 left-1/2 z-20 flex w-[min(calc(100vw-0.5rem),calc((100dvh-2rem)*1100/700))] -translate-x-1/2 items-center justify-between gap-2 rounded-md border-2 border-[#FF6B6B] bg-[#0f0f0f]/90 p-2 font-mono shadow-[0_0_20px_rgba(255,107,107,0.4)] backdrop-blur-sm transition-all duration-300 ease-out sm:gap-3 sm:p-3 lg:static lg:bottom-auto lg:left-auto lg:z-auto lg:mx-0 lg:w-auto lg:max-w-none lg:flex-none lg:translate-x-0 lg:translate-y-0 lg:rounded-none lg:border-x-0 lg:border-b-0 lg:border-t-[3px] lg:bg-[#0f0f0f] lg:opacity-100 lg:shadow-[0_-5px_15px_rgba(255,107,107,0.2)] lg:backdrop-blur-none ${
					showControls
						? 'translate-y-0 opacity-100'
						: 'pointer-events-none translate-y-full opacity-0 lg:pointer-events-auto'
				}`}
			>
					<div className="flex-1 text-[11px] text-[#E0E0E0] sm:text-[13px]">
						<div>
							Facción:{' '}
							<span className="text-[#FFD700]">
								{myFaction ? FACTIONS[myFaction]?.name : '—'}
							</span>
						</div>
						<div className="mt-1">
							Fase: <span className="font-bold text-[#FF6B6B]">{phase}</span>
						</div>
						{currentPlayer && (
							<div className={`mt-1 text-[10px] sm:mt-1.5 sm:text-[11px] ${isMyTurn ? 'text-[#4CAF50]' : 'text-[#888]'}`}>
								Turno:{' '}
								<span className={isMyTurn ? 'text-[#4CAF50]' : 'text-[#bbb]'}>
									{isMyTurn ? (
										'Tu turno'
									) : (
										<>
											<button
												onClick={() => setProfileUsername(currentPlayer.id)}
												className="cursor-pointer border-0 bg-transparent p-0 font-mono text-[10px] font-bold text-[#6496FF] hover:underline sm:text-[11px]"
											>
												{currentPlayer.id}
											</button>
											{' — '}{FACTIONS[currentPlayer.faction]?.name || '?'}
										</>
									)}
								</span>
							</div>
						)}
						{isMyTurn && phase === TurnManager.PHASES.REINFORCE && (
							<div className="mt-1 font-bold text-[#4CAF50]">
								Refuerzos: {reinforcementsLeft}
							</div>
						)}
					</div>

					<div className="flex flex-1 flex-col items-center gap-1 sm:gap-2">
						<div className="text-center text-[11px] text-white sm:text-[13px]">
							<div>Turno</div>
							<div className="text-sm font-bold text-[#FFD700] sm:text-base">
								{turn} / {maxTurns}
							</div>
						</div>
						<button
							onClick={handleNextTurn}
							disabled={!isMyTurn || !!winner}
							className="min-w-[100px] rounded border-0 bg-[#FF6B6B] px-2 py-1.5 text-[11px] font-bold text-white shadow-[0_0_10px_rgba(255,107,107,0.3)] transition-all duration-200 enabled:cursor-pointer enabled:hover:bg-[#FF5252] enabled:hover:shadow-[0_0_20px_rgba(255,107,107,0.6)] disabled:cursor-not-allowed disabled:opacity-40 sm:min-w-[140px] sm:px-4 sm:py-2 sm:text-xs"
						>
							Siguiente turno
						</button>
						<button
							onClick={handleSurrender}
							disabled={!isAlive || !!winner}
							className="min-w-[100px] rounded border border-[#FF6B6B] bg-transparent px-2 py-1 text-[10px] font-bold text-[#FF6B6B] transition-all duration-200 enabled:cursor-pointer enabled:hover:bg-[#FF6B6B] enabled:hover:text-white disabled:cursor-not-allowed disabled:opacity-40 sm:min-w-[140px] sm:px-3 sm:py-1.5 sm:text-[11px]"
						>
							Rendirse
						</button>
					</div>

					<div className="min-h-[60px] flex-1">
						{phase === TurnManager.PHASES.FORTIFY && fortifyFrom && fortifyTo && (
							<div className="text-xs text-white">
								<div className="mb-1.5 font-bold">
									{TERRITORIES[fortifyFrom].name} '&gt;' {TERRITORIES[fortifyTo].name}
								</div>
								<input
									type="range"
									min={1}
									max={troopCount[fortifyFrom] - 1}
									value={fortifyTroops}
									onChange={(e) => setFortifyTroops(Number(e.target.value))}
									className="mb-1 w-full"
								/>
								<div className="mb-1.5 text-[11px]">Tropas: {fortifyTroops}</div>
								<button
									onClick={() => handleFortify(fortifyTo)}
									disabled={currentPlayer?.id !== playerId}
									className="mb-[3px] w-full cursor-pointer rounded-[3px] border-0 bg-[#4CAF50] p-1 text-[11px] font-bold text-white transition-all duration-200 hover:bg-[#45a049] hover:shadow-[0_0_10px_rgba(76,175,80,0.4)]"
								>
									Mover
								</button>
								<button
									onClick={() => {
										setFortifyFrom(null);
										setFortifyTo(null);
										setFortifyTroops(1);
									}}
									className="w-full cursor-pointer rounded-[3px] border-0 bg-[#FF6B6B] p-1 text-[11px] font-bold text-white transition-all duration-200 hover:bg-[#FF5252] hover:shadow-[0_0_10px_rgba(255,107,107,0.4)]"
								>
									Cancelar
								</button>
							</div>
						)}

						{phase === TurnManager.PHASES.ATTACK && attackFrom && attackTo && (
							<div className="text-xs text-white">
								<div className="mb-1.5 font-bold">
									{TERRITORIES[attackFrom].name} → {TERRITORIES[attackTo].name}
								</div>
								<input
									type="range"
									min={1}
									max={Math.min(3, troopCount[attackFrom] - 1)}
									value={attackTroops}
									onChange={(e) => setAttackTroops(Number(e.target.value))}
									className="mb-1 w-full"
								/>
								<div className="mb-1.5 text-[11px]">Tropas: {attackTroops}</div>
								<button
									onClick={handleAttack}
									disabled={currentPlayer?.id !== playerId}
									className="mb-[3px] w-full rounded-[3px] border-0 bg-[#FF6B6B] p-1 text-[11px] font-bold text-white transition-all duration-200 hover:bg-[#FF5252] hover:shadow-[0_0_10px_rgba(255,107,107,0.4)] disabled:cursor-not-allowed disabled:opacity-50 enabled:cursor-pointer"
								>
									¡Atacar!
								</button>
								<button
									onClick={() => {
										setAttackFrom(null);
										setAttackTo(null);
										setAttackTroops(1);
									}}
									className="w-full cursor-pointer rounded-[3px] border-0 bg-[#FF6B6B] p-1 text-[11px] font-bold text-white transition-all duration-200 hover:bg-[#FF5252] hover:shadow-[0_0_10px_rgba(255,107,107,0.4)]"
								>
									Cancelar
								</button>
							</div>
						)}
					</div>
</footer>

			<button
				type="button"
				onClick={() => setShowControls((s) => !s)}
				aria-label={showControls ? 'Hide controls' : 'Show controls'}
				className="absolute bottom-1 left-1/2 z-30 flex h-7 w-12 -translate-x-1/2 cursor-pointer items-center justify-center rounded-md border border-[#FF6B6B] bg-[#0f0f0f]/90 font-mono text-sm text-[#FF6B6B] shadow-[0_0_10px_rgba(255,107,107,0.4)] backdrop-blur-sm hover:bg-[#FF6B6B] hover:text-white lg:hidden"
			>
				{showControls ? '▼' : '▲'}
			</button>

			{winner && (
				<div className="fixed top-1/2 left-1/2 z-30 max-h-[90vh] w-[92vw] max-w-md -translate-x-1/2 -translate-y-1/2 overflow-y-auto rounded-[10px] border-[3px] border-[#FF6B6B] bg-black/95 p-5 text-center font-mono text-white shadow-[0_0_30px_rgba(255,107,107,0.5)] sm:p-8">
					<h2 className="mt-0 mb-4 text-[#FF6B6B]">
						¡{FACTIONS[winner.factionId].name} gana!
					</h2>
					<p className="mb-5 text-[#E0E0E0]">
						{winner.reason === 'capitals'
							? 'Ha conquistado todas las capitales enemigas'
							: `Victoria por puntos — ${calculateScore(winner.factionId, territoryOwners)} pts`}
					</p>
					<button
						onClick={onExitGame}
						className="cursor-pointer rounded border-0 bg-[#4CAF50] px-5 py-2.5 text-sm font-bold text-white transition-all duration-200 hover:bg-[#45a049] hover:shadow-[0_0_15px_rgba(76,175,80,0.5)]"
					>
						Nueva partida
					</button>
				</div>
			)}

			{battleReport && (
				<div className="fixed top-1/2 left-1/2 z-[25] max-h-[90vh] w-[92vw] max-w-[400px] -translate-x-1/2 -translate-y-1/2 overflow-y-auto rounded-[10px] border-2 border-[#FF6B6B] bg-black/95 p-4 text-center font-mono text-white shadow-[0_0_20px_rgba(255,107,107,0.5)] sm:p-6">
					<h2 className="mt-0 mb-4 text-[#FF6B6B]">Battle Report</h2>

					<div className="mb-3 rounded-md bg-[rgba(255,107,107,0.1)] p-3">
						<div className="mb-2 text-sm">
							<strong>{battleReport.attackFrom}</strong>{' '}
							<span className="text-[#FFD700]">→</span>{' '}
							<strong>{battleReport.attackTo}</strong>
						</div>
					</div>

					<div className="mb-4 grid grid-cols-2 gap-3">
						<div className="rounded-md border-l-[3px] border-[#6496FF] bg-[rgba(100,150,255,0.2)] p-3">
							<div className="mb-2 text-xs text-[#6496FF]">ATTACKER</div>
							<div className="mb-1.5 text-sm">
								Troops: <strong>{battleReport.attackerTroops}</strong>
							</div>
							<div className="text-[11px] text-[#CCC]">
								Dice: {battleReport.attackDice.join(', ')}
							</div>
						</div>

						<div className="rounded-md border-l-[3px] border-[#FF6B6B] bg-[rgba(255,107,107,0.2)] p-3">
							<div className="mb-2 text-xs text-[#FF6B6B]">DEFENDER</div>
							<div className="mb-1.5 text-sm">
								Troops: <strong>{battleReport.defenderTroops}</strong>
							</div>
							<div className="text-[11px] text-[#CCC]">
								Dice: {battleReport.defenseDice.join(', ')}
							</div>
						</div>
					</div>

					{battleReport.troopBonus > 0 && (
						<div className="mb-4 rounded-md border-l-[3px] border-[#4CAF50] bg-[rgba(76,175,80,0.15)] p-2.5">
							<div className="text-xs font-bold text-[#4CAF50]">
								✦ Reinforcements increased attack in +{battleReport.troopBonus}
							</div>
						</div>
					)}

					<div className="mb-4 rounded-md bg-black/50 p-3">
						<div className="mb-1.5 text-xs">CASUALTIES</div>
						<div className="grid grid-cols-2 gap-3">
							<div>
								<div className="text-[13px] text-[#6496FF]">Attacker Losses</div>
								<div className="text-base font-bold text-[#FF9999]">
									-{battleReport.attackerLosses}
								</div>
							</div>
							<div>
								<div className="text-[13px] text-[#FF6B6B]">Defender Losses</div>
								<div className="text-base font-bold text-[#FF9999]">
									-{battleReport.defenderLosses}
								</div>
							</div>
						</div>
					</div>

					<div
						className={`mb-4 rounded-md border-l-[3px] p-3 ${
							battleReport.conquered
								? 'border-[#4CAF50] bg-[rgba(76,175,80,0.2)]'
								: 'border-[#FF6B6B] bg-[rgba(255,107,107,0.2)]'
						}`}
					>
						<div
							className={`text-sm font-bold ${
								battleReport.conquered ? 'text-[#4CAF50]' : 'text-[#FF9999]'
							}`}
						>
							{battleReport.conquered ? '✓ TERRITORY CONQUERED!' : '✗ Attack Failed'}
						</div>
					</div>

					<button
						onClick={() => setBattleReport(null)}
						className="w-full cursor-pointer rounded border-0 bg-[#FF6B6B] p-2.5 text-[13px] font-bold text-white transition-all duration-200 hover:bg-[#FF5252] hover:shadow-[0_0_15px_rgba(255,107,107,0.5)]"
					>
						Continue
					</button>
				</div>
			)}
		</div>
	);
}
