/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:36:57 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/12 00:07:35 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <string>
# include "Cat.hpp"
# include "Dog.hpp"

class Brain{
	private:
		std::string	_ideas[100];
	
	public:
		Brain(void);
		Brain(const Brain &other);
		Brain(std::string type);
		virtual ~Brain(void);
		Brain &operator=(const Brain &other);
		
		std::string	getIdeas(size_t	index) const;
		void		setIdeas(size_t index, const std::string &idea);
};

#endif
