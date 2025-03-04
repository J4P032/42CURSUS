/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:09:02 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/04 11:43:36 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx-linux/mlx.h"

int main(void)
{
    void *mlx;
    void *win;

    mlx = mlx_init();
    if (!mlx)
        return (1);

    win = mlx_new_window(mlx, 800, 600, "Mi Ventana");
    if (!win)
        return (1);

    mlx_loop(mlx);
    return (0);
}
