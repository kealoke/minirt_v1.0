/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushimom <yushimom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:33:04 by yushimom          #+#    #+#             */
/*   Updated: 2024/03/02 18:35:16 by yushimom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//環境光の放射輝度を取得する関数
// 1: t_minirt *world -> ワールド情報
double	get_ambient(t_minirt *world)
{
	double	ambient_ref;

	ambient_ref = AMB_K * world->amb->light_intensity;
	return (ambient_ref);
}

//拡散反射の放射輝度を取得する関数
// 1: t_minirt *world -> ワールド情報
// 2: t_vec_info obj -> レイと交差するオブジェクト
double	get_diffuse(t_minirt *world, t_vec_info closest_obj)
{
	double	diffuse_ref;
	double	nl;

	nl = inner_vec(closest_obj.light_dir, closest_obj.normal);
	if (nl < 0)
		nl = 0;
	diffuse_ref = DIFF_K * nl * world->light->brightness;
	return (diffuse_ref);
}

//鏡面反射の放射輝度を取得する関数
// 1: t_minirt *world -> ワールド情報
// 2: t_vec_info obj -> レイと交差するオブジェクト
// 3: t_vec dir_vec -> レイの方向ベクトル
double	get_supecular(t_minirt *world, t_vec_info closest_obj, t_vec dir_vec)
{
	double	supecular_ref;
	double	nl;
	t_vec	r;
	t_vec	v;
	double	vr;

	nl = inner_vec(closest_obj.light_dir, closest_obj.normal);
	if (nl > 0)
	{
		r = vec_normalize(sub_vec(mul_vec(mul_vec(closest_obj.normal, nl), 2),
					closest_obj.light_dir));
		v = vec_normalize(mul_vec(dir_vec, -1));
		vr = inner_vec(v, r);
		if (vr < 0)
			vr = 0;
		supecular_ref = SUP_K * world->light->brightness * pow(vr, 10.0);
	}
	else
		supecular_ref = 0;
	return (supecular_ref);
}
