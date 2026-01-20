/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:26:56 by jrollon-          #+#    #+#             */
/*   Updated: 2026/01/20 17:04:28 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

template <typename T, typename F> void iter(T *array, const size_t len, F f){
	for (size_t i = 0; i < len; i++)
		f(array[i]);		
}

template <typename T>
void printValues(T& element){
	std::cout << GREEN << element << RESET << ", " << std::endl;
}

template <typename T>
void printValues(const T& element){
	std::cout << GREEN << element << RESET << ", " << std::endl;
}

int	main (void){

	float		num1 = 32.1f, num2 = 0.4f;
	int			intMatrix[] = {3, 423, 2, -34, 0}; //cuidado!! sin = es C++11
	std::string	frases[] 	= {"hola mundo", "como estas ?", "yo bien", ""};
	double		vacio[] 	= {};
	float* 		pFloats[] 	= {&num1, &num2};
	
	size_t	len = sizeof(intMatrix) / sizeof(intMatrix[0]);
	size_t	len2 = sizeof(frases) / sizeof(frases[0]);
	size_t	len3 = sizeof(vacio) / sizeof(vacio[0]);
	size_t	len4 = sizeof(pFloats) / sizeof(pFloats[0]);	

	iter(intMatrix, len, static_cast<void(*)(int&)>(printValues<int>)); //hay que castear, pq si no no sabe cual pillar de las funciones. Se resolveria con un lamda pero es cpp11
	std::cout << std::endl;
	iter(intMatrix, len, static_cast<void(*)(const int&)>(printValues<int>));
	
	std::cout << YELLOW << "-------Con Strings---------" << RESET << std::endl;

	iter(frases, len2, static_cast<void(*)(std::string&)>(printValues<std::string>));
	std::cout << std::endl;
	iter(frases, len2, static_cast<void(*)(const std::string&)>(printValues<std::string>));
	
	std::cout << YELLOW << "-------Con Doubles Vacios---------" << RESET << std::endl;

	iter(vacio, len3, static_cast<void(*)(double&)>(printValues<double>));
	std::cout << std::endl;
	iter(vacio, len3, static_cast<void(*)(const double&)>(printValues<double>));

	std::cout << YELLOW << "-------Con punteros a float---------" << RESET << std::endl;

	iter(pFloats, len4, static_cast<void(*)(float*&)>(printValues<float*>));
	iter(pFloats, len4, static_cast<void(*)(float* const&)>(printValues<float*>)); //NOTA* DE ALGO MUY ROMPEDOR LA CABEZA ABAJO. 

	/*NOTA*:
	Como hemos visto, cuando usamos F f, como parametro podemos meter cualquier cosa, incluso objetos, por ello casteamos. 
	Es como cuando haciamos 
	
	funcion(void parametro){\
		(int)parametro; // o (char)parametro
	}
	
	es decir casteábamos a cualquier tipo dentro de la función y así podíamos aceptar todo tipo de parámetros.
	Entonces cuando tenemos un F a, donde F es un typename (puede ser cualquier tipo) también tenemos que castear a ese tipo para que sepa qué narices
	estamos tratando de usar. No pasaría nada si tuvíeramos una única funcion "printValues" y podriamos hacer:
	
	ter(intMatrix, len, printValues<int>);

	pero en nuestro caso está duplicada (overload) y por lo tanto aquí sí que tenemos que castear a qué tipo es para que detecte que se va a pasar un
	parámetro const o no const.
	El lio de "NOTA*" viene cuando se invierte el orden de a lo que se va a castear. Me explico:

	si tenemos un int como "intMatrix", el casteo para este template:

	template <typename T>
	void printValues(const T& element);

	iter(intMatrix, len, static_cast<void(*)(const int&)>(printValues<int>));

	es decir void(*)(int&) donde puede parecer que SUSTITUIMOS:

	T = int
	por lo tanto -> const T& = const int&

	y como vemos funciona.... PEROOOOOOOOOOOOOOOOOOOOOOOOOOO EN PUNTEROOOOOSSS la cosa es muy diferente:

	Para la misma plantilla (template) si en este caso tenemos:

	T = float* es decir punteros a float.

	la sustitución podríamos pensar que es:

	const T& = const float*& PERO NOO!!!!!!!!!!!!!!

	sería: 

	const T& = float* const& porque...

	... si tenemos 
	const float* p -> ese const dice que se puede sustituir la dirección de memoria, pero no el valor de dicha dirección de memoria
	mientras que 
	float* const p -> No podemos cambiar el valor de la dirección de memoria almacenada en "p" pero sí el valor que apunta (*p)

	en nuestro caso es un const T& es decir, una refencia a un tipo que tiene que ser constante. Es el tipo el que no puede cambiar, y si hacemos

	const float*& podríamos cambiar los valores almacenados de ese tipo.. es decir punteros a float.
	Si la matriz que nos pasan son dos direcciones de memoria, queremos conservar dicha dirección de memoria SIEMPRE es decir esos valores de dirección
	de memoría (memoria casilla 1, memoria casilla 29) tienen que ser siempre los mismos, y la firma:

	iter(pFloats, len4, static_cast<void(*)(const float*&)>(printValues<float*>)); //const float*&
	haría que podria cambiar, por que lo único constante es lo que almacenan dichas direcciones de memoria

	así:
	iter(pFloats, len4, static_cast<void(*)(float* const&)>(printValues<float*>)); //float* const& sí que se mantiene constante dichas direcciones de memoria.
	*/
		
	return (0);
}


