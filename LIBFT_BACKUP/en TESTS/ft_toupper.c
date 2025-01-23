/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:08:01 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/22 14:33:51 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*will return 'c' char to upper if it is lower. If not will leave it as it is*/
int	ft_toupper(int c)
{
	if ((c >= 'a') && (c <= 'z'))
		return (c - 32);
	else
		return (c);
}
