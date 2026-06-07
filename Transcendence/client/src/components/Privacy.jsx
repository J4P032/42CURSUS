/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privacy.jsx                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 10:58:47 by jrollon-          #+#    #+#             */
/*   Updated: 2026/05/29 11:05:02 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


import React from 'react';

export default function Privacy({ onBack }) {
  return (
    <div style={containerStyle}>
      <h1 style={titleStyle}>PRIVACY POLICY</h1>
      
      <div style={contentStyle}>
        <h3 style={sectionTitle}>1. DATA COLLECTION</h3>
        <p>We only collect the strictly necessary data for the operation of ft_transcendence: your email address, username, and encrypted password. For 42 school evaluation purposes, we also store game statistics and match history.</p>

        <h3 style={sectionTitle}>2. DATA SECURITY</h3>
        <p>Your password is never stored in plain text. We use scrypt, a memory-hard key derivation function, with a per-user random salt to ensure your credentials are protected against unauthorized access.</p>

        <h3 style={sectionTitle}>3. COOKIES AND LOCAL STORAGE</h3>
        <p>We use local storage only to maintain your session active. We do not use tracking or advertising cookies.</p>

        <h3 style={sectionTitle}>4. DATA SHARING</h3>
        <p>Your data is not shared with any third parties. It is stored exclusively within our private database environment for the duration of this project's evaluation.</p>
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
