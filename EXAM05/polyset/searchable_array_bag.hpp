/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_array_bag.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 12:02:02 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/02 14:30:57 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEARCHABLE_ARRAY_BAG_HPP
# define SEARCHABLE_ARRAY_BAG_HPP

# include "array_bag.hpp"
# include "searchable_bag.hpp"

class searchable_array_bag : public array_bag, public searchable_bag{
public:
	searchable_array_bag(void) : array_bag() {}
	searchable_array_bag(const searchable_array_bag& other) : array_bag(other) {}
	searchable_array_bag& operator=(const searchable_array_bag& other){
		array_bag::operator=(other);
		return (*this);
	}
	virtual ~searchable_array_bag(void){}

	bool has(int num) const{
		for (int i = 0; i < size; i++){
			if (num == data[i])
				return (true);
		}
		return (false);
	}
};


#endif
