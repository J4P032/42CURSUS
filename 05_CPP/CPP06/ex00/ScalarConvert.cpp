/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConvert.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 11:51:49 by jrollon-          #+#    #+#             */
/*   Updated: 2026/01/13 14:44:50 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <limits>

ScalarConverter::ScalarConverter(void){};

ScalarConverter::ScalarConverter(const ScalarConverter &other){
	(void)other;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other){
	(void)other;
	return (*this);
}

ScalarConverter::~ScalarConverter(void){}

bool	isDigit(char c){
	if (c > 47 && c < 58)
		return (true);
	return (false);
}

//parseo

size_t	ft_strlen(const char *line){
	size_t i = 0;

	while (line[i])
		i++;
	return (i);
}

bool	ft_isValidLine(const std::string &line){
	size_t		i = 0;
	const char	*c_line = line.c_str();
	int			num_decimals = 0;
	size_t		numChars = ft_strlen(c_line);
	
	if (!c_line[0])
		return (false);
	if (numChars == 1)
		return (true);
	while (c_line[i]){
		if (i == 0 && (c_line[i] == '-' || c_line[i] == '+')) { //casos con signo al principio
			i++;
			continue;
		}
		if (!isDigit(c_line[i])){
			if (c_line[i] == '.' && num_decimals < 1){ //si hay un decimal ok, si mas, chungo.
				num_decimals++;
				i++;
				continue ;
			}
			if(c_line[i] == 'f' && !c_line[i + 1]) //si es el penultimo char de la linea y es 'f' de float, ok
				return (true);
			return(false);
		}
		i++;
	}
	return (true);
}

bool	ft_isValidChar(const std::string &line, bool isValidLine){
	size_t		i = 0;
	const char	*c_line = line.c_str();

	while (c_line[i] && isValidLine)
		i++;
	if (i == 1 && !isDigit(c_line[0]))
		return(true);
	return(false);
}

int	seeRares(const std::string &line){
	std::string	cases[] = {"-inf", "-inff", "+inf", "+inff", "nan", "nanf", "inf", "inff"};
	for (size_t i = 0; i < 8; i++){
		if (line == cases[i])
			return(i);
	}
	return(8); //sale de rango
}

void	printRare(int index){
	switch (index){
		case 0:
			std::cout << "-inf";
			break;
		case 1:
			std::cout << "-inf";
			break;
		case 2:
			std::cout << "+inf";
			break;
		case 3:
			std::cout << "+inf";
			break;
		case 4:
			std::cout << "nan";
			break;
		case 5:
			std::cout << "nan";
			break;
		case 6:
			std::cout << "inf";
			break;
		case 7:
			std::cout << "inf";
		default:
			break;
	}
}

void	printChar(int inum, int index, bool isValidLine, bool isIntOverflow){
	bool	impossible = false;
	if (index < 8) //casos extremos
		impossible = true;
	if (inum < 0 || inum > 127) //casos fuera de ascii
		impossible = true;
	
	std::cout << "char: ";
	if (impossible || !isValidLine || isIntOverflow){  
		std::cout << "impossible" << std::endl;
		return ;
	}
	if (inum > 31 && inum < 127)
		std::cout << "'" << static_cast<char>(inum) << "'"; 
	else
		std::cout << "Non displayable";
	std::cout << std::endl;
}

void printInt(int inum, int index, bool isValidLine, bool isIntOverflow){
	bool	impossible = false;
	if (index < 8) //casos extremos
		impossible = true;
	std::cout << "int: ";
	if (impossible || !isValidLine || isIntOverflow){
		std::cout << "impossible" << std::endl;
		return ;
	}
	if (index == 8)
		std::cout << static_cast<int>(inum);
	std::cout << std::endl;
}

void printFloat(float fnum, int index, bool isValidLine){
	std::cout << "float: ";
	
	printRare(index);
	if (index == 8 && isValidLine){
		//std::cout << std::fixed << static_cast<float>(fnum); //float tiene 7 digitos de precision double 15, por lo tanto en std::fixed redondeara en float
		std::cout << static_cast<float>(fnum);
		if (fnum == static_cast<int>(fnum)) //para el caso de input 42.0f si no saldra 42f
			std::cout << ".0";
	}
	if (!isValidLine && index == 8){
		std::cout << "impossible";
		std::cout << std::endl;
		return ;
	}
	std::cout << "f";
	std::cout << std::endl;
}

void	printDouble(double dnum, int index, bool isValidLine){
	std::cout << "double: ";
	
	printRare(index);
	if (index == 8 && isValidLine){
		//std::cout << std::fixed << static_cast<double>(dnum);
		std::cout << static_cast<double>(dnum);
		if (dnum == static_cast<int>(dnum)) //para el caso de input 42.0 si no saldra 42
			std::cout << ".0";
	}
	if (!isValidLine && index == 8)
		std::cout << "impossible";
	std::cout << std::endl;
}

void ScalarConverter::convert(const std::string &line){
	bool 	isValidLine = ft_isValidLine(line);
	bool	isValidChar = ft_isValidChar(line, isValidLine);
	bool	isIntOverflow = false;
	
	int		index = seeRares(line); //check si es nan, nanf, +inf, etc...
	if (!isValidChar){ //si es un numero valido
		double	dnum = std::strtod(line.c_str(), NULL); //to double para comparar con limites overflow
		int		inum = std::atoi(line.c_str());
		float	fnum = std::atof(line.c_str());
		
		if (dnum > std::numeric_limits<int>::max() || dnum < std::numeric_limits<int>::min())
			isIntOverflow = true;
		
		printChar(inum, index, isValidLine, isIntOverflow);
		printInt(inum, index, isValidLine, isIntOverflow);
		printFloat(fnum, index, isValidLine);
		printDouble(dnum, index, isValidLine);
	}
	else{ //si es solo un character imprimible el argumento pasado.
		const char	*c_line = line.c_str();
		printChar(static_cast<int>(c_line[0]), index, isValidLine, isIntOverflow);
		printInt(static_cast<int>(c_line[0]), index, isValidLine, isIntOverflow);
		printFloat(static_cast<int>(c_line[0]), index, isValidLine);
		printDouble(static_cast<int>(c_line[0]), index, isValidLine);
	}
}
