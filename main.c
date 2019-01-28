#include "fractol.h"

static void	error()
{
	ft_putstr("Usage: ./fractol fractal_type\n");
	ft_putstr("Available fractals:	* Julia\n");
	ft_putstr("                     * Mandelbrot\n");
	exit(-1);
}

void	init_ptr(t_graphic *ptr)
{
	ptr->mlx = mlx_init();
	ptr->win = mlx_new_window(ptr->mlx, WIDTH, HEIGHT, "fractol");
	ptr->max_iter = 300;
	ptr->map[0].color = rgb_map(66, 30, 15);
	ptr->map[1].color = rgb_map(25, 7, 26);
	ptr->map[2].color = rgb_map(9, 1, 47);
	ptr->map[3].color = rgb_map(4, 4, 73);
	ptr->map[4].color = rgb_map(0, 7, 100);
	ptr->map[5].color = rgb_map(12, 44, 138);
	ptr->map[6].color = rgb_map(24, 82, 177);
	ptr->map[7].color = rgb_map(57, 125, 209);
	ptr->map[8].color = rgb_map(134, 181, 229);
	ptr->map[9].color = rgb_map(211, 236, 248);
	ptr->map[10].color = rgb_map(241, 233, 191);
	ptr->map[11].color = rgb_map(248, 201, 95);
	ptr->map[12].color = rgb_map(255, 170, 0);
	ptr->map[13].color = rgb_map(204, 128, 0);
	ptr->map[14].color = rgb_map(153, 87, 0);
	ptr->map[15].color = rgb_map(106, 52, 3);
}

int	main(int ac, char **av)
{
	t_graphic	ptr;

	if (ac != 2 || (ft_strcmp(av[1], "Julia") && ft_strcmp(av[1], "Mandelbrot")))
		error();
	init_ptr(&ptr);
	if (!strcmp(av[1], "Mandelbrot"))
		mandelbrot(ptr);
	if (!strcmp(av[1], "Julia"))
		julia(ptr);
	mlx_loop(ptr.mlx);
}
