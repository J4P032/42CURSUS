/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.jsx                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 13:47:37 by jrollon-          #+#    #+#             */
/*   Updated: 2026/05/29 12:04:33 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

import './App.css';
import { useState } from 'react';
import Lobby from './components/Lobby.jsx';
import GameBoard from './components/Gameboard.jsx';
import Login from './components/Login.jsx';
import Register from './components/Register.jsx';
import Footer from './components/Footer.jsx';
import Privacy from './components/Privacy.jsx';
import Terms from './components/Terms.jsx';

export default function App() {
	const [user, setUser] = useState(null); //guarda el usuario cuango loguea
	const [view, setView] = useState('login') //login, register, privacy, terms
	const [gameInfo, setGameInfo] = useState(null);

 	console.log('gameInfo:', gameInfo);
	console.log('roomId tipo:', typeof gameInfo?.roomId, gameInfo?.roomId);

	// 1. Pantallas Legales (Tienen prioridad de dibujado)
    if (view === 'privacy') return <Privacy onBack={() => setView('login')} />;
    if (view === 'terms') return <Terms onBack={() => setView('login')} />;

    // 2. Si no hay sesión iniciada (Login o Registro)
	// con el <> devuelve dos a la vez el register/login y el Footer de terminos
    if (!user) {
        return (
            <> 
                {view === 'register' ? (
                    <Register 
                        onLogin={setUser} 
                        onBack={() => setView('login')} 
                    />
                ) : (
                    <Login 
                        onLogin={setUser} 
                        onGoToRegister={() => setView('register')} 
                    />
                )}
                <Footer 
                    onPrivacy={() => setView('privacy')} 
                    onTerms={() => setView('terms')} 
                />
            </>
        );
    }

	//3. Si hay sesión pero no ha empezado la partida(lobby)
	if (!gameInfo){
		return (
      			<Lobby
				onStart={setGameInfo}
				initialPlayerId={user.username}
				onLogout={() => setUser(null)}
				/>
    	);
  	}

	//4. Si hay sesión y partida
	return (
    <GameBoard 
      roomId={gameInfo.roomId} 
      playerId={gameInfo.playerId} 
      onLogout={() => setUser(null)}
      onExitGame={() => setGameInfo(null)}
    />
  );
}
