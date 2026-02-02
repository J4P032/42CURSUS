/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:36:22 by jrollon-          #+#    #+#             */
/*   Updated: 2026/01/21 12:46:09 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

# include <iostream>

template <typename T> void swap(T &a, T &b){
	T aux	= a;
	a 		= b;
	b 		= aux;
};

template <typename T> T min(T a, T b){
	return (a < b ? a : b);
};

template <typename T> T max(T a, T b){
	return (a > b ? a : b);
};

#endif
