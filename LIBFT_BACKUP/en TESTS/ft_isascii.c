/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:02:42 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/22 13:14:07 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*check if the char passed is betwen 0 and 127 in ascii table*/
int	ft_isascii(int c)
{
	if ((c >= 0) && (c <= 127))
		return (1);
	else
		return (0);
}
