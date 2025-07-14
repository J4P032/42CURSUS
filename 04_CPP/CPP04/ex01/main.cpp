/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:54:08 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/14 11:25:01 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib> //rand
#include <ctime> //time para rand
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

void	ex01_42Tester(void){
	const 	Animal* j = new Dog();
	const 	Animal* i = new Cat();
	Cat		*catAux;
	Dog		*dogAux;

	
	
	//AÑADIDO
	
	//Checkeo de DeepCopy
	
	std::cout << std::endl;
	std::cout << "CHECK DEEP COPY" << std::endl;
	std::cout << std::endl;
	
	Cat		catOrig;
	Dog		dogOrig;
	
	std::cout << "** BEFORE COPY **" << std::endl;
	std::cout << "🧠😸:	Default Idea[50]: " << catOrig.getBrain()->getIdeas(50) << std::endl;
	std::cout << "🧠🐶:	Default Idea[32]: " << dogOrig.getBrain()->getIdeas(32) << std::endl;
	catOrig.getBrain()->setIdeas(50, "Mice!");
	dogOrig.getBrain()->setIdeas(32, "Bone!");
	std::cout << "🧠😸:	Init Idea[50]: " << catOrig.getBrain()->getIdeas(50) << std::endl;
	std::cout << "🧠🐶:	Init Idea[32]: " << dogOrig.getBrain()->getIdeas(32) << std::endl;
	std::cout << "🧠😸:	Original Cat ideas Address: " << catOrig.getBrain() << std::endl;
	std::cout << "🧠🐶:	Origina Dog ideas Address: " << dogOrig.getBrain() << std::endl;
	
	Cat		catCopy = catOrig; //deep copy produced (copy constructor because declare de variable Class before)
	Dog		dogCopy = dogOrig;

	std::cout << "** AFTER COPY **" << std::endl;
	
	std::cout << "🧠😸:	Init Idea[50]: " << catOrig.getBrain()->getIdeas(50) << std::endl;
	std::cout << "🧠🐶:	Init Idea[32]: " << dogOrig.getBrain()->getIdeas(32) << std::endl;
	std::cout << "🧠😸:	Original Cat ideas Address: " << catOrig.getBrain() << std::endl;
	std::cout << "🧠🐶:	Origina Dog ideas Address: " << dogOrig.getBrain() << std::endl;

	std::cout << "🧠🐈:	Copy Idea[50]: " << catCopy.getBrain()->getIdeas(50) << std::endl;
	std::cout << "🧠🐕:	Copy Idea[32]: " << dogCopy.getBrain()->getIdeas(32) << std::endl;
	std::cout << "🧠🐈:	Copy Cat ideas Address: " << catCopy.getBrain() << std::endl;
	std::cout << "🧠🐕:	Copy Dog ideas Address: " << dogCopy.getBrain() << std::endl;

	std::cout << "** CHANGE IDEA OF ORIGINALS **" << std::endl;
	catOrig.getBrain()->setIdeas(50, "EAT JAM!");
	dogOrig.getBrain()->setIdeas(32, "PLAY PLAY AND PLAY!");
	std::cout << "🧠😸:	Init Idea[50]: " << catOrig.getBrain()->getIdeas(50) << std::endl;
	std::cout << "🧠🐶:	Init Idea[32]: " << dogOrig.getBrain()->getIdeas(32) << std::endl;
	std::cout << "🧠😸:	Original Cat ideas Address: " << catOrig.getBrain() << std::endl;
	std::cout << "🧠🐶:	Origina Dog ideas Address: " << dogOrig.getBrain() << std::endl;

	std::cout << "🧠🐈:	Copy Idea[50]: " << catCopy.getBrain()->getIdeas(50) << std::endl;
	std::cout << "🧠🐕:	Copy Idea[32]: " << dogCopy.getBrain()->getIdeas(32) << std::endl;
	std::cout << "🧠🐈:	Copy Cat ideas Address: " << catCopy.getBrain() << std::endl;
	std::cout << "🧠🐕:	Copy Dog ideas Address: " << dogCopy.getBrain() << std::endl;
	

	std::cout << "** ASSIGN OPERATOR DEEP COPY **" << std::endl;
	
	Cat	catEqual;
	Dog dogEqual;

	catEqual = catOrig; //operador = por que no declarado en la misma linea
	dogEqual = dogOrig;

	std::cout << "🧠😸:	Init Idea[50]: " << catOrig.getBrain()->getIdeas(50) << std::endl;
	std::cout << "🧠🐶:	Init Idea[32]: " << dogOrig.getBrain()->getIdeas(32) << std::endl;
	std::cout << "🧠😸:	Original Cat ideas Address: " << catOrig.getBrain() << std::endl;
	std::cout << "🧠🐶:	Origina Dog ideas Address: " << dogOrig.getBrain() << std::endl;

	std::cout << "🧠😻:	EqualCat Idea[50]: " << catEqual.getBrain()->getIdeas(50) << std::endl;
	std::cout << "🧠🦮:	EqualDog Idea[32]: " << dogEqual.getBrain()->getIdeas(32) << std::endl;
	std::cout << "🧠😻:	EqualCat Cat ideas Address: " << catEqual.getBrain() << std::endl;
	std::cout << "🧠🦮:	EqualDog Dog ideas Address: " << dogEqual.getBrain() << std::endl;

	//INICIALIZACION ARRAY
	
	std::srand(std::time(NULL));
	std::cout << std::endl;
	std::cout << "ARRAY ANIMALS 50/50" << std::endl;
	std::cout << std::endl;
	Animal	*beasts[10];
	for (size_t k = 0; k < 10; k++){
		if (k < 5){
			beasts[k] = new Cat(); 
			catAux = dynamic_cast<Cat*>(beasts[k]); //lo necesita por que si no no puedo acceder a getBrain() ya que es de la clase Cat y Animal no lo tiene. 
												//Casteo dinamico por que asi asegura en ejecucion de que clase es realmente (mira si Beast[k] es Cat, como lo es. Sino seria NULL)
			if (catAux){
				for (size_t	index = 0; index < 99; index++){
					catAux->getBrain()->setIdeas(index, "Eat jam");//set _ideas[100]
				}
			}
		}
		else{
			beasts[k] = new Dog();
			dogAux = dynamic_cast<Dog*>(beasts[k]);
			if (dogAux){
				for (size_t	index = 0; index < 99; index++){
					dogAux->getBrain()->setIdeas(index, "Play!!");//set _ideas[100]
				}
			}
		}
	}
	
	//Decir la idea aleatoria
	size_t	randomNum;
	randomNum = std::rand() % 100; //de 0 a 99
	catAux = dynamic_cast<Cat*>(beasts[3]);
	if (catAux){
		std::cout << "🧠😸	Cat random idea number: " << randomNum << " " << catAux->getBrain()->getIdeas(randomNum) << std::endl;
	
		randomNum = std::rand() % 100; //de 0 a 99
	}
	dogAux = dynamic_cast<Dog*>(beasts[6]);
	if (dogAux){
		std::cout << "🧠🐶	Dog random idea number: " << randomNum << " " << dogAux->getBrain()->getIdeas(randomNum) << std::endl;
	}
	//Liberacion Memoria
	for (size_t k = 0; k < 10; k++){
		delete beasts[k];
		beasts[k] = NULL;
	}
	std::cout << std::endl;
	std::cout << "END ARRAY ANIMALS 50/50" << std::endl;
	std::cout << std::endl;

	//FIN AÑADIDO

	delete j;//should not create a leak
	delete i;
}


int main(int argc, char **argv)
{
	system("clear");
	if (argc != 2){
		std::cerr << "⛔	Please input: AnimalSpeak <num>" << std::endl;
		std::cerr << "<num>:	1. Default 42 Tester" << std::endl;
		std::cerr << "	2. Default 42 WrongAnimal Tester" << std::endl;
		std::cerr << "	3. My own Tester" << std::endl;
		std::cerr << "	4. ex01 Tester" << std::endl;
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
		case 4 :
			ex01_42Tester();
			break;
		default :
			std::cerr << "⛔	wrong <num> selection" << std::endl;
			break;
	}
	return (0);
}
