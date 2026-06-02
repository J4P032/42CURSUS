/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Footer.jsx                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:10:50 by jrollon-          #+#    #+#             */
/*   Updated: 2026/05/29 11:51:02 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

import React from 'react';

export default function Footer({ onPrivacy, onTerms }) {
	return (
		<footer style={footerStyle}>
			<span onClick={onPrivacy} style={linkStyle}> Privacy Policy</span>
			<span style={{ margin: '0 15px', color: '#555' }}>|</span>
			<span onClick={onTerms} style={linkStyle}>Terms of Service</span>
		</footer>	
	);
}

const footerStyle = {
	position: 'fixed',
	bottom: '0',
	left: '0',
	width: '100%',
	padding: '15px 0',
	backgroundColor: '#0a0a1a',
  	borderTop: '1px solid #333',
  	textAlign: 'center',
  	fontFamily: 'monospace',
  	fontSize: '12px',
  	color: '#888',
  	zIndex: 1000 // Para que siempre esté por encima de todo
};

const linkStyle = {
  cursor: 'pointer',
  textDecoration: 'underline',
  color: '#aaa',
  transition: 'color 0.2s'
};
