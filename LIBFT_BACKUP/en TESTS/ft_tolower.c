/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:28:39 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/22 14:33:11 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*turns 'c' char into lowercase if it is upper. If not will leave it as it is*/
int	ft_tolower(int c)
{
	if ((c >= 'A') && (c <= 'Z'))
		return (c + 32);
	else
		return (c);
}
