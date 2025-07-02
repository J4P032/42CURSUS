/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:02:47 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/02 16:49:59 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>

std::string	SubstituteString(std::string &myLine, char *s1, char *s2, size_t pos)
{
	std::string	searchStr	= std::string(s1);
	std::string substStr	= std::string(s2);
	size_t		length_s1	= searchStr.length();

	myLine.erase(pos, length_s1);
	myLine.insert(pos, substStr);

	//No necesita if pos < myLine.length() antes por que ya esta protegido el metodo
	size_t position = myLine.find(s1, pos + 1);
	if (position == std::string::npos){
		return (myLine);
	}
	else{
		return (SubstituteString(myLine, s1, s2, position));
	}
}

int	main(int argc, char **argv)
{
	size_t		position;
	std::string	myLine;

	//chequea que el numero de argumentos es correcto
	if (argc != 4){
		std::cout << "Usage: ./losers filename string1 string2" << std::endl;
		return (1);
	}
	
	//abre el archivo en argv[1]
	std::ifstream sourceFile(argv[1]);
	if(!sourceFile.is_open()){
		std::cerr << "Error: Cannot open file\n";
		return (1);
	}
	
	//crea el archivo para sustituir el de origen
	std::string nameDestFile = std::string(argv[1]) + ".replace";
	std::ofstream	destFile(nameDestFile.c_str());
	if(!destFile.is_open()){
		std::cout << "Error: Cannot open destiny file\n";
		return (1);
	}

	/*busca argv[2] dentro de myLine si no lo encuentra position == std::string::npos*/	
	/*Si lo encuentra el "position" sera el primer indice encontrado. Hay que buscar si hay mas*/
	while (std::getline(sourceFile, myLine)){
		position = myLine.find(argv[2]);
		if (position != std::string::npos){
			myLine = SubstituteString(myLine, argv[2], argv[3], position);
		}
		destFile << myLine << "\n";
	}
	
	//cerramos los archivos abiertos
	destFile.close();
	sourceFile.close();
	return (0);
}
