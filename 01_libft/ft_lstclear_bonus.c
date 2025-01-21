/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:44:11 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/21 20:49:40 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*aux;

	if (!*lst || !lst)
		return ;
	while (*lst)
	{
		aux = (*lst)->next;
		if (del)
			del((*lst)->content);
		free(*lst);
		*lst = aux;
	}
	*lst = NULL;
}

/*
   t_list *current;
    t_list *next;

    if (!lst || !*lst)
        return;

    current = *lst;
    while (current)
    {
        next = current->next;    // Guarda el siguiente antes de borrar
        if (del)
            del(current->content);  // Borra el contenido
        free(current);           // Borra el nodo actual
        current = next;          // Avanza al siguiente
    }
    *lst = NULL;                // Al final, pone el puntero a NULL
 */
