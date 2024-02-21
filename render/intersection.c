#include "../minirt.h"

//オブジェクトにより交点の計算方法を変更する
// 1: t_minirt *world -> 全体の情報を持つ構造体
// 2: t_objects tmp_o_list -> オブジェクトリストのノード
// 3: t_ray ray -> 交差判定をするレイ
t_vec_info	calc_intersection(t_minirt *world, t_objects node, t_ray ray)
{
	t_vec_info	non;

	non.t = -1;
	if (node.obj_type == t_pl)
		return (pl_intersection(world, node, ray));
	else if (node.obj_type == t_sp)
		return (sp_intersection(world, node, ray));
	else if (node.obj_type == t_cy)
		return (cy_intersecton(world, node, ray));
	return (non);
}

//レイとオブジェクトの交点を取得する
//1: t_minirt *world ->ワールド変数
//2: t_vec dir_vec -> ワールドに変換したレイの方向ベクトル
t_vec_info	get_intersection(t_minirt *world, t_ray ray)
{
	t_objects	*tmp_o_list;
	t_vec_info	closest;
	t_vec_info	tmp;

	// 最も近い交点までの距離
	closest.t = INFINITY;
	tmp_o_list = world->objs;
	//全てのオブジェクトに対して計算する
	while (tmp_o_list != NULL)
	{
		tmp = calc_intersection(world, *tmp_o_list, ray);
		if (tmp.t > 0 && tmp.t < closest.t)
		{
			closest = tmp;
		}
		tmp_o_list = tmp_o_list->next;
	}
	if (closest.t == INFINITY)
		closest.t = -1;
	return (closest);
}
