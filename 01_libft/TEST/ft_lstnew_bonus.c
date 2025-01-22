/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:32:48 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/22 13:33:09 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*returns a new node with 'content' in it. But don't join it to anything*/
t_list	*ft_lstnew(void *content)
{
	t_list	*lnew;

	lnew = (t_list *)malloc(sizeof(t_list));
	if (!lnew)
		return (NULL);
	lnew->content = content;
	lnew->next = NULL;
	return (lnew);
}
