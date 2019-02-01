#include "fractol.h"

static void	part_feigen(t_graphic ptr, int p, int q)
{
	t_complex	tmp;
	t_complex	c;
	t_complex	z;
	t_complex	z1;
	int	k;
	int	i;
	int	j;

	i = (HEIGHT * (p - 1)) / DIV;
	while (i < (HEIGHT * p) / DIV)
	{
		tmp.im = (i - HEIGHT/2.0) * 4/WIDTH * ptr.zoom;
		j = (WIDTH * (q - 1)) / DIV;
		while (j < (WIDTH * q) / DIV)
		{
			tmp.re = (j - WIDTH/2.0) * 4/WIDTH * ptr.zoom;
			c.re = pow(tmp.re, 3) - 3 * tmp.re * pow(tmp.im, 2);
			c.im = 3 * pow(tmp.re, 2) * tmp.im - pow(tmp.im, 3);
			if (j < P(j, i) - 2 * pow(P(j, i), 2) + 1 / 4 || pow(j + 1, 2) + pow(i, 2) < 1/16)
			{
				img_put_pixel(&ptr, j, i, 0);
				continue;
			}
			z = complex(0, 0);
			k = -1;
			while (mod(z) <= 2 && ++k < ptr.max_iter)
			{
				z1.re = pow((pow(z.re, 2) + pow(z.im, 2)), (ptr.m_puis / 2.0)) * cos(ptr.m_puis * atan2(z.im, z.re)) + c.re -1.401155;
				z1.im = pow((pow(z.re, 2) + pow(z.im, 2)), (ptr.m_puis / 2.0)) * sin(ptr.m_puis * atan2(z.im, z.re)) + c.im;
				z = z1;
			}
			if (k < ptr.max_iter)
				img_put_pixel(&ptr, j, i, design_color(ptr, k));
			else
				img_put_pixel(&ptr, j, i, intern_color(ptr, k, mod(z)));
			j++;
		}
		i++;
	}
}

void		feigenbaum(t_graphic ptr)
{
	int	i;
	int	j;

	i = 0;
	while (++i <= DIV)
	{
		j = 0;
		while (++j <= DIV)
			part_feigen(ptr, i, j);
	}
}
