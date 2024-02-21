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

	nl = inner_product(closest_obj.light_dir, closest_obj.normal);
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

	nl = inner_product(closest_obj.light_dir, closest_obj.normal);
	if (nl > 0)
	{
		//正反射ベクトルを求める
		r = vec_normalize(sub_vec(mul_vec(mul_vec(closest_obj.normal, nl), 2),
					closest_obj.light_dir));
		//視線ベクトルの逆ベクトル
		v = vec_normalize(mul_vec(dir_vec, -1));
		vr = inner_product(v, r);
		if (vr < 0)
			vr = 0;
		supecular_ref = SUP_K * world->light->brightness * pow(vr, 10.0);
	}
	else
		supecular_ref = 0;
	return (supecular_ref);
}

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
