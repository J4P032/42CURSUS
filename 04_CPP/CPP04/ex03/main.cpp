/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:09:40 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/14 00:10:28 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "Fire.hpp"

/* int main()
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
	return (0);
} */

int main()
{
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
		src->learnMateria(new Ice());
		Cure *cureptr = new Cure();
		src->learnMateria(cureptr);//NO PUEDO HACER DELETE EN MAIN ya que la funcion
			//que lo libera esta en learnMateria y al ser puntero simple "por obligacion de ejercicio"
			//poner un NULL ahi no valdria de nada para no hacer double double free con SegFault en el destructor

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

		ICharacter* pepe = new Character("pepe");

		javi->use(0, *pepe); //fire
		//javi->use(0, *null); NO SE PUEDE por que al TENER QUE RECIBIR "&target" TIENE QUE SER NO NULL SIEMPRE
		javi->use(1, *pepe); //ice
		javi->use(1, *javi); //ice
		javi->use(2, *javi); //heals
		javi->unequip(0); //quita fuego
		javi->use(0, *javi); //no deberia salir
		javi->use(3, *pepe); //fuego2
		
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
		for(size_t i = 0; i < 4; i++){
			tmp = src->createMateria("cure");
			javi->equip(tmp); //tmp sigue teniendo direccion pero esta liberado necestio hacer un createMateria de nuevo
		}
		javi->use(0, *pepe); 
		javi->use(1, *pepe); 
		javi->use(2, *pepe); 
		javi->use(3, *pepe); 
		for(size_t i = 0; i < 4; i++){
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
