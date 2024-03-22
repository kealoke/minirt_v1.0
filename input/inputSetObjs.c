/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputSetObjs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaei <smaei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:32:13 by yushimom          #+#    #+#             */
/*   Updated: 2024/03/22 22:08:55 by smaei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// tokenからt_sphere構造体に値を変換する関数
// 1: char **token -> 変換したいtoken列
// 2: t_minirt *world -> 変換した値を入れるminirt構造体
// 3: t_read_flag *flag -> オブジェクト情報が正しく入力されたかどうか
void	set_sphere(char **token, t_minirt *world, t_read_flag *flag)
{
	t_sphere	*sp;
	t_objects	*obj;
	bool		rgb_flag;

	if (!token[1] || !token[2] || !token[3])
		err_and_exit("Sphere value is not enough\n");
	if (token[4] && token[4][0] != '\0' && token[4][0] != '\n')
		err_and_exit("Sphere value is many\n");
	sp = my_malloc(sizeof(t_sphere));
	set_vec(token[1], &(sp->center_vec));
	sp->diameter = ft_atod(token[2]);
	rgb_flag = set_rgb_color(token[3], &(sp->color));
	if (rgb_flag == false)
		err_and_exit(SP_COLOR_ERR);
	obj = objnew(sp);
	obj->obj_type = t_sp;
	ob_lstadd_back(&(world->objs), obj);
	flag->obj_f = true;
}

// tokenからt_plane構造体に値を変換する関数
// 1: char **token -> 変換したいtoken列
// 2: t_minirt *world -> 変換した値を入れるminirt構造体
// 3: t_read_flag *flag -> オブジェクト情報が正しく入力されたかどうか
void	set_plane(char **token, t_minirt *world, t_read_flag *flag)
{
	bool		rgb_flag;
	t_plane		*pl;
	t_objects	*obj;

	if (!token[1] || !token[2] || !token[3])
		err_and_exit("Plane value is not enough\n");
	if (token[4] && token[4][0] != '\0' && token[4][0] != '\n')
		err_and_exit("Plane value is many\n");
	pl = my_malloc(sizeof(t_plane));
	set_vec(token[1], &(pl->pos_vec));
	set_vec(token[2], &(pl->normal_vec));
	if (check_vec_range(pl->normal_vec) == false)
		err_and_exit(PLANE_VEC_ERR);
	rgb_flag = set_rgb_color(token[3], &(pl->color));
	if (rgb_flag == false)
		err_and_exit(PLANE_COLOR_ERR);
	obj = objnew(pl);
	obj->obj_type = t_pl;
	ob_lstadd_back(&(world->objs), obj);
	flag->obj_f = true;
}

// tokenからt_cylinder構造体に値を変換する関数
// 1: char **token -> 変換したいtoken列
// 2: t_minirt *world -> 変換した値を入れるminirt構造体
// 3: t_read_flag *flag -> オブジェクト情報が正しく入力されたかどうか
void	set_cylinder(char **token, t_minirt *world, t_read_flag *flag)
{
	bool		rgb_flag;
	t_cylinder	*cy;
	t_objects	*obj;

	if (!token[1] || !token[2] || !token[3] || !token[4] || !token[5])
		err_and_exit("Cylinder value is not enough\n");
	if (token[6] && token[6][0] != '\0' && token[6][0] != '\n')
		err_and_exit("Cylinder value is many\n");
	cy = my_malloc(sizeof(t_cylinder));
	set_vec(token[1], &(cy->center_vec));
	set_vec(token[2], &(cy->axis_vec));
	if (check_vec_range(cy->axis_vec) == false)
		err_and_exit(CY_AXIS_VEC_ERR);
	cy->diameter = ft_atod(token[3]);
	cy->height = ft_atod(token[4]);
	rgb_flag = set_rgb_color(token[5], &(cy->color));
	if (rgb_flag == false)
		err_and_exit(CY_COLOR_ERR);
	obj = objnew(cy);
	obj->obj_type = t_cy;
	ob_lstadd_back(&(world->objs), obj);
	flag->obj_f = true;
}
