/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputSet.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushimom <yushimom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:32:09 by yushimom          #+#    #+#             */
/*   Updated: 2024/03/07 17:22:57 by yushimom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// tokenからt_ambient構造体に値を変換する関数
// 1: char **token -> 変換したいtoken列
// 2: t_minirt *world -> 変換した値を入れるminirt構造体
// 3: t_read_flag *flag -> ambient情報が正しく読み込まれたかどうか
void	set_ambient(char **token, t_minirt *world, t_read_flag *flag)
{
	bool	rgb_flag;

	if (!token[1] || !token[2])
		err_and_exit("Amiebt value is not enough\n");
	if (world->amb != NULL)
		err_and_exit("Ambient can only be declared once\n");
	world->amb = my_malloc(sizeof(t_ambient));
	world->amb->light_intensity = ft_atod(token[1]);
	if (world->amb->light_intensity < 0.0 || 1.0 < world->amb->light_intensity)
		err_and_exit(AMB_LIGHT_ERR);
	rgb_flag = set_rgb_color(token[2], &(world->amb->color));
	if (rgb_flag == false)
		err_and_exit(AMB_COLOR_ERR);
	flag->amb_f = true;
}

// tokenからカメラ構造体に変換する関数
// 1: char **token -> 変換したいtoken列
// 2: t_minirt *world -> 変換した値を入れるminirt構造体
// 3: t_read_flag *flag -> カメラ情報が正しく読み取れたかどうか
void	set_camera(char **token, t_minirt *world, t_read_flag *flag)
{
	if (!token[1] || !token[2] || !token[3])
		err_and_exit("Camera value is not enough\n");
	if (world->cam != NULL)
		err_and_exit("Camera can only be declared once\n");
	world->cam = my_malloc(sizeof(t_camera));
	set_vec(token[1], &(world->cam->pos_vec));
	set_vec(token[2], &(world->cam->ori_vec));
	if (check_vec_range(world->cam->ori_vec) == false)
		err_and_exit(CAM_VEC_ERR);
	world->cam->fov = atoi_and_check(token[3]);
	if (world->cam->fov < 0 || 180 < world->cam->fov)
		err_and_exit(CAM_FOV_ERR);
	flag->cam_f = true;
}

// tokenからLight構造体に変換する関数
// 1: char **token -> 変換したいtoken列
// 2: t_minirt *world -> 変換した値を入れるminirt構造体
// 3: t_read_flag *flag -> 光源情報が正しく読み取れたかどうか
void	set_light(char **token, t_minirt *world, t_read_flag *flag)
{
	int	rgb_flag;

	if (!token[1] || !token[2] || !token[3])
		err_and_exit("Light value is not enough\n");
	if (world->light != NULL)
		err_and_exit("Light can only be declared once");
	world->light = my_malloc(sizeof(t_light));
	set_vec(token[1], &(world->light->pos_vec));
	world->light->brightness = ft_atod(token[2]);
	if (world->light->brightness < 0.0 || 1.0 < world->light->brightness)
		err_and_exit(LIGHT_BRIGHT_ERR);
	rgb_flag = set_rgb_color(token[3], &(world->light->color));
	if (rgb_flag == false)
		err_and_exit(LIGHT_COLOR_ERR);
	flag->light_f = true;
}
