/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:18:59 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/02 16:32:46 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

#include <iostream>

class	Harl{
	public :
		Harl(void);
		~Harl(void);
		void	complain(std::string level);
	
	private :
		void	debug(void);
		void	info(void);	
		void	warning(void);
		void	error(void);
};


#endif
