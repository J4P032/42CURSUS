/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:32:21 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/07 17:44:42 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Fixed.hpp"

#include <iostream>
int main( void ) {
Fixed a;
Fixed const c(5.05f);
Fixed const d(2);
Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
std::cout << a << std::endl;
std::cout << ++a << std::endl;
std::cout << a << std::endl;
std::cout << a++ << std::endl;
std::cout << a << std::endl;
std::cout << b << std::endl;
std::cout << Fixed::max( a, b ) << std::endl;

std::cout << std::endl;
std::cout << "****** My Tests ******" << std::endl;
float		fnum = 3.013f;
int			num = 7;

Fixed const f1(fnum);
Fixed const f2(num);
std::cout << "fnum: " << fnum << " | num: " << num << std::endl;
std::cout << "fnum + num = " << (fnum + num) << " | f1 + f2 = " << (f1 + f2) << std::endl;
std::cout << "fnum - num = " << (fnum - num) << " | f1 - f2 = " << (f1 - f2) << std::endl;
std::cout << "fnum * num = " << (fnum * num) << " | f1 * f2 = " << (f1 * f2) << std::endl;
std::cout << "fnum / num = " << (fnum / num) << " | f1 / f2 = " << (f1 / f2) << std::endl;

std::cout << std::endl;
std::cout << "****** overflows ******" << std::endl;
fnum = 2147483640.3f;
float fnum2 = 0.01f;

Fixed const f3(fnum);
Fixed const f4(fnum2);
std::cout << "fnum: " << fnum << " | fnum2: " << fnum2 << std::endl;
std::cout << "fnum + fnum2 = " << (fnum + fnum2) << " | f3 + f4 = " << (f3 + f4) << std::endl;
std::cout << "fnum - fnum2 = " << (fnum - fnum2) << " | f3 - f4 = " << (f3 - f4) << std::endl;
std::cout << "fnum * fnum2 = " << (fnum * fnum2) << " | f3 * f4 = " << (f3 * f4) << std::endl;
std::cout << "fnum / fnum2 = " << (fnum / fnum2) << " | f3 / f4 = " << (f3 / f4) << std::endl;

std::cout << std::endl;
std::cout << "****** Cero ******" << std::endl;
fnum = 0.0f;
fnum2 = 0.01f;

Fixed const f5(fnum);
Fixed const f6(fnum2);
std::cout << "fnum: " << fnum << " | fnum2: " << fnum2 << std::endl;
std::cout << "fnum + fnum2 = " << (fnum + fnum2) << " | f5 + f6 = " << (f5 + f6) << std::endl;
std::cout << "fnum - fnum2 = " << (fnum - fnum2) << " | f5 - f6 = " << (f5 - f6) << std::endl;
std::cout << "fnum * fnum2 = " << (fnum * fnum2) << " | f5 * f6 = " << (f5 * f6) << std::endl;
std::cout << "fnum / fnum2 = " << (fnum / fnum2) << " | f5 / f6 = " << (f5 / f6) << std::endl;


std::cout << std::endl;
std::cout << "****** Division by Cero ******" << std::endl;
fnum = 0.01f;
num = 0;

Fixed const f7(fnum);
Fixed const f8(num);
std::cout << "fnum: " << fnum << " | fnum2: " << num << std::endl;
std::cout << "fnum + fnum2 = " << (fnum + num) << " | f7 + f8 = " << (f7 + f8) << std::endl;
std::cout << "fnum - fnum2 = " << (fnum - num) << " | f7 - f8 = " << (f7 - f8) << std::endl;
std::cout << "fnum * fnum2 = " << (fnum * num) << " | f7 * f8 = " << (f7 * f8) << std::endl;
std::cout << "fnum / fnum2 = " << (fnum / num) << " | f7 / f8 = " << (f7 / f8) << std::endl;

fnum = 4.0f;
fnum2 = 4.1f;
Fixed const f9(fnum);
Fixed const f10(fnum2);
std::cout << fnum << " > " << fnum2 << " " << (f9 > f10) << std::endl;
std::cout << fnum << " < " << fnum2 << " " << (f9 < f10) << std::endl;
std::cout << fnum << " == " << fnum2 << " " << (f9 == f10) << std::endl;

fnum = 5.0f;
num = 5;
Fixed const f11(fnum);
Fixed const f12(num);
std::cout << fnum << " > " << num << " " << (f11 > f12) << std::endl;
std::cout << fnum << " < " << num << " " << (f11 < f12) << std::endl;
std::cout << fnum << " == " << num << " " << (f11 == f12) << std::endl;

return 0;
}

/* $> ./a.out
0
0.00390625
0.00390625
0.00390625
0.0078125
10.1016
10.1016
$>
puede crashear el programa si se hace / 0 */
