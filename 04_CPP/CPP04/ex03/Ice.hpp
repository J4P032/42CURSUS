/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:32:39 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/12 17:34:54 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
# define ICE_HPP

# include "AMateria.hpp"

class	Ice : public AMateria{
	
	public:
		Ice(void);
		Ice(const Ice &other);
		~Ice(void);
		Ice	&operator=(const Ice &other);

		AMateria	*clone(void) const;
		void 		use(ICharacter &target);
};

#endif

