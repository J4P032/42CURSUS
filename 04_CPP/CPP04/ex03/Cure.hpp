/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:39:17 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/12 17:54:17 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
# define CURE_HPP

# include "AMateria.hpp"

class	Cure : public AMateria{
	
	public:
		Cure(void);
		Cure(const Cure &other);
		~Cure(void);
		Cure	&operator=(const Cure &other);

		AMateria	*clone(void) const;
		void 		use(ICharacter &target);
};

#endif
