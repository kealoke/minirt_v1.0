#include "../minirt.h"

double	get_cy_intersection(t_ray ray, t_cylinder obj, bool first)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vec	pvc;

	pvc = sub_vec(ray.pos, obj.center_vec);
	a = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
	b = 2 * (pvc.x * ray.dir.x + pvc.z * ray.dir.z);
	c = pvc.x * pvc.x + pvc.z * pvc.z - obj.height / 2 * obj.height / 2;
	d = b * b - 4 * a * c;
	if (d == 0)
		return ((-b - sqrt(d)) / (2 * a));
	else if (d > 0 && first)
		return (-b - sqrt(d)) / (2 * a);
	else if (d > 0)
		return (-b + sqrt(d)) / (2 * a);
	return (d);
}

double	get_cy_test_condition(t_cylinder *obj, t_ray ray, double harf_h)
{
	double	t1;
	double	t2;
	double	diff_t1;
	double	diff_t2;

	t1 = get_cy_intersection(ray, *obj, true);
	t2 = get_cy_intersection(ray, *obj, false);
	diff_t1 = obj->center_vec.y - add_vec(ray.pos, mul_vec(ray.dir, t1)).y;
	diff_t2 = obj->center_vec.y - add_vec(ray.pos, mul_vec(ray.dir, t2)).y;
	if (-harf_h < diff_t1 && diff_t1 < harf_h && -harf_h < diff_t2
		&& diff_t2 < harf_h)
	{
		if (diff_t1 < diff_t2)
			return (t1);
		return (t2);
	}
	else if (-harf_h < diff_t1 && diff_t1 < harf_h)
		return (t1);
	else if (-harf_h < diff_t2 && diff_t2 < harf_h)
	{
		obj->inside = true;
		return (t2);
	}
	return (-1);
}

//交点位置をえきさんして高さの範囲内にあるか見る

//円柱のオブジェクトとレイの交差判定をしてベクトル情報を返す
//	交点がある場合は描写に必要なベクトル情報を構造体で返す
// 1: t_minirt *world -> 全体の情報を持つ構造体
// 2: t_objects tmp_o_list -> オブジェクトリストのノード
// 3: t_ray ray -> 交差判定をするレイ
t_vec_info	cy_intersecton(t_minirt *world, t_objects tmp_o_list, t_ray ray)
{
	t_cylinder	*cy_obj;
	t_vec_info	res;
	t_vec		inter_to_center;

	cy_obj = tmp_o_list.content;
	cy_obj->inside = false;
	res.t = get_cy_test_condition(cy_obj, ray, cy_obj->height / 2);
	// Dが０以上なら交点を持つ、0以上かつy軸距離が[−ℎ2,ℎ2]の範囲内である場合のみ交点を持つ
	if (res.t > 0)
	{
		//交点位置
		res.inter_pos = add_vec(ray.pos, mul_vec(ray.dir, res.t));
		// 交点位置から円柱の中心へのベクトルを計算
		inter_to_center = sub_vec(res.inter_pos, cy_obj->center_vec);
		// 円柱の軸に平行な成分を除外
		inter_to_center.y = 0;
		inter_to_center.x *= 2;
		inter_to_center.z *= 2;
		// 法線ベクトルを正規化
		res.normal = vec_normalize(inter_to_center);
		//flagがtrueなら円柱の内側なので逆ベクトルにする
		if (cy_obj->inside == true)
			res.normal = mul_vec(res.normal, -1);
		res.light_dir = vec_normalize(sub_vec(world->light->pos_vec,
					res.inter_pos));
		res.color = cy_obj->color;
	}
	return (res);
}
