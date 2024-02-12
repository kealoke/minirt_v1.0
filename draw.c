#include "minirt.h"

double clamp(double value, double min, double max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;

}
//内積を計算
double	InnerProduct(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

//ベクトルの足し算
t_vec add_vec(t_vec a, t_vec b){
	t_vec res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

//ベクトルの引き算
t_vec sub_vec(t_vec a, t_vec b){
	t_vec res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

t_vec mul_vec(t_vec a, double b){
	t_vec res;

	res.x = a.x * b;
	res.y = a.y * b;
	res.z = a.z * b;
	return res;
}

// ベクトルの正規化
t_vec	vec_normalize(t_vec a)
{
	t_vec res;
	double mag = sqrt(InnerProduct(a,a));
	res.x = a.x / mag;
	res.y = a.y / mag;
	res.z = a.z / mag;
	return (res);
}

// ベクトルのノルムを求める
double get_vec_norm(t_vec a){
	double res;

	res = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return res;
}

//color構図体からintに変換する
int	argb_to_hex(t_color color)
{
	int	res_color;
	unsigned int a;

	a = 0;
	res_color = ((a & 0xFF) << 24) | ((color.r & 0xFF) << 16) | ((color.g & 0xFF) << 8) | (color.b & 0xFF);
	return (res_color);
}

//平面オブジェクトとレイの交差判定をする
t_vec_info	pl_intersection(t_minirt *global_info, t_objects *tmp_o_list, t_vec dir_vec)
{
	t_plane	*pl_obj;
	t_vec	s_vec;
	t_vec_info res;
	// double	t;

	pl_obj = tmp_o_list->content;
	//視点（カメラ）と物体の距離
	s_vec.x = global_info->cam->view_vec.x - pl_obj->point_vec.x;
	s_vec.y = global_info->cam->view_vec.y - pl_obj->point_vec.y;
	s_vec.z = global_info->cam->view_vec.z - pl_obj->point_vec.z;
	// d_vec.x = x + 0.5 - s_vec.x;
	// d_vec.y = y + 0.5 - s_vec.y;
	// // d_vec.z = global_info->cam->view_vec.z
	res.t = -((InnerProduct(s_vec, pl_obj->normal_vec) / (InnerProduct(dir_vec, pl_obj->normal_vec))));
	if(res.t > 0){
		res.normal = pl_obj->normal_vec;
		res.color = pl_obj->color;
		t_vec init_pos = add_vec(global_info->cam->view_vec, mul_vec(dir_vec, res.t));
		res.light_dir = vec_normalize(sub_vec(global_info->light->point_vec, init_pos));
	}
	return (res);
}

//判別式Dを計算し、tを求める
double	get_sp_test_condition(t_vec vec, double r, t_vec dir_vec)
{
	double	A;
	double	B;
	double	C;
	double	D;
	// t_vec	d_vec;

	// d_vec.x = x + 0.5 - vec.x;
	// d_vec.y = y + 0.5 - vec.y;
	// d_vec.z = 0 - r;
	A = InnerProduct(dir_vec, dir_vec);
	B = InnerProduct(vec, dir_vec) * 2;
	C = InnerProduct(vec, vec) - r * r;
	D = B * B - 4 * A * C;
	// return D;
	if(D == 0){
		return (-B / (2*A));
	}
	else if (D > 0){
		double t1 = (-B - sqrt(D)) / (2*A);
		double t2 = (-B + sqrt(D)) / (2*A);
		// カメラに近い方の交点を選択
		if (t1 > 0 && t1 < t2) return t1;
		if (t2 > 0) return t2;
	}
	return (D);
}

//球体のオブジェクトとレイの交差判定をしてベクトル情報を返す
t_vec_info	sp_intersection(t_minirt *global_info, t_objects *tmp_o_list, t_vec dir_vec)
{
	t_vec		pvc;
	t_sphere	*sp_obj;
	// double		t;
	t_vec_info res;

	sp_obj = tmp_o_list->content;
	pvc = sub_vec(global_info->cam->view_vec, sp_obj->center_vec);
	res.t = get_sp_test_condition(pvc, sp_obj->diameter, dir_vec);

	if(res.t > 0){
		//交点位置
		t_vec init_pos = add_vec(global_info->cam->view_vec, mul_vec(dir_vec, res.t));
		// 法線ベクトル
		res.normal = vec_normalize(sub_vec(init_pos, sp_obj->center_vec));
		// 入射ベクトル
		res.light_dir = vec_normalize(sub_vec(global_info->light->point_vec, init_pos));
		res.color = sp_obj->color;
	}
	return (res);
}


//交点を計算する
t_vec_info get_intersection(t_minirt *global_info, t_vec dir_vec)
{
	t_objects	*tmp_o_list;
	t_vec_info closest;
	t_vec_info tmp;

	closest.t = INFINITY; // 最も近い交点までの距離
    // t_objects *closest_obj = NULL; // 最も近いオブジェクト

	tmp_o_list = global_info->objs;

	//全てのオブジェクトに対して計算する
	while (tmp_o_list != NULL)
	{
		if (tmp_o_list->obj_type == t_pl)
		{
			tmp = pl_intersection(global_info, tmp_o_list, dir_vec);
		}
		else if (tmp_o_list->obj_type == t_sp)
		{
			tmp = sp_intersection(global_info, tmp_o_list, dir_vec);
		}
		// 円柱
		// else if(tmp_o_list->obj_type == t_cy){
		// 	tmp_t = cy_intersecton();
		// }
		//tmp_t交点が，現在見つかっている最も近い交点よりも近いならその情報を記憶する
		if (tmp.t > 0 && tmp.t < closest.t)
        {
            closest = tmp;
        }
		tmp_o_list = tmp_o_list->next;
	}
	closest.t = closest.t != INFINITY ? closest.t : -1;

	return closest;
}


// int set_obj_lighting(t_minirt *global_info, double t, t_objects *node){
// 	t_vec *p;
// 	t_vec *n;
// 	int i;

// 	//視点と物体の交点を計算する
// 	p = plus_vec(global_info->cam->view_vec, global_info->cam->ori_vec, t);
// 	//法線
// 	if(node->obj_type == )
// 	n = minus_vec(p, )


// }

void calculate_ref(){

}

bool	draw(t_minirt *global_info, t_mlx *mlx)
{
	int  x;
	int  y;
	t_vec_info closest_obj;
	int color = 0;


	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "MiniRT");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &(mlx->bits_per_pixel), &(mlx->line_length), &(mlx->endian));

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			//ワールドベクトルに変換する
			t_vec screen_vec;
			screen_vec.x = 2 * x / (WIDTH - 1.0);
			screen_vec.y = 2 * y / (HEIGHT - 1.0);
			screen_vec.z = 0;
			// 方向ベクトル
			t_vec dir_vec;
			dir_vec = vec_normalize(sub_vec(screen_vec, global_info->cam->view_vec));

			// 視点とぶつかるオブジェクトを計算する
			closest_obj = get_intersection(global_info, dir_vec);
			//交点があれば
			if (closest_obj.t > 0)
			{
				//環境光の放射輝度
				double ambient_ref;
				double ambient_k = 1;
				ambient_ref = ambient_k * global_info->amb->light_range;
				//拡散反射の放射輝度
				double diffuse_ref;
				double diffuse_k = 1;
				double nl = InnerProduct(closest_obj.light_dir, closest_obj.normal);
				if(nl < 0)
					nl = 0;
				diffuse_ref = global_info->light->brightness * diffuse_k * nl;
				//鏡面反射の放射輝度
				double supecular_ref;
				double supecular_k = 1;
				if(nl > 0){
					//正反射ベクトルを求める
					t_vec r;
					r.x = closest_obj.light_dir.x - 2 * nl * closest_obj.normal.x;
					r.y = closest_obj.light_dir.y - 2 * nl * closest_obj.normal.y;
					r.z = closest_obj.light_dir.z - 2 * nl * closest_obj.normal.z;
					//視線ベクトルの逆ベクトル
					t_vec v = vec_normalize(mul_vec(dir_vec, -1));
					double vr = InnerProduct(v, r);
					if(vr < 0)
						vr = 0;
					supecular_ref = global_info->light->brightness * supecular_k * pow(vr, 5.0);
				}
				else{
					supecular_ref = 0;
				}
				double ref_light = diffuse_ref + supecular_ref;
				// double ref_light =  diffuse_ref;


				closest_obj.color.r *= ref_light;
				closest_obj.color.g *= ref_light;
				closest_obj.color.b *= ref_light;

				color = argb_to_hex((closest_obj.color));

				//環境光の反射光の放射輝度を計算して【放射輝度】に代入
				//for(全ての光源について繰り返す) {
				//      光源iによるライティングを計算する．

				//      光源iからの光の拡散反射光の放射輝度を計算して【放射輝度】に加算する．

				//      光源iからの光の鏡面反射光の放射輝度を計算して【放射輝度】に加算する．
				//    }

				//    【放射輝度】を色に変換して描画色に設定する．
				my_mlx_pixel_put(mlx, x , y, color);
			}
			else
			{
				//背景
				my_mlx_pixel_put(mlx, x, y, 0x00000000);
			}
			// if( 100<x && x>200 && 100<y && y>100){

			// 	my_mlx_pixel_put(mlx, x, y, 0x000000FF);
			// }
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img, 0, 0);
	mlx_hook(mlx->window, 17, 0, close_win, mlx);
	mlx_loop(mlx->mlx);
	return (true);
}

