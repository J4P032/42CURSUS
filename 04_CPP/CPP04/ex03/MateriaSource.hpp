/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:15:56 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/14 08:30:44 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

# include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource{
	private:
		AMateria	*_materias[4];
		size_t		_trashCapacity; //ground dinamico para almacenar punteros magias soltadas
		AMateria	**_trash; //para almacenar las magias soltadas

	public:
		MateriaSource(void);
		MateriaSource(const MateriaSource &other);
		~MateriaSource(void);
		MateriaSource	&operator=(const MateriaSource &other);

		void		learnMateria(AMateria*);
		AMateria 	*createMateria(std::string const &type);
		void		sendToTrash(AMateria *materia);
};

#endif
