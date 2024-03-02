/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushimom <yushimom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:32:59 by yushimom          #+#    #+#             */
/*   Updated: 2024/03/02 18:35:25 by yushimom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//平面オブジェクトとレイの交差判定をする
//	交点がある場合は描写に必要なベクトル情報を構造体で返す
// 1: t_minirt *world -> 全体の情報を持つ構造体
// 2: t_objects tmp_o_list -> オブジェクトリストのノード
// 3: t_ray ray -> 交差判定をするレイ
t_vec_info	pl_intersection(t_minirt *world, t_objects tmp_o_list, t_ray ray)
{
	t_plane		*pl_obj;
	t_vec		s_vec;
	t_vec_info	res;
	double		denom;

	pl_obj = tmp_o_list.content;
	s_vec = sub_vec(ray.pos, pl_obj->pos_vec);
	denom = inner_vec(ray.dir, pl_obj->normal_vec);
	if (fabs(denom) > 1e-6)
	{
		res.t = (-(inner_vec(s_vec, pl_obj->normal_vec) / denom));
		if (res.t >= 0)
		{
			res.normal = vec_normalize(pl_obj->normal_vec);
			res.color = pl_obj->color;
			res.inter_pos = add_vec(ray.pos, mul_vec(ray.dir, res.t));
			res.light_dir = vec_normalize(sub_vec(world->light->pos_vec,
						res.inter_pos));
		}
	}
	else
		res.t = -1;
	return (res);
}
