#include "../minirt.h"

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
	b = 2 * inner_vec(cross_vec(ray.dir, obj.axis_vec), cross_vec(pvc, obj.axis_vec));
	c = norm_vec(cross_vec(pvc, obj.axis_vec));
	c = c * c - obj.diameter/2 * obj.diameter/2;

	d = b * b - 4 * a * c;
	if (d >= 0 && first)
		return ((-b - sqrt(d)) / (2 * a));
	else if (d > 0 && first == false)
		return ((-b + sqrt(d)) / (2 * a));

	return (NON);
}

t_cy_info get_cy_intersection_info(t_ray ray, t_cylinder *obj, bool first) {
	t_cy_info res;

	res.t = get_cy_intersection(ray, *obj, first);
	res.inter_pos = add_vec(ray.pos, mul_vec(ray.dir, res.t));
	// レイと無限円柱の交点
	res.to_center = sub_vec(res.inter_pos, obj->center_vec);
	res.p_c_n = inner_vec(res.to_center, obj->axis_vec);
	if (first)
		res.flag = out;
	else
		res.flag = in;
	return res;
}

void	get_cy_test_condition(t_cylinder *obj, t_ray ray, double h, t_cy_info *inter)
{
	t_cy_info inner_intersection;
	t_cy_info outer_intersection;

	outer_intersection = get_cy_intersection_info(ray, obj, true);
	inner_intersection = get_cy_intersection_info(ray, obj, false);
	if (-h/2 <= outer_intersection.p_c_n && outer_intersection.p_c_n <= h/2 && outer_intersection.t > 0)
	{
		inter->flag = outer_intersection.flag;
		inter->t = outer_intersection.t;
		inter->inter_pos = outer_intersection.inter_pos;
		inter->to_center = outer_intersection.to_center;
		inter->p_c_n = outer_intersection.p_c_n;
	}
	else if (-h/2 <= inner_intersection.p_c_n && inner_intersection.p_c_n <= h/2 && inner_intersection.t > 0)
	{
		inter->flag = inner_intersection.flag;
		inter->t = inner_intersection.t;
		inter->inter_pos = inner_intersection.inter_pos;
		inter->to_center = inner_intersection.to_center;
		inter->p_c_n = inner_intersection.p_c_n;
	}
	else
		inter->flag = non;
}

//円柱のオブジェクトとレイの交差判定をしてベクトル情報を返す
//	交点がある場合は描写に必要なベクトル情報を構造体で返す
// 1: t_minirt *world -> 全体の情報を持つ構造体
// 2: t_objects tmp_o_list -> オブジェクトリストのノード
// 3: t_ray ray -> 交差判定をするレイ
t_vec_info	cy_intersecton(t_minirt *world, t_objects tmp_o_list, t_ray ray)
{
	t_cylinder		*cy_obj;
	t_vec_info		res;
	t_cy_info	inter;
	t_vec			inter_to_center;

	cy_obj = tmp_o_list.content;
	get_cy_test_condition(cy_obj, ray, cy_obj->height, &inter);
	// Dが０以上なら交点を持つ、0以上かつy軸距離が[−ℎ2,ℎ2]の範囲内である場合のみ交点を持つ
	if (inter.flag == non)
		res.t = -1.0;
	else
	{
		res.t = inter.t;
		//交点位置
		res.inter_pos = inter.inter_pos;
		//交点から円柱の中心
		if (inter.flag == in)
			inter_to_center = sub_vec(mul_vec(cy_obj->axis_vec, inter.p_c_n),inter.to_center);
		else if (inter.flag == out)
			inter_to_center = sub_vec(inter.to_center,mul_vec(cy_obj->axis_vec, inter.p_c_n));
		//法線ベクトルを求める
		// 法線ベクトルを正規化
		res.normal = vec_normalize(inter_to_center);
		res.light_dir = vec_normalize(sub_vec(world->light->pos_vec, res.inter_pos));
		res.color = cy_obj->color;
	}
	return (res);
}