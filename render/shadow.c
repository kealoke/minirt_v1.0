#include "../minirt.h"

//物体にシャドウがかかるかチェックする関数
// 1: t_minirt *world -> ワールド情報
// 2: t_vec_info obj -> レイと交差するオブジェクト
bool	check_shadow(t_minirt *world, t_vec_info obj)
{
	t_ray		shadow_ray;
	t_vec		i_to_l;
	double		d_to_light;
	t_objects	*tmp_o_list;
	t_vec_info	tmp;

	tmp_o_list = world->objs;
	// 交点から光源までのベクトル
	i_to_l = sub_vec(world->light->pos_vec, obj.inter_pos);
	shadow_ray.dir = vec_normalize(i_to_l);
	shadow_ray.pos = add_vec(obj.inter_pos, mul_vec(shadow_ray.dir, EPSILON));
	d_to_light = norm_vec(i_to_l) - EPSILON;
	//全てのオブジェクトに対して計算するが交点があった時点で終了
	while (tmp_o_list != NULL)
	{
		tmp = calc_intersection(world, *tmp_o_list, shadow_ray);
		//交点があり、光源までの距離よりも短いなら影になる
		if (tmp.t >= 0 && tmp.t <= d_to_light)
			return (true);
		tmp_o_list = tmp_o_list->next;
	}
	return (false);
}
