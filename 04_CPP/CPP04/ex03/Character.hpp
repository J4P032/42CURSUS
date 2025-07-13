/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:04:22 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/13 13:38:18 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include <iostream>
# include "ICharacter.hpp"



class	Character : public ICharacter{

	private:
		std::string	_name;
		AMateria	*_inventory[4];
		size_t		_groundCapacity; //ground dinamico para almacenar punteros objetos soltados
		AMateria	**_ground; //para almacenar los objetos soltados
		
	public:
		Character(void);
		Character(const std::string &name);
		Character(const Character &other);
		~Character(void);
		Character	&operator=(const Character &other);

		//Metodos del interface
		std::string const &getName() const;
		void 		equip(AMateria *m);
		void		unequip(int idx);
		void		use(int idx, ICharacter &target);
};

#endif
