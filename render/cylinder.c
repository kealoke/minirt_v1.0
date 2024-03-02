#include "../minirt.h"

double	get_cy_intersection(t_ray ray, t_cylinder obj, bool first)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vec	pvc;

	pvc = sub_vec(ray.pos, obj.center_vec);
	// a = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
	// b = 2 * (pvc.x * ray.dir.x + pvc.z * ray.dir.z);
	// c = pvc.x * pvc.x + pvc.z * pvc.z - obj.height / 2 * obj.height / 2;
	a = norm_vec(cross_vec(ray.dir, obj.axis_vec));
	a *= a;
	b = 2 * inner_vec(cross_vec(ray.dir, obj.axis_vec), cross_vec(pvc, obj.axis_vec));
	c = norm_vec(cross_vec(pvc, obj.axis_vec));
	c = c * c - obj.diameter/2 * obj.diameter/2;

	d = b * b - 4 * a * c;
	// if (d == 0)
	// 	return ((-b - sqrt(d)) / (2 * a));
	// else if (d > 0 && first)
	// 	return ((-b - sqrt(d)) / (2 * a));
	// else if (d > 0)
	// 	return ((-b + sqrt(d)) / (2 * a));
	if (d >= 0 && first)
		return ((-b - sqrt(d)) / (2 * a));
	else if (d > 0 && first == false)
		return ((-b + sqrt(d)) / (2 * a));

	return (NON);
}

void	get_cy_test_condition(t_cylinder *obj, t_ray ray, double h, t_cy_info *res)
{
	double	t1;
	double	t2;
	double	diff_out;
	double	diff_in;

	t1 = get_cy_intersection(ray, *obj, true);
	t2 = get_cy_intersection(ray, *obj, false);
	// diff_t1 = obj->center_vec.y - add_vec(ray.pos, mul_vec(ray.dir, t1)).y;
	// diff_t2 = obj->center_vec.y - add_vec(ray.pos, mul_vec(ray.dir, t2)).y;

	t_vec p_out = add_vec(ray.pos, mul_vec(ray.dir, t1));
	t_vec p_in = add_vec(ray.pos, mul_vec(ray.dir, t2));

	//レイと無限円柱の交点
	t_vec center_to_out = sub_vec(p_out, obj->center_vec);
	t_vec center_to_in = sub_vec(p_in, obj->center_vec);

	diff_out = inner_vec(center_to_out, obj->axis_vec);
	diff_in = inner_vec(center_to_in, obj->axis_vec);

	if (0 <= diff_out && diff_out <= h)
	{
		res->flag = out;
		res->t = t1;
		res->inter_pos = p_out;
		res->to_center = center_to_out;
		res->p_c_n = diff_out;
	}
	else if (0 <= diff_in && diff_in <= h)
	{
		res->flag = in;
		res->t = t2;
		res->inter_pos = p_in;
		res->to_center = center_to_in;
		res->p_c_n = diff_in;
	}
	else
		res->flag = non;
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
	// cy_obj->inside = false;
	get_cy_test_condition(cy_obj, ray, cy_obj->height, &inter);
	// Dが０以上なら交点を持つ、0以上かつy軸距離が[−ℎ2,ℎ2]の範囲内である場合のみ交点を持つ
	if (inter.flag == non)
	{
		res.t = -1.0;
	}
	else
	{
		//交点位置
		res.inter_pos = inter.inter_pos;
		//交点から円柱の中心
		if (inter.flag == in)
		{
			inter_to_center = sub_vec(mul_vec(cy_obj->axis_vec, inter.p_c_n),inter.to_center);
		}
		else if (inter.flag == out)
		{
			inter_to_center = sub_vec(inter.to_center,mul_vec(cy_obj->axis_vec, inter.p_c_n));
		}
		//法線ベクトルを求める
		// 法線ベクトルを正規化
		res.normal = vec_normalize(inter_to_center);
		res.light_dir = vec_normalize(sub_vec(world->light->pos_vec, res.inter_pos));
		res.color = cy_obj->color;
	}
	return (res);
}