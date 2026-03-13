/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 09:38:28 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/13 13:36:38 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <list>

/*Un STACK como digo en el hpp es una capa que hace comportarse al contenedor por
debajo diferente a como debería. En este ejercicio cuando se hace una introducción
de 5 y luego 17, en el STACK queda como (17,5) PEEEEROOO internamente el DEQUE, VECTOR
o LIST queda como (5,17). Entonces cuando se pide un .top() este método interno lo que
devuelve es el contenedor.back() y así PARECE que el contenedor los tiene almacenados
en inverso.. PERO NO!!
POR ESOOO cuando se aplica el iterador a MutantStack pasa que sí que se accede al 
contenedor por debajo (DEQUE, LIST o VECTOR) y por lo tanto lo muestra en el orden suyo
que parece que es invertido PERO NO. asi saldrá en la solución a este primer test main_subject
como: 5,3,5,737,0 aunque haya sido el 0 el último número en meterse. Si lo hubieramos sacado
con .top() si que lo mostraría. se lo añado al final a las pruebas de subject para demostrarlo*/
int main_subject(){
	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << mstack.top() << std::endl;
	mstack.pop();
	std::cout << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
	std::cout << *it << std::endl;
	++it;
	}
	std::stack<int> s(mstack);
	std::cout << "con pop saldrá el cero: " << mstack.top() << std::endl;
	return 0;
}

int main_list(){
	std::list<int> mstack;
	mstack.push_back(5); //push() = push_back()
	mstack.push_back(17); 
	std::cout << mstack.back() << std::endl; //top() = back()
	mstack.pop_back();
	std::cout << mstack.size() << std::endl;
	mstack.push_back(3);
	mstack.push_back(5);
	mstack.push_back(737);
	//[...]
	mstack.push_back(0);
	std::list<int>::iterator it = mstack.begin();
	std::list<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
	std::cout << *it << std::endl;
	++it;
	}
	std::list<int> s(mstack);
	std::cout << "con pop saldrá el cero: " << s.back() << std::endl;
	return 0;
}

template <typename C>
void	fill_container(C& container, size_t size){
	int	num;
	int	neg;
	
	for (size_t i = 0; i < size; ++i){
		num = std::rand();
		neg = std::rand();
		num = !(neg %= 2) ? num : (num * - 1) - 1;
		
		container.push_back(num);
	}
}

template <typename C>
void	print_container(const C& container){
	typename C::const_iterator it = container.begin();
	for (; it != container.end(); ++it){
		if (it != container.begin())
			std::cout << ",";
		std::cout << *it;
	}
	std::cout << std::endl;
}

int	main_mytests(){
	srand(time(NULL));
	
	//PRUEBA CON VECTOR de INTs
	std::cout << "\n\nVECTOR<int> TEST" << std::endl;
	std::vector<int> aux;
	fill_container(aux, 10);
	std::cout << "vector<int> formado:" << std::endl;
	print_container(aux);
	MutantStack<int> a(aux.begin(), aux.end());
	std::cout << "MutantStack<int> formado (lee con iteradores):" << std::endl;
	std::cout << a << std::endl;
	std::cout << "MutantStack<int> reversa (reverse iterators):" << std::endl;
	MutantStack<int>::const_reverse_iterator crit = a.rbegin();
	while (crit != a.rend()){
		if (crit != a.rbegin())
			std::cout << ",";
		std::cout << *crit;
		crit++;
	}
	std::cout << std::endl;
	std::cout << "cambio de valor al segundo elemento (no const iterator)" << std::endl;
	MutantStack<int>::iterator it = a.begin() + 1;
	*it = 32;
	std::cout << a << std::endl;

	//COPY OF MONSTERSTACK
	std::cout << "\nCOPY OF MONSTERSTACK" << std::endl;
	MutantStack<int> b;
	b = a;
	std::cout << "MutantStack<int> b = a" << std::endl;
	std::cout << b << std::endl;
	std::cout << "MutantStack<int> c(b)" << std::endl;
	MutantStack<int> c(b);
	std::cout << c << std::endl;

	//LIST of abcd
	std::cout << "\nMutantStack<char> in a LIST" << std::endl;
	std::list<char> aux2;
	for (char i = 'a'; i != '{'; i++){
		aux2.push_back(i);
	}
	std::cout << "list container:" << std::endl;
	print_container(aux2);
	std::cout << "MutantStack<char> composed but reverse order:" << std::endl;
	MutantStack<char> d(aux2.rbegin(), aux2.rend());
	std::cout << d << std::endl;
	std::cout << "Insert a '?' char and see it with .top()" << std::endl;
	d.push('?');
	std::cout << d << std::endl;
	std::cout << "top must be last pushed. .top() = " << d.top() << std::endl;
	std::cout << "removed with pop now top should be last included so final of the container = a" << std::endl;
	d.pop();
	std::cout << ".top() = " << d.top() << std::endl;
	std::cout << d << std::endl;
	std::cout << "size of d<char>: " << d.size() << std::endl;
	
	return 0;
}


int main(){
	int r;
	int ret;
	
	std::cout << "TESTS -----" << std::endl;
	std::cout << "1. Subject test\n2. Subject test with std::list\n3. My own tests" << std::endl;
	std::cout << "choose an option: ";
	std::cin >> r;
 
	switch (r){
		case 1:
			ret = main_subject();
			break;
		case 2:
			ret = main_list();
			break;
		case 3:
			ret = main_mytests();
			break;
		default:
			break;	
	}
	
	return ret;
}
