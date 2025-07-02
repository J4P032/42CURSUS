/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:49:34 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/02 10:57:53 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>

class Zombie {

    public:
        Zombie (std::string my_name);  
        ~Zombie (void);
    
        void announce (void) const;
        
    private:
        std::string _name;
};

Zombie  *newZombie(std::string name);
void    randomChump(std::string name);

#endif
