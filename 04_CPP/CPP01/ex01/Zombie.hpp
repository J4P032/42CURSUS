/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 22:13:11 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/02 10:59:21 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>

class Zombie {
    public:
		Zombie(void);
		~Zombie(void);

		void setName(std::string my_name);
		void announce(void) const;
	private:
		std::string _name;	
};

Zombie *zombieHorde(int N, std::string name);

#endif
