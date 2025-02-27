/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:49:53 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/27 13:50:48 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int     ft_recursive_power(int nb, int power)
{
        if (power > 0)
                nb = nb * ft_recursive_power(nb, (power - 1));
        if (power == 0)
                return (1);
        if (power < 0)
                return (0);
        return (nb);
}

int     ft_sqrt(int nb)
{
        int     i;

        i = 0;
        while (ft_recursive_power(i, 2) < nb)
                i++;
        if (ft_recursive_power(i, 2) == nb)
                return (i);
        else
                return (0);
}
