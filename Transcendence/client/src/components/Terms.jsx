/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Terms.jsx                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 10:58:52 by jrollon-          #+#    #+#             */
/*   Updated: 2026/05/29 11:08:00 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

import React from 'react';

export default function Terms({ onBack }) {
  return (
    <div style={containerStyle}>
      <h1 style={titleStyle}>TERMS OF SERVICE</h1>
      
      <div style={contentStyle}>
        <h3 style={sectionTitle}>1. ACCEPTANCE OF TERMS</h3>
        <p>By accessing ft_transcendence, you agree to follow the rules of the 42 community. This platform is an educational project created for the 42 Common Core.</p>

        <h3 style={sectionTitle}>2. FAIR PLAY</h3>
        <p>Hacking, cheating, or intentionally exploiting bugs is strictly prohibited. The game is designed to test strategy and skill, not exploit-finding abilities.</p>

        <h3 style={sectionTitle}>3. CODE OF CONDUCT</h3>
        <p>Bullying, hate speech, or harassment in the global chat will result in an immediate account suspension. Respect your fellow students as per the 42 Pedagogy standards.</p>

        <h3 style={sectionTitle}>4. LIMITATION OF LIABILITY</h3>
        <p>This software is provided "as is", without warranty of any kind. The developers are not responsible for any data loss or "emotional damage" caused by losing a game of Risk.</p>

        <h3 style={sectionTitle}>5. ACCOUNT TERMINATION</h3>
        <p>We reserve the right to terminate accounts that violate these terms or the general spirit of the 42 Network.</p>
      </div>

      <button onClick={onBack} style={btnStyle}>GO BACK</button>
    </div>
  );
}

const containerStyle = {
  maxWidth: '700px',
  margin: '40px auto',
  padding: '40px',
  backgroundColor: '#1a1a2e',
  border: '2px solid #FF6B6B',
  color: 'white',
  fontFamily: 'monospace',
  borderRadius: '12px',
};

const titleStyle = { textAlign: 'center', color: '#FF6B6B', marginBottom: '30px' };
const contentStyle = { textAlign: 'left', fontSize: '14px', lineHeight: '1.6' };
const sectionTitle = { color: '#FFD700', marginTop: '20px' };
const btnStyle = { 
  display: 'block', margin: '30px auto 0', padding: '10px 20px', 
  backgroundColor: '#444', color: 'white', border: 'none', cursor: 'pointer' 
};
