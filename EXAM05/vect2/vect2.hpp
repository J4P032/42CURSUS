/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:56:46 by jrollon-          #+#    #+#             */
/*   Updated: 2026/02/27 18:30:57 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT2_HPP
# define VECT2_HPP

# include <iostream>

class	vect2{
public:
//CANONICA
	vect2(void) : _x(0), _y(0){}

	vect2(int x, int y) : _x(x), _y(y){}

	vect2(const vect2& other) : _x(other._x), _y(other._y){}

	vect2& operator=(const vect2& other){
		_x = other._x;
		_y = other._y;
		return (*this);
	}

	~vect2(void){}

	
//[]

	int	operator[](int n) const{
		int valor;
		if (n == 0)
			valor = _x;
		else
			valor = _y;
		return (valor);
	}

	int& operator[](int n){
		return (n == 0 ? _x : _y);
	}

//+=
	vect2 operator+(const vect2& other) const{
		return (vect2(_x + other._x, _y + other._y));
	}

	vect2& operator+=(const vect2& other){
		_x += other._x;
		_y += other._y;
		return (*this);
	}

	vect2& operator+=(int n){
		_x += n;
		_y += n;
		return (*this);
	}

//-=

	vect2 operator-(const vect2& other) const{
		return (vect2(_x - other._x, _y - other._y));
	}

	vect2& operator-=(const vect2& other){
		_x -= other._x;
		_y -= other._y;
		return (*this);
	}

	vect2& operator-=(int n){
		_x -= n;
		_y -= n;
		return (*this);
	}

//*
	vect2 operator*(int n) const{
		return (vect2(_x * n, _y * n));
	}

	vect2& operator*=(int n){
		_x *= n;
		_y *= n;
		return (*this);
	}


//==
	bool operator==(const vect2& other) const{
		return (_x == other._x && _y == other._y);
	}

	bool operator!=(const vect2& other) const{
		return !(*this == other);
	}

//++
	//++a
	vect2& operator++(){
		_x++;
		_y++;
		return (*this);
	}
	//a++
	vect2 operator++(int){
		vect2 temp(*this);
		++(*this);
		return (temp);
	}

//--
	//--a
	vect2& operator--(){
		_x--;
		_y--;
		return (*this);
	}
	//a--
	vect2 operator--(int){
		vect2 temp(*this);
		--(*this);
		return (temp);
	}	

//GETTERS
	int	get_x(void) const{
		return (_x);
	}

	int	get_y(void) const{
		return (_y);
	}

//PRIVATES
private:
	int	_x;
	int	_y;
};

std::ostream& operator<<(std::ostream& out, const vect2& v){
	out << "{" << v[0] << ", " << v[1] << "}" << std::endl;
	return (out); 
}

vect2 operator*(int n, const vect2& other){
	return (other * n);
}


#endif
