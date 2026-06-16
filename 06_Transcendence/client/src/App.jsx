/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.jsx                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagonzal <cagonzal@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 13:47:37 by jrollon-          #+#    #+#             */
/*   Updated: 2026/06/09 18:14:28 by cagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

import { useEffect, useState } from 'react';
import Lobby from './components/Lobby.jsx';
import GameBoard from './components/Gameboard.jsx';
import Login from './components/Login.jsx';
import Register from './components/Register.jsx';
import Footer from './components/Footer.jsx';
import Privacy from './components/Privacy.jsx';
import Terms from './components/Terms.jsx';
import RotatePrompt from './components/RotatePrompt.jsx';

const USER_STORAGE_KEY = 'transcendence.user';

function loadUser() {
	try {
		const raw = localStorage.getItem(USER_STORAGE_KEY);
		return raw ? JSON.parse(raw) : null;
	} catch {
		return null;
	}
}

export default function App() {
	const [user, setUser] = useState(loadUser);
	const [view, setView] = useState('login');
	const [gameInfo, setGameInfo] = useState(null);

	useEffect(() => {
		if (user) localStorage.setItem(USER_STORAGE_KEY, JSON.stringify(user));
		else localStorage.removeItem(USER_STORAGE_KEY);
	}, [user]);

	const handleLogout = () => {
		setUser(null);
		setGameInfo(null);
	};

	let content;
	if (view === 'privacy') {
		content = <Privacy onBack={() => setView('login')} />;
	} else if (view === 'terms') {
		content = <Terms onBack={() => setView('login')} />;
	} else if (!user) {
		content = (
			<>
				{view === 'register' ? (
					<Register onLogin={setUser} onBack={() => setView('login')} />
				) : (
					<Login onLogin={setUser} onGoToRegister={() => setView('register')} />
				)}
				<Footer
					onPrivacy={() => setView('privacy')}
					onTerms={() => setView('terms')}
				/>
			</>
		);
	} else if (!gameInfo) {
		content = (
			<Lobby
				onStart={setGameInfo}
				initialPlayerId={user.username}
				onLogout={handleLogout}
			/>
		);
	} else {
		content = (
			<GameBoard
				roomId={gameInfo.roomId}
				playerId={gameInfo.playerId}
				onLogout={handleLogout}
				onExitGame={() => setGameInfo(null)}
			/>
		);
	}

	return (
		<>
			{content}
			<RotatePrompt />
		</>
	);
}
