/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:52:19 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/22 13:13:58 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Checks if the char passed is alphanumeric number (0-9) (a-z) (A-Z)*/
int	ft_isalnum(int c)
{
	if (c < '0')
		return (0);
	if ((c > '9') && (c < 'A'))
		return (0);
	if ((c > 'Z') && (c < 'a'))
		return (0);
	if (c > 'z')
		return (0);
	return (1);
}
