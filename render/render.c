/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushimom <yushimom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:33:07 by yushimom          #+#    #+#             */
/*   Updated: 2024/03/02 18:35:08 by yushimom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//スクリーンの基底ベクトルを取得する
// 1: t_minirt *world -> ワールド情報
t_screen	get_screen_vec(t_minirt *world)
{
	double		d;
	t_screen	res;

	d = WIDTH / 2 / tan(world->cam->fov / 2 / 180 * M_PI);
	res.dsc = mul_vec(world->cam->ori_vec, d);
	res.esx.x = res.dsc.z / sqrt(res.dsc.z * res.dsc.z + res.dsc.x * res.dsc.x);
	res.esx.y = 0;
	res.esx.z = -res.dsc.x / sqrt(res.dsc.z * res.dsc.z + res.dsc.x
			* res.dsc.x);
	res.esx = vec_normalize(res.esx);
	res.esy = vec_normalize(cross_vec(res.dsc, res.esx));
	return (res);
}

//レイの位置ベクトルと方向ベクトルを取得する
// 1: t_minirt *world -> ワールド情報
// 2: t_screen screen -> スクリーンの基底ベクトル
// 3: int x -> スクリーンのx座標
// 4: int y -> スクリーンのy座標
t_ray	get_ray(t_minirt *world, t_screen screen, int x, int y)
{
	t_ray	res_ray;
	double	screen_w;
	double	screen_h;
	t_vec	x_vec;
	t_vec	y_vec;

	screen_w = x - (WIDTH - 1) / 2;
	screen_h = (HEIGHT - 1) / 2 - y;
	x_vec = mul_vec(screen.esx, screen_w);
	y_vec = mul_vec(screen.esy, screen_h);
	res_ray.dir = vec_normalize(add_vec(screen.dsc, add_vec(x_vec, y_vec)));
	res_ray.pos = world->cam->pos_vec;
	return (res_ray);
}

//レンダーを行い、ウィンドウに描写する
// 1: t_minirt *world -> ワールド情報
// 2: t_screen screen -> スクリーンの基底ベクトル
// 3: int x -> スクリーンのx座標
// 4: int y -> スクリーンのy座標
// 5: t_mlx *mlx -> mlx情報
void	draw(t_minirt *world, t_screen screen, int x, int y)
{
	t_ray		ray;
	t_vec_info	closest_obj;
	double		ra;
	int			color;

	ra = get_ambient(world);
	ray = get_ray(world, screen, x, y);
	closest_obj = get_intersection(world, ray);
	if (closest_obj.t > 0)
	{
		color = get_color(world, closest_obj, ray, ra);
		my_mlx_pixel_put(&(world->mlx), x, y, color);
	}
	else
		my_mlx_pixel_put(&(world->mlx), x, y, BACK_COLOR);
}

// ウィンドウに描写する
// 1: t_minirt *world -> ワールド情報
// 2: t_mlx *mlx -> mlx情報
bool	render(t_minirt *world)
{
	int			x;
	int			y;
	t_screen	screen;

	screen = get_screen_vec(world);
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			draw(world, screen, x, y);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(world->mlx.mlx, world->mlx.window, world->mlx.img,
		0, 0);
	mlx_hook(world->mlx.window, 17, 0, close_win, &(world->mlx));
	mlx_hook(world->mlx.window, 2, 0, key, &(world->mlx));
	mlx_loop(world->mlx.mlx);
	return (true);
}
