import './App.css';
import { useState } from 'react';
import Lobby from './components/Lobby.jsx';
import GameBoard from './components/Gameboard.jsx';

export default function App() {
  const [gameInfo, setGameInfo] = useState(null);
  // gameInfo = { roomId, playerId, faction }
	console.log('gameInfo:', gameInfo);
	console.log('roomId tipo:', typeof gameInfo?.roomId, gameInfo?.roomId);
  return gameInfo
    ? <GameBoard roomId={gameInfo.roomId} playerId={gameInfo.playerId} />
    : <Lobby onStart={setGameInfo} />;
}
