/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 11:09:27 by obelouch          #+#    #+#             */
/*   Updated: 2019/02/04 11:09:36 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	*part_mandel(void *varg)
{
	t_fractol		*r;
	t_complex	c;
	t_complex	z[2];
	int	k;
	double	ind[2];

	r = (t_fractol*)varg;
	ind[0] = (HEIGHT * (r->p - 1)) / DIV;
	while (ind[0] < (HEIGHT * r->p) / DIV)
	{
		c.im = ind[0] / r->ptr->zoom + (r->mouse).y;
		ind[1] = (WIDTH * (r->q - 1)) / DIV;
		while (ind[1] < (WIDTH * r->q) / DIV)
		{
			c.re = ind[1] / r->ptr->zoom + (r->mouse).x;
			z[0] = complex(0, 0);
			k = -1;
			while (z[0].re * z[0].re + z[0].im * z[0].im < 4 && ++k < r->ptr->max_iter)
			{
				z[1].re = z[0].re * z[0].re - z[0].im * z[0].im + c.re;
				z[1].im = 2 * z[0].re * z[0].im + c.im;
				if (z[1].re == z[0].re && z[1].im == z[0].im)
					{
						k = r->ptr->max_iter;
						break ;
					}
				z[0] = z[1];
			}
			if (k < r->ptr->max_iter)
				img_put_pixel(r->ptr, ind[1], ind[0], design_color(*(r->ptr), k));
			else
				img_put_pixel(r->ptr, ind[1], ind[0], intern_color(*(r->ptr), k, z[0]));
			ind[1]++;
		}
		ind[0]++;
	}
	return (NULL);
}
void	mandelbrot(t_fractol *r)
{
	int		ind[3];
	t_fractol		*tmp;
	pthread_t	id_thread[DIV * DIV];

	tmp = (t_fractol*)malloc(sizeof(t_fractol) * DIV * DIV);
	ind[0] = -1;
	while(++ind[0] < DIV * DIV)
		tmp[ind[0]] = *r;
	ind[0] = 0;
	while(++ind[0] <= DIV)
	{
		ind[1] = 0;
		while(++ind[1] <= DIV)
		{
			tmp[((ind[0] - 1) * DIV) + (ind[1] - 1)].p = ind[0];
			tmp[((ind[0] - 1) * DIV) + (ind[1] - 1)].q = ind[1];
		}
	}
	ind[2] = -1;
	ind[0] = -1;
	while(++ind[0] < DIV * DIV)
		pthread_create(&id_thread[ind[0]], NULL, part_mandel, (void*)(&tmp[ind[0]]));
	while(++ind[2] < DIV * DIV)
		pthread_join(id_thread[ind[2]], NULL);
	free(tmp);
}
