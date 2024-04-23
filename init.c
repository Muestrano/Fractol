/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:20:17 by picarlie          #+#    #+#             */
/*   Updated: 2024/04/23 19:36:43 by picarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	malloc_error(void) //static means that this function is only for this file ie no prototype needed in header file
{
	perror("Problems with malloc");
	exit(EXIT_FAILURE);
}

void	data_init(t_fractal *fractal)
{
	fractal->escape_value = 4; // 2 * 2 hypotenuse
	fractal->iterations_definition = 42;
	fractal->shift_x = 0;
	fractal->shift_y = 0;
	fractal->zoom = 0;
}

static void	events_init(t_fractal *fractal)
{
	mlx_hook(fractal->mlx_window, KeyPress, KeyPressMask, key_handler, fractal); //for keyboard
	mlx_hook(fractal->mlx_window, ButtonPress, ButtonPressMask, mouse_handler, fractal); //for mouse
	mlx_hook(fractal->mlx_window, DestroyNotify, StructureNotifyMask, close_handler, fractal); //for "X" top right button
}

/*
Init mlx/listening events/hooks data
*/
void	fractal_init(t_fractal *fractal)
{
	// MLX stuff
	fractal->mlx_connection = mlx_init();
	if (fractal->mlx_connection == NULL)
		malloc_error(); //TODO
	fractal->mlx_window = mlx_new_window(fractal->mlx_connection, WIDTH, HEIGHT, fractal->name);
	if (fractal->mlx_window == NULL)
	{
		mlx_destroy_display(fractal->mlx_connection);
		free(fractal->mlx_connection);
		malloc_error();
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_connection, WIDTH, HEIGHT);
	if (fractal->img.img_ptr == NULL)
	{
		mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
		mlx_destroy_display(fractal->mlx_connection);
		free(fractal->mlx_connection);
		malloc_error();
	}
	fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.img_ptr, &fractal->img.bpp, &fractal->img.line_len, &fractal->img.endian);
	
	events_init(fractal); //==> TODO
	data_init(fractal);
}