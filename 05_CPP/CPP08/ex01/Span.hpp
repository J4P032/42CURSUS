/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:43:19 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/12 14:45:02 by jrollon-         ###   ########.fr       */
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
	
	void			addNumber(int);
	void			addNumber(std::vector<int>::const_iterator, std::vector<int>::const_iterator);
	unsigned long	shortestSpan(void) const;
	unsigned long	longestSpan(void) const;

	Span	operator+(const Span& other) const;

	//getter
	const std::vector<int>&	getVector() const;

private:
	std::vector<int>	_span;
	unsigned int		_maxSize;
};

std::ostream& operator<<(std::ostream& out, const Span& other);

#endif
