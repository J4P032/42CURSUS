/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:56:15 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/12 00:30:53 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"
# include "Brain.hpp"

class	Cat : public Animal{
	private:
		Brain *_brain;
	
	public:
		Cat(void);
		Cat(const Cat &other);
		Cat	&operator=(const Cat &other);
		~Cat(void);

		void makeSound(void) const;
};

#endif
