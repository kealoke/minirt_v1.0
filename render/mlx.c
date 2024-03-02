/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushimom <yushimom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:32:50 by yushimom          #+#    #+#             */
/*   Updated: 2024/03/02 18:32:52 by yushimom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//mlxのウィンドウ情報を設定する
void	set_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "MiniRT");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &(mlx->bits_per_pixel),
			&(mlx->line_length), &(mlx->endian));
}

//ウィンドウを閉じてプログラムを終了する
int	close_win(t_mlx *data)
{
	mlx_destroy_window(data->mlx, data->window);
	exit(1);
	return (0);
}

//キーが押された時に対応する処理を実行する
int	key(int key_code, t_mlx *mlx)
{
	if (key_code == ESC)
	{
		close_win(mlx);
	}
	return (0);
}

//イメージにピクセルカラーを設定する
void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}
