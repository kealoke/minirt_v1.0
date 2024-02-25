#include "../minirt.h"
/*
//円柱のオブジェクトとレイの交差判定をしてベクトル情報を返す
//	交点がある場合は描写に必要なベクトル情報を構造体で返す
// 1: t_minirt *world -> 全体の情報を持つ構造体
// 2: t_objects tmp_o_list -> オブジェクトリストのノード
// 3: t_ray ray -> 交差判定をするレイ
t_vec_info cy_sh_intersecton(t_minirt *world, t_objects tmp_o_list, t_ray ray) {
    t_vec        pvc;
    t_cylinder    *cy_obj;
    bool flag;

    cy_obj = tmp_o_list.content;
    pvc = sub_vec(ray.pos, cy_obj->center_vec);
    double A;
    double B;
    double C;
    double r = cy_obj->diameter / 2;
    double harf_h = cy_obj->height / 2;
    // printf("harf-h  %f", harf_h);
    t_vec_info res;

    A = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
    B = 2 * (pvc.x * ray.dir.x + pvc.z * ray.dir.z);
    C = pvc.x * pvc.x + pvc.z * pvc.z - r * r;

    res.t = get_test_condition(A, B, C);
    // Dが０以上なら交点を持つ、0以上かつy軸距離が[−ℎ2,ℎ2]の範囲内である場合のみ交点を持つ
    if (res.t > 0) {
        //交点位置
        res.inter_pos = add_vec(ray.pos, mul_vec(ray.dir, res.t));
        double diff = cy_obj->center_vec.y - res.inter_pos.y;
        // 交点位置から円柱の中心へのベクトルを計算
        t_vec inter_to_center = sub_vec(res.inter_pos, cy_obj->center_vec);

        // 円柱の軸に平行な成分を除外
        inter_to_center.y = 0;
        // inter_to_center.x *= 2;
        // inter_to_center.z *= 2;

        // 法線ベクトルを正規化
        res.normal = vec_normalize(inter_to_center);
        //flagがtrueなら円柱の内側なので逆ベクトルにする
        if(flag == true){
            res.normal = mul_vec(res.normal, -1);
        }

        res.light_dir = vec_normalize(sub_vec(world->light->pos_vec, res.inter_pos));
        res.color = cy_obj->color;
    }
    return (res);
}


//オブジェクトにより交点の計算方法を変更する
// 1: t_minirt *world -> 全体の情報を持つ構造体
// 2: t_objects tmp_o_list -> オブジェクトリストのノード
// 3: t_ray ray -> 交差判定をするレイ
t_vec_info	calc_sh_intersection(t_minirt *world, t_objects node, t_ray ray)
{
	t_vec_info	non;

	non.t = -1;
	if (node.obj_type == t_pl)
		return (pl_intersection(world, node, ray));
	else if (node.obj_type == t_sp)
		return (sp_intersection(world, node, ray));
	else if (node.obj_type == t_cy)
		return (cy_sh_intersecton(world, node, ray));
	return (non);
}
*/


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
