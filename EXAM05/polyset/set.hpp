/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:21:55 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/02 15:31:57 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

#include "searchable_bag.hpp"
#include <iostream>


class	set{
public:
	set(void){}
	set(searchable_bag&	bag) : _bag(&bag){}
	set(const set& other) : _bag(other._bag){}
	set& operator=(const set& other){
		_bag = other._bag;
		return (*this);
	}
	~set(void){}

	void	insert(int num){
		if (!_bag->has(num))
			_bag->insert(num);
	}

	void	insert(int* arr, int n){
		for (int i = 0; i < n; i++)
			insert(arr[i]);
	}

	void	print(){
		_bag->print();
	}

	void	clear(){
		_bag->clear();
	}

	searchable_bag&	get_bag() const{
		return (*_bag);
	}

	bool	has(int num) const{
		return _bag->has(num);
	}
	
private:
	searchable_bag* _bag;
	
};


#endif
