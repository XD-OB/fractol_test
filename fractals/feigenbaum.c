/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feigenbaum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 11:09:01 by obelouch          #+#    #+#             */
/*   Updated: 2019/02/10 23:50:30 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int		ffillz(t_graphic *ptr, int *ind, t_complex *z)
{
	z[1].re = pow((pow(z[0].re, 2) + pow(z[0].im, 2)),
			((ptr->m_puis - 1) / 2.0)) * cos((ptr->m_puis - 1)
			* atan2(z[0].im, z[0].re)) + z[2].re - 1.401155;
	z[1].im = pow((pow(z[0].re, 2) + pow(z[0].im, 2)),
			((ptr->m_puis - 1) / 2.0)) * sin((ptr->m_puis - 1)
			* atan2(z[0].im, z[0].re)) + z[2].im;
	if (z[1].re == z[0].re && z[1].im == z[0].im)
	{
		ind[2] = ptr->max_iter;
		return (1);
	}
	z[0] = z[1];
	return (0);
}

static void		fput_in(t_graphic *ptr, int *ind, t_complex c)
{
	if (ind[2] < ptr->max_iter)
		img_put_pixel(ptr, ind[1], ind[0], outer(*ptr, ind[2]));
	else
		img_put_pixel(ptr, ind[1], ind[0], inner(*ptr, ind[2], c));
}

static void		*part_feigen(void *varg)
{
	t_fractol	*f;
	t_complex	z[4];
	int			ind[3];

	f = (t_fractol*)varg;
	ind[0] = ((HEIGHT * (f->div - 1)) / DIV) - 1;
	while (++ind[0] < (HEIGHT * f->div) / DIV)
	{
		z[3].im = ind[0] / f->ptr->zoom + (f->mouse).y;
		ind[1] = -1;
		while (++ind[1] < WIDTH)
		{
			z[3].re = ind[1] / f->ptr->zoom + (f->mouse).x;
			z[2].re = pow(z[3].re, 3) - 3 * z[3].re * z[3].im * z[3].im;
			z[2].im = 3 * z[3].re * z[3].re * z[3].im - pow(z[3].im, 3);
			z[0] = complex(0, 0);
			ind[2] = -1;
			while (mod2(z[0]) < 4 && ++ind[2] < f->ptr->max_iter)
				ffillz(f->ptr, ind, z);
			fput_in(f->ptr, ind, z[0]);
		}
	}
	return (NULL);
}

void			feigenbaum(t_fractol *f)
{
	int			ind[2];
	t_fractol	*tmp;
	pthread_t	id[DIV];

	tmp = (t_fractol*)malloc(sizeof(t_fractol) * DIV);
	ind[0] = -1;
	while (++ind[0] < DIV)
	{
		tmp[ind[0]] = *f;
		tmp[ind[0]].div = ind[0] + 1;
	}
	ind[1] = -1;
	ind[0] = -1;
	while (++ind[0] < DIV)
		pthread_create(&id[ind[0]], NULL, part_feigen, (void*)(&tmp[ind[0]]));
	while (++ind[1] < DIV)
		pthread_join(id[ind[1]], NULL);
	free(tmp);
}
