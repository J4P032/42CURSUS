/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:20:56 by jrollon-          #+#    #+#             */
/*   Updated: 2026/04/07 12:36:29 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>

class	PmergeMe{
private:
	std::vector<int>	_vector;
	std::deque<int>		_deque;

public:
	PmergeMe(void);
	PmergeMe(const PmergeMe&);
	PmergeMe& operator=(const PmergeMe&);
	~PmergeMe(void);

	void	setPmergeMe(int);
	
};

#endif