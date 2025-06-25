/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:49:34 by jrollon-          #+#    #+#             */
/*   Updated: 2025/06/25 10:20:19 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

class Zombie {

    public:
        Zombie (std::string my_name);  
        ~Zombie (void);
    
        void announce (void) const;
        
    private:
        std::string name;
};

Zombie  *newZombie(std::string name);
void    randomChump(std::string name);