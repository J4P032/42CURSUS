/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:47:19 by jrollon-          #+#    #+#             */
/*   Updated: 2026/01/13 10:10:10 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
# define BASE_HPP

# include <iostream>
# include <cstdlib> //randomize
# include <ctime> //semilla de rand
# include <exception> //para identify por referencia

#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[38;2;255;0;0m"
#define GREEN "\033[38;2;0;255;0m"
#define YELLOW "\033[38;5;226m"
#define BLUE "\033[38;2;0;100;255m"
#define MAGENTA "\033[38;2;100;50;255m"
#define CYAN "\033[38;2;0;200;255m"
#define WHITE "\033[37m"

class Base{
public:
	virtual ~Base(void);
};

class A : public Base{
public:
	A(void);
};

class B : public Base{
public:
	B(void);
};

class C : public Base{
public:
	C(void);
};

Base* 	generate(void);

void	identify(Base* p);

void 	identify(Base& p);

#endif