// bool	draw2(t_minirt *global_info, t_mlx *mlx)
// {
// 	int  x;
// 	int  y;
// 	// double t;
// 	// double ttt;
// 	t_objects *node;
// 	// int			i;
// 	int			obj_size;
// 	t_objects	*tmp_o_list;
// 	// double		tmp_t = 0;
// 	t_objects	*tmp_node;
// 	t_vec		pvc;
// 	t_sphere	*sp_obj;
// 	double	A;
// 	double	B2;
// 	double	C;
// 	double	D= -1;

// 	x = 0;

// 	mlx->mlx = mlx_init();
// 	mlx->window = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "MiniRT");
// 	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
// 	mlx->addr = mlx_get_data_addr(mlx->img, &(mlx->bits_per_pixel), &(mlx->line_length), &(mlx->endian));
// 	while (x < WIDTH)
// 	{
// 		y = 0;
// 		while (y < HEIGHT)
// 		{
// 			D = -1;
// 			node = NULL;
// 			tmp_o_list = global_info->objs;
// 			obj_size = get_obj_size(tmp_o_list);
// 			tmp_node = NULL;

// 			t_vec screen_vec;
// 			screen_vec.x = 2 * x / (WIDTH - 1.0);
// 			screen_vec.y = 2 * y / (HEIGHT - 1.0);
// 			screen_vec.z = 0;
// 			// 方向ベクトル
// 			t_vec dir_vec;
// 			dir_vec = vec_normalize(sub_vec(screen_vec, global_info->cam->view_vec));

// 			while (tmp_o_list != NULL)
// 			{
// 				if (tmp_o_list->obj_type == t_sp)
// 				{
// 					sp_obj = tmp_o_list->content;
// 					pvc = sub_vec(global_info->cam->view_vec, sp_obj->center_vec);

// 					A = vec_get_norm(dir_vec) * vec_get_norm(dir_vec);
// 					B2 = InnerProduct(pvc, dir_vec) * 2;
// 					C = InnerProduct(pvc, pvc) - sp_obj->diameter * sp_obj->diameter;
// 					D = B2 * B2 - 4 * A * C;
// 				}
// 				tmp_o_list = tmp_o_list->next;
// 			}
// 			if(D >= 0){
// 				my_mlx_pixel_put(mlx, x , y, 0x000000FF);
// 			}
// 			else
// 			{
// 				//背景
// 				my_mlx_pixel_put(mlx, x, y, 0x00FFFFFF);
// 			}
// 			// if( 100<x && x>200 && 100<y && y>100){

// 			// 	my_mlx_pixel_put(mlx, x, y, 0x000000FF);
// 			// }
// 			y++;
// 		}
// 		x++;
// 	}
// 	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img, 0, 0);
// 	mlx_hook(mlx->window, 17, 0, close_win, mlx);
// 	mlx_loop(mlx->mlx);
// 	return (true);
// }