/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:45:46 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/22 13:20:37 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*removes the node pointed by 'lst' with function 'del'*/
/*aux node will point to next node to remove*/
/*copy content of aux = next node to lst, free(aux)*/
/*A-B-C del(B)>Aux=C > B = AUX > del(aux) = B = C = A-C*/
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del)
		del(lst->content);
	free(lst);
}
