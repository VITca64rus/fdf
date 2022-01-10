/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazelda <sazelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:57:28 by sazelda           #+#    #+#             */
/*   Updated: 2022/01/10 20:26:13 by sazelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

#define MAX(a, b) (a > b ? a : b)
#define MOD(a) (a < 0 ? -a : a)

void ft_3d(float *x, float *y, int z, t_fdf *data)
{
	*x = (*x - *y) * cos(data->angle);
	*y = (*x + *y) * sin(data->angle) - z;
}

static void	ft_bresenham(float x, float y, float x1, float y1, t_fdf *data)
{
	float	x_step;
	float	y_step;
	int		max;
	int		z;
	int		z1;

	data->color = data->matrix[(int)y][(int)x]->color;
	if (data->color == 0)
	{
		data->color = 267386880;
	}
	z = data->matrix[(int)y][(int)x]->z * 10;
	z1 = data->matrix[(int)y1][(int)x1]->z * 10;
	x *= data->zoom;
	y *= data->zoom;
	x1 *= data->zoom;
	y1 *= data->zoom;
	ft_3d(&x, &y, z, data);
	ft_3d(&x1, &y1, z1, data);

	x += data->shift_x;
	y += data->shift_y;
	x1 += data->shift_x;
	y1 += data->shift_y;

	x_step = x1 - x;
	y_step = y1 - y;
	max = MAX(MOD(x_step), MOD(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(x - x1) || (int)(y - y1))
	{
		//max = ft_get_int(data->color_matrix[(int)y][(int)x]);
		if (max == 0)
		{
			max = 0xffffff;
		}
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, data->color);
		x += x_step;
		y += y_step;
	}
}

void	draw(t_fdf *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			if (j < data->width - 1)
				ft_bresenham(j, i, j + 1, i, data);
			if (i < data->height - 1)
				ft_bresenham(j, i, j, i + 1, data);
			j++;
		}
		i++;
	}
}
