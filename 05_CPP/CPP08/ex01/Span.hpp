/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:43:19 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/10 15:20:41 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <iostream>

class	Span{
public:
	Span(void);
	Span(unsigned int);
	Span(const Span&);
	Span& operator=(const Span&);
	~Span(void);
	
	void	addNumber(int);
	int		shortestSpan(void) const;
	int		longestSpan(void) const;

private:
	std::vector<int>	_span;
	unsigned int		_maxSize;
};



#endif
