/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:47:19 by jrollon-          #+#    #+#             */
/*   Updated: 2026/01/12 17:28:51 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
# define BASE_HPP

# include <iostream>
# include <cstdlib> //randomize
# include <ctime> //semilla de rand

class Base{
public:
	virtual ~Base(void);
};

class A : public Base{
};

class B : public Base{
};

class C : public Base{
};

Base* 	generate(void);

void	identify(Base* p);

void 	identify(Base& p);

#endif
