/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:54:08 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/12 14:43:14 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"


void	test42Default(void){
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound(); //will output the cat sound!
	j->makeSound();
	meta->makeSound();
	delete meta;
	delete j;
	delete i;
}

void	test42Wrong(void){
	const WrongAnimal* meta = new WrongAnimal();
	const WrongAnimal* i = new WrongCat();
	const WrongCat	*wCat = new WrongCat();
	std::cout << i->getType() << " " << std::endl;
	std::cout << wCat->getType() << " " << std::endl;
	i->makeSound(); //esta vez suelta el Animal sound ya que no es virtual
	meta->makeSound();
	std::cout << "WrongCat as WrongCat sound: ";
	wCat->makeSound();
	std::cout << std::endl;
	delete meta;
	delete i;
	delete wCat;
}

void	myTests(void){
	Animal		*meta = new Animal();
	Animal		*meta2 = new Animal(*meta);
	Animal		*gato = NULL;
	Cat			*gato2 = new Cat();
	const Dog	*perro = new Dog();
	Dog			*perro2 = new Dog(*perro);
	Cat			g1;
	Cat			g2;
	Animal		a1;
	Animal		a2;
	Animal		a3(a1);
	
	
	gato = gato2;
	g1 = g2;
	a1 = a2;
	std::cout << meta->getType() << " " << std::endl;
	std::cout << meta2->getType() << " " << std::endl;
	std::cout << gato->getType() << " " << std::endl;
	std::cout << gato2->getType() << " " << std::endl;
	std::cout << perro->getType() << " " << std::endl;
	std::cout << perro2->getType() << " " << std::endl;
	std::cout << g1.getType() << " " << std::endl;
	std::cout << g2.getType() << " " << std::endl;
	meta->makeSound();
	meta2->makeSound();
	gato->makeSound();
	gato2->makeSound();
	perro->makeSound();
	perro2->makeSound();
	g1.makeSound();
	g2.makeSound();
	delete meta;
	delete meta2;
	delete gato;
	delete perro;
	delete perro2;
}


int main(int argc, char **argv)
{
	system("clear");
	if (argc != 2){
		std::cerr << "⛔	Please input: AnimalSpeak <num>" << std::endl;
		std::cerr << "<num>:	1. Default 42 Tester" << std::endl;
		std::cerr << "	2. Default 42 WrongAnimal Tester" << std::endl;
		std::cerr << "	3. My own Tester" << std::endl;
		std::cerr << std::endl;
		return (1);
	}
	int	num = std::atoi(argv[1]);
	switch (num){
		case 1 :
			test42Default();
			break;
		case 2 :
			test42Wrong();
			break;
		case 3 :
			myTests();
			break;
		default :
			std::cerr << "⛔	wrong <num> selection" << std::endl;
			break;
	}
	return (0);
}
