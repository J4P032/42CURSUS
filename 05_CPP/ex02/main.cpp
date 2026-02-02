/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:36:12 by jrollon-          #+#    #+#             */
/*   Updated: 2026/01/26 15:00:17 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

int main() {
    try{
        Array<int> a(3);
        std::cout << "---------------- INT ----------------" << std::endl;
        std::cout << a[1] << std::endl;
        std::cout << a << std::endl;
        a[0] = 32;
        a[1] = 42;
        a[2] = -1;
        
        Array<std::string> b(3);
        b[0] = "hola";
        b[1] = "mundo !";
        b[2] = "que tal?";
        
        double  da = 32.3;
        double  db = 0.23;
        double* p_da = &da;
        double* p_db = &db;
        Array<double*> p_c(3);
        p_c[0] = p_da;
        p_c[1] = p_db;
        
        Array<float> c;
        
        
        std::cout << "---------------- INT despues----------------" << std::endl;
        std::cout << a[1] << std::endl;
        std::cout << a << std::endl;
        
        std::cout << "---------------- std::string ----------------" << std::endl;
        std::cout << b[1] << std::endl;
        std::cout << b << std::endl;
        
        std::cout << "---------------- punteros double ----------------" << std::endl;
        std::cout << p_c[1] << std::endl;
        std::cout << p_c << std::endl;
        
        std::cout << "---------------- array vacio ----------------" << std::endl;
        std::cout << c[1] << std::endl;
        std::cout << c << std::endl;
    }
    catch(std::exception &ex){
        std::cerr << "Exception: " << ex.what() << std::endl;
    }
    return (0);
}

/* #include <iostream>
#include "Array.hpp"
#include <cstdlib>  // Para srand, rand
#include <ctime>    // Para time


#define MAX_VAL 750
int main(int, char**)
{
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    //SCOPE
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    delete [] mirror;//
    return 0;
} */

