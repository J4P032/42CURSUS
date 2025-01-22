/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:55:26 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/22 13:37:11 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*Writes the 'c' given character through 'fd' given*/
void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}
