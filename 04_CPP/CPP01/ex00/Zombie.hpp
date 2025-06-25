/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:49:34 by jrollon-          #+#    #+#             */
/*   Updated: 2025/06/25 09:32:10 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

class Zombie {

    public:
        Zombie (std::string my_name){}    
        ~Zombie (void){}
    
        void announce (void){}
        
    private:
        std::string name;
};