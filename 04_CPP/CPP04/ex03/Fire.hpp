/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fire.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:10:10 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/13 14:12:28 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIRE_HPP
# define FIRE_HPP

# include "AMateria.hpp"

class	Fire : public AMateria{
	
	public:
		Fire(void);
		Fire(const Fire &other);
		~Fire(void);
		Fire	&operator=(const Fire &other);

		AMateria	*clone(void) const;
		void 		use(ICharacter &target);
};

#endif
