/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:01:20 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/22 13:14:02 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*checks if the char passed is a alphabetic (A-Z, a-z)*/
int	ft_isalpha(int c)
{
	if (c < 'A')
		return (0);
	if ((c > 'Z') && (c < 'a'))
		return (0);
	if (c > 'z')
		return (0);
	return (1);
}
