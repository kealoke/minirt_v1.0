/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushimom <yushimom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:32:38 by yushimom          #+#    #+#             */
/*   Updated: 2024/03/02 18:36:03 by yushimom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// 円柱の判別式を計算する関数
// 1: t_ray ray -> レイベクトル
// 2: t_cylinder obj -> 判定するオブジェクト
// 3: bool first -> 内側か外側かのflag
double	get_cy_intersection(t_ray ray, t_cylinder obj, bool first)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vec	pvc;

	pvc = sub_vec(ray.pos, obj.center_vec);
	a = norm_vec(cross_vec(ray.dir, obj.axis_vec));
	a *= a;
	b = 2 * inner_vec(cross_vec(ray.dir, obj.axis_vec), cross_vec(pvc,
				obj.axis_vec));
	c = norm_vec(cross_vec(pvc, obj.axis_vec));
	c = c * c - obj.diameter / 2 * obj.diameter / 2;
	d = b * b - 4 * a * c;
	if (d >= 0 && first)
		return ((-b - sqrt(d)) / (2 * a));
	else if (d > 0 && first == false)
		return ((-b + sqrt(d)) / (2 * a));
	return (NON);
}

// 交点判定の結果から各ベクトルを計算する関数
// 1: t_ray ray -> レイベクトル
// 2: t_cylinder obj -> 判定するオブジェクト
// 3: bool first -> 内側か外側かのflag
t_cy_info	get_cy_intersection_info(t_ray ray, t_cylinder *obj, bool first)
{
	t_cy_info	res;

	res.t = get_cy_intersection(ray, *obj, first);
	res.inter_pos = add_vec(ray.pos, mul_vec(ray.dir, res.t));
	res.to_center = sub_vec(res.inter_pos, obj->center_vec);
	res.p_c_n = inner_vec(res.to_center, obj->axis_vec);
	if (first)
		res.flag = out;
	else
		res.flag = in;
	return (res);
}

// 交点の計算情報を格納する（情報をコピーする）
// 1: t_cy_info *inter -> 情報を格納する変数
// 2: t_cy_info intersection -> 格納したい情報を持つ変数
void	assignment(t_cy_info *inter, t_cy_info intersection)
{
	inter->flag = intersection.flag;
	inter->t = intersection.t;
	inter->inter_pos = intersection.inter_pos;
	inter->to_center = intersection.to_center;
	inter->p_c_n = intersection.p_c_n;
}

// 円柱の交点を計算する
// 1: t_cylinder *obj -> 円柱オブジェクト
// 2: t_ray ray -> レイベクトル
// 3: double h -> 円柱の高さ/2
// 4: t_cy_info *inter -> 法線ベクトルなどの計算に必要な交点の情報
void	get_cy_test_condition(t_cylinder *obj, t_ray ray, double h,
		t_cy_info *inter)
{
	t_cy_info	inner_inter;
	t_cy_info	outer_inter;

	outer_inter = get_cy_intersection_info(ray, obj, true);
	inner_inter = get_cy_intersection_info(ray, obj, false);
	if (-h <= outer_inter.p_c_n && outer_inter.p_c_n <= h && outer_inter.t > 0)
		assignment(inter, outer_inter);
	else if (-h <= inner_inter.p_c_n && inner_inter.p_c_n <= h
		&& inner_inter.t > 0)
		assignment(inter, inner_inter);
	else
		inter->flag = non;
}

// 円柱のオブジェクトとレイの交差判定をしてベクトル情報を返す
//		交点がある場合は描写に必要なベクトル情報を構造体で返す
// 1: t_minirt *world -> 全体の情報を持つ構造体
// 2: t_objects tmp_o_list -> オブジェクトリストのノード
// 3: t_ray ray -> 交差判定をするレイ
t_vec_info	cy_intersecton(t_minirt *world, t_objects tmp_o_list, t_ray ray)
{
	t_cylinder	*cy_obj;
	t_vec_info	res;
	t_cy_info	inter;
	t_vec		inter_to_center;

	cy_obj = tmp_o_list.content;
	get_cy_test_condition(cy_obj, ray, cy_obj->height / 2, &inter);
	if (inter.flag == non)
		res.t = -1.0;
	else
	{
		res.t = inter.t;
		res.inter_pos = inter.inter_pos;
		if (inter.flag == in)
			inter_to_center = sub_vec(mul_vec(cy_obj->axis_vec, inter.p_c_n),
					inter.to_center);
		else if (inter.flag == out)
			inter_to_center = sub_vec(inter.to_center, mul_vec(cy_obj->axis_vec,
						inter.p_c_n));
		res.normal = vec_normalize(inter_to_center);
		res.light_dir = vec_normalize(sub_vec(world->light->pos_vec,
					res.inter_pos));
		res.color = cy_obj->color;
	}
	return (res);
}
