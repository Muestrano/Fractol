/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:16:26 by picarlie          #+#    #+#             */
/*   Updated: 2024/04/23 19:56:08 by picarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
	To run when ESC or X button
	int (*f)(void *param)
*/
int	close_handler(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_connection, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
	mlx_destroy_display(fractal->mlx_connection);
	free(fractal->mlx_connection);
	exit(EXIT_SUCCESS);
}

/*
	Keypress prototype
	int (*f)(int keycode, void *param)
*/
int	key_handler(int keysym, t_fractal *fractal) //Difference between keycode (hardware, physical keyborad) and keysym (the symbol or function)
{
	printf("%d\n", keysym);
	//(void)fractal;

	if (keysym == XK_Escape)
			close_handler(fractal); //todo
	if (keysym == XK_Left)
		fractal->shift_x -= 0.10;
	else if (keysym == XK_Right)
		fractal->shift_x += 0.10;
	else if (keysym == XK_Up)
		fractal->shift_y += 0.10;
	else if (keysym == XK_Down)
		fractal->shift_y -= 0.10;
	else if (keysym == 61 || keysym == 65451) // XK_plus doesnt work
		fractal->iterations_definition += 10;
	else if (keysym == XK_minus || keysym == 65453)
		fractal->iterations_definition -= 10;
	fractal_render(fractal); // refresh img
	return (0);
}

/*
	int (*f)(int button, int x, int y, void *param)
*/
int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	if (button == Button5)
	{
		fractal->zoom += 0.3;
	}
	else if (button == Button4)
	{		
		fractal->zoom -= 0.3;
	}
	printf("%d\n", button); // 4 || Button5 to zoom in, 5 || Button4 to zoom out
	(void)x;
	(void)y;
	fractal_render(fractal);
	return (0);
}
