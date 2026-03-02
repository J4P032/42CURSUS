/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_tree_bag.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 12:03:17 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/02 16:20:43 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEARCHABLE_TREE_BAG_HPP
# define SEARCHABLE_TREE_BAG_HPP

# include "tree_bag.hpp"
# include "searchable_bag.hpp"
# include <iostream>

class searchable_tree_bag : public tree_bag, public searchable_bag{
public:	
	searchable_tree_bag(void) : tree_bag(){}
	searchable_tree_bag(const searchable_tree_bag& other) : tree_bag(other){}
	searchable_tree_bag& operator=(const searchable_tree_bag& other){
		tree_bag::operator=(other);
		return (*this);
	}
	virtual ~searchable_tree_bag(void){}

	bool has(int num) const{
		node	*aux;
		aux = tree;
		while (aux != NULL){
			if (num == aux->value)
				return (true);
			if (num < aux->value)
				aux = aux->l;
			else
				aux = aux->r;	
		}
		return (false);
	}
};

#endif
