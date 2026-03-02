/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_tree_bag.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 12:03:17 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/02 13:04:40 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEARCHABLE_TREE_BAG_HPP
# define SEARCHABLE_TREE_BAG_HPP

# include "tree_bag.hpp"
# include "searchable_bag.hpp"

class searchable_tree_bag : public tree_bag, public searchable_bag{
	searchable_tree_bag(void) : tree_bag(){}
	searchable_tree_bag(const searchable_tree_bag& other) : tree_bag(other){}
	searchable_tree_bag& operator=(const searchable_tree_bag& other){
		tree_bag::operator=(other);
		return (*this);
	}
	virtual ~searchable_tree_bag(void){}

	bool has(int num) const{
		node	aux;
		if (num < tree->value)
			aux = tree->l;
		
		while (node != NULL){
			

		}
	}
	

	/* struct node {
    node *l;
    node *r;
    int value;
  };
  node *tree; */
	
};


#endif
