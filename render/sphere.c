/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushimom <yushimom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:33:21 by yushimom          #+#    #+#             */
/*   Updated: 2024/03/02 18:33:23 by yushimom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//判別式Dを計算し、tを求める
double	get_test_condition(t_vec pvc, t_ray ray, t_sphere *sp_obj)
{
	double	a;
	double	b;
	double	c;
	double	d;

	a = inner_vec(ray.dir, ray.dir);
	b = inner_vec(pvc, ray.dir) * 2;
	c = inner_vec(pvc, pvc) - sp_obj->diameter / 2 * sp_obj->diameter / 2;
	d = b * b - 4 * a * c;
	if (d >= 0)
	{
		return ((-b - sqrt(d)) / (2 * a));
	}
	return (d);
}

//球体のオブジェクトとレイの交差判定をしてベクトル情報を返す
//	交点がある場合は描写に必要なベクトル情報を構造体で返す
// 1: t_minirt *world -> 全体の情報を持つ構造体
// 2: t_objects tmp_o_list -> オブジェクトリストのノード
// 3: t_ray ray -> 交差判定をするレイ
t_vec_info	sp_intersection(t_minirt *world, t_objects tmp_o_list, t_ray ray)
{
	t_vec		pvc;
	t_sphere	*sp_obj;
	t_vec_info	res;

	sp_obj = tmp_o_list.content;
	pvc = sub_vec(ray.pos, sp_obj->center_vec);
	res.t = get_test_condition(pvc, ray, sp_obj);
	if (res.t > 0)
	{
		res.inter_pos = add_vec(ray.pos, mul_vec(ray.dir, res.t));
		res.normal = vec_normalize(sub_vec(res.inter_pos, sp_obj->center_vec));
		res.light_dir = vec_normalize(sub_vec(world->light->pos_vec,
					res.inter_pos));
		res.color = sp_obj->color;
	}
	return (res);
}
