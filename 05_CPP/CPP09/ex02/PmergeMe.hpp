/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:20:56 by jrollon-          #+#    #+#             */
/*   Updated: 2026/04/07 18:39:01 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <iostream>


int	jacobsthal(int);

class	PmergeMe{
private:
	std::vector<int>	_vector;
	std::deque<int>		_deque;
	std::vector<int>	fJSort(std::vector<int>);

public:
	PmergeMe(void);
	PmergeMe(const PmergeMe&);
	PmergeMe& operator=(const PmergeMe&);
	~PmergeMe(void);

	void	setPmergeMe(int);
	void	printVector(void) const;
	double	vector_FJ(void);
	size_t	vectorSize(void);
	
};

#endif