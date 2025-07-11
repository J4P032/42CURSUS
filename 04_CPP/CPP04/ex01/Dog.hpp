/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:40:49 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/12 00:10:50 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"
# include "Brain.hpp"

class	Dog : public Animal{
	private:
		Brain *_brain;
	
	public:
		Dog(void);
		Dog(const Dog &other);
		Dog	&operator=(const Dog &other);
		~Dog(void);

		void makeSound(void) const;
};

#endif
