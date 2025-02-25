/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:05:07 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/18 12:40:25 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*converts from string to number int*/
int	ft_atoi(const char *nptr)
{
	int	result;
	int	minus;
	int	i;

	minus = 1;
	i = 0;
	result = 0;
	while (nptr[i] != 0 && ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == 32))
		i++;
	if (nptr[i] != '\0' && (nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			minus = -1;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (minus * result);
}
