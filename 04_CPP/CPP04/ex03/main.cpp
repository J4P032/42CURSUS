/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:09:40 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/14 10:06:15 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include "Character.hpp"
#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "Fire.hpp"

int main()
{
	system("clear");
	{
		IMateriaSource* src = new MateriaSource();
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());
		
		ICharacter* me = new Character("me");

		AMateria* tmp;
		tmp = src->createMateria("ice");
		me->equip(tmp);
		tmp = src->createMateria("cure");
		me->equip(tmp);

		ICharacter* bob = new Character("bob");

		me->use(0, *bob);
		me->use(1, *bob);
		
		delete bob;
		delete me;
		delete src;

	}
	std::cout << std::endl << " TEST PROPIO  " << std::endl << std::endl;
	{
		IMateriaSource* src = new MateriaSource();
		src->learnMateria(new Fire()); //nueva clase con hechizo fuego
		//check segfault
		src->learnMateria(new Fire());
		src->learnMateria(new Fire());
		src->learnMateria(new Fire());
		src->learnMateria(new Fire());
		
		src->learnMateria(new Ice());
		src->learnMateria(new Ice());
		src->learnMateria(new Ice());
		src->learnMateria(new Ice());
		Cure *cureptr = new Cure();
		src->learnMateria(cureptr);//NO PUEDO HACER DELETE EN MAIN ya que la funcion
			//que lo libera esta en learnMateria y al ser puntero simple "por obligacion de ejercicio"
			//poner un NULL ahi no valdria de nada para no hacer double double free con SegFault en el destructor
		
		//check segfault
		src->learnMateria(cureptr);
		src->learnMateria(cureptr);
		src->learnMateria(cureptr);
		src->learnMateria(cureptr);
		src->learnMateria(cureptr);
		src->learnMateria(cureptr);

		

		ICharacter* javi = new Character("javi");

		//ICharacter *null = NULL; //no puede ser NULL por que recibe un & y eso siempre es algo.

		AMateria* tmp;
		tmp = src->createMateria("fire");
		javi->equip(tmp);
		tmp = src->createMateria("ice");
		javi->equip(tmp);
		tmp = src->createMateria("cure");
		javi->equip(tmp);
		//tmp = src->createMateria("cure"); 
		//equipo dos punteros iguales para ver si protejo segfault. Lo hace ahora
		javi->equip(tmp);
		//tmp = src->createMateria("cure");
		javi->equip(tmp);
		//tmp = src->createMateria("cure");
		javi->equip(tmp);
		javi->equip(tmp);
		javi->equip(tmp);
		javi->equip(tmp);
		javi->equip(tmp); //Cuando se meten muchos iguales se puede hacer delete...
						//...dos veces y eso da segfault corregido en equip.

		tmp = src->createMateria("kk");//test de creacion nada
		javi->equip(tmp);//no debe meterlo. Y no lo hace

		tmp = src->createMateria("fire");
		javi->equip(tmp);
		javi->equip(tmp);
		javi->equip(tmp);
		javi->equip(tmp);

		std::cout << "ver lo que tiene equipado javi" << std::endl;
		javi->use(0, *javi);//fuego
		javi->use(1, *javi);//ice
		javi->use(2, *javi);//heal
		javi->use(3, *javi);//fuego2
		javi->use(4, *javi);
		std::cout << "visto equipado javi\n" << std::endl;

		ICharacter* pepe = new Character("pepe");
		
		std::cout << "check constructor de copias" << std::endl;
		Character ana("Ana");
		tmp = src->createMateria("fire");
		ana.equip(tmp);
		tmp = src->createMateria("ice");
		ana.equip(tmp);
		tmp = src->createMateria("cure");
		ana.equip(tmp);
		tmp = src->createMateria("fire");
		ana.equip(tmp);
		ana.equip(tmp);
		std::cout << "equipado ana" << std::endl;
		ana.use(0, ana);//fuego
		ana.use(1, ana);//ice
		ana.use(2, ana);//heal
		ana.use(3, ana);//fuego2
		ana.use(4, ana);
		std::cout << "termina equipado ana\n" << std::endl;
		
		std::cout << "copiado Ana a Noa" << std::endl;
		Character noa = ana; //constructor de copia
		
		std::cout << "equipado Noa" << std::endl;
		noa.use(0, noa);//fuego
		noa.use(1, noa);//ice
		noa.use(2, noa);//heal
		noa.use(3, noa);//fuego2
		noa.use(4, noa);
		std::cout << "termina equipado Noa\n" << std::endl;
		
		std::cout << "desequipa Ana solo" << std::endl;
		ana.unequip(0); //quita fuego
		std::cout << "Ana uso (no deberia salir nada): ";
		ana.use(0, *javi);//no deberia salir
		std::cout << "\nNoa uso: ";
		noa.use(0, *javi); //deberia salir fuego
		std::cout << "\ntermina test desequipa" << std::endl;
		
		std::cout << "copiado Ana a Sol" << std::endl;
		Character sol;
		sol = ana; //operador=
		
		std::cout << "equipado ana despues de desequiparse el 0" << std::endl;
		std::cout << "slot 0: "; ana.use(0, ana); std::cout << std::endl;//nada
		std::cout << "slot 1: "; ana.use(1, ana);//ice
		std::cout << "slot 2: "; ana.use(2, ana);//heal
		std::cout << "slot 3: "; ana.use(3, ana);//fuego2
		std::cout << "slot 4(no existe): "; ana.use(4, ana); std::cout << std::endl;
		std::cout << "termina equipado ana\n" << std::endl;

		std::cout << "equipado Sol no deberia tener el 0" << std::endl;
		std::cout << "slot 0: "; sol.use(0, sol); std::cout << std::endl;//nada
		std::cout << "slot 1: "; sol.use(1, sol);//ice
		std::cout << "slot 2: "; sol.use(2, sol);//heal
		std::cout << "slot 3: "; sol.use(3, sol);//fuego2
		std::cout << "slot 4(no existe): "; sol.use(4, sol); std::cout << std::endl;
		std::cout << "termina equipado ana\n" << std::endl;

		std::cout << "Test desequipa Ana completo" << std::endl;
		ana.unequip(0); //quita fuego
		ana.unequip(1);
		ana.unequip(2);
		ana.unequip(3);
		ana.unequip(4);
		ana.unequip(-5);
		std::cout << "Ana uso (no deberia salir nada): ";
		ana.use(0, *javi);//no deberia salir
		ana.use(1, *javi);
		ana.use(2, *javi);
		ana.use(3, *javi);
		ana.use(12, *javi);
		ana.use(-8, *javi);
		std::cout << "\nSol uso: ";
		sol.use(0, *javi); //deberia salir fuego
		sol.use(1, *javi);
		sol.use(2, *javi);
		sol.use(3, *javi);
		sol.use(4, *javi);
		sol.use(-1, *javi);
		std::cout << "termina test desequipa" << std::endl;
		
		//suelta todo
		javi->unequip(0); //ver si hay segfault
		javi->unequip(1);
		javi->unequip(2);
		javi->unequip(3);
		javi->unequip(-4);//test segfault
		
		//no debe usar nada
		javi->use(0, *pepe); 
		javi->use(1, *pepe); 
		javi->use(2, *pepe); 
		javi->use(3, *pepe); 
		javi->use(-1, *pepe); 
		javi->use(100, *pepe);
		
		//test reposicion
		for(size_t i = 0; i < 15; i++){
			tmp = src->createMateria("cure");
			javi->equip(tmp); //tmp sigue teniendo direccion pero esta liberado necestio hacer un createMateria de nuevo
		}
		javi->use(0, *pepe); 
		javi->use(1, *pepe); 
		javi->use(2, *pepe); 
		javi->use(3, *pepe); 
		for(size_t i = 0; i < 32; i++){
			tmp = src->createMateria("fire");
			javi->equip(tmp); //debe equiparse por que si no hay leaks por la funcion que no recibe otro parametro (por ejercicio)
		}
		javi->use(0, *pepe); //sigue siendo cure ya que no se vaciaron
		javi->use(1, *pepe); 
		javi->use(2, *pepe); 
		javi->use(3, *pepe); 
		
		javi->equip(tmp);
		javi->equip(tmp);
		javi->equip(tmp);
		javi->equip(tmp);
		
		//test liberacion ground
		for(size_t i = 0; i < 101; i++){
			javi->unequip(0);
			tmp = src->createMateria("fire");
			javi->equip(tmp); 
		}
		javi->use(0, *pepe); //solo cambia fuego
		javi->use(1, *pepe); 
		javi->use(2, *pepe); 
		javi->use(3, *pepe); 
		
		delete pepe;
		delete javi;
		delete src;
		
	}
	return 0;
}
