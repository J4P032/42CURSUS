/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:55:36 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/07 11:59:04 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isdigit(int c)
{
	return (('0' <= c) && (c <= '9'));
}

static int	ft_isupper(int c)
{
	return ((c >= 'A') && (c <= 'Z'));
}

static int	ft_islower(char c)
{
	return ((c >= 'a') && (c <= 'z'));
}


int	ft_atoi_base(const char *str, int base)
{
    int sign;
    int result;

    sign = 1;
    result = 0;

    if (*str == '-')
    {
        sign = -1;
        str++;
    }

    while (*str)
    {
        result *= base;

        if (ft_isdigit(*str))
            result += (*str - '0');
        else if (ft_isupper(*str))
            result += (*str - 'A' + 10);  // 'A' debe representar 10
        else if (ft_islower(*str))
            result += (*str - 'a' + 10);  // 'a' debe representar 10

        str++;
    }

    return (result * sign);
}
