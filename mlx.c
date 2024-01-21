#include "minirt.h"

int	close_win(t_libx *data)
{
	mlx_destroy_window(data->mlx, data->window);
	exit(1);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}