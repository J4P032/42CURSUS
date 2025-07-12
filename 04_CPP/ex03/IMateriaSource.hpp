/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMateriaSource.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:10:30 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/12 20:15:22 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMATERIASOURCE_HPP
# define IMAGERIASOURCE_HPP

# include <iostream>

class AMateria;

class IMateriaSource
{
	public:
		virtual ~IMateriaSource();
		virtual void learnMateria(AMateria*) = 0;
		virtual AMateria *createMateria(std::string const & type) = 0;
};

#endif
