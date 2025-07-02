/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:03:36 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/02 11:00:46 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

#include <iostream>

class	Weapon{
	public :
		Weapon(const std::string &myWeapon);
		~Weapon(void);
		
		const std::string	&getType(void) const;
		void				setType(const std::string &newType);
		
	private :
		std::string	_type;
};

#endif
