#include "minirt.h"

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

//内積を計算
double	InnerProduct(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

//平面オブジェクトとレイの交差判定をする
double	pl_intersection(t_minirt *global_info, t_objects *tmp_o_list, t_vec dir_vec)
{
	t_plane	*pl_obj;
	t_vec	s_vec;
	// t_vec	d_vec;
	double	t;

	pl_obj = tmp_o_list->content;
	//視点（カメラ）と物体の距離
	s_vec.x = global_info->cam->view_vec.x - pl_obj->point_vec.x;
	s_vec.y = global_info->cam->view_vec.y - pl_obj->point_vec.y;
	s_vec.z = global_info->cam->view_vec.z - pl_obj->point_vec.z;
	// d_vec.x = x + 0.5 - s_vec.x;
	// d_vec.y = y + 0.5 - s_vec.y;
	// // d_vec.z = global_info->cam->view_vec.z
	t = -((InnerProduct(s_vec, pl_obj->normal_vec)
				/ (InnerProduct(dir_vec,
						pl_obj->normal_vec))));
	return (t);
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
	if (D >= 0){
		double t1 = (-B - sqrt(D)) / (2*A);
		double t2 = (-B + sqrt(D)) / (2*A);
		// カメラに近い方の交点を選択
		if (t1 > 0 && t1 < t2) return t1;
		if (t2 > 0) return t2;
	}
	return (D);
}

//球体のオブジェクトとレイの交差判定をする
double	sp_intersection(t_minirt *global_info, t_objects *tmp_o_list, t_vec dir_vec)
{
	t_vec		pvc;
	t_sphere	*sp_obj;
	double		t;

	sp_obj = tmp_o_list->content;
	pvc = sub_vec(global_info->cam->view_vec, sp_obj->center_vec);
	t = get_sp_test_condition(pvc, sp_obj->diameter, dir_vec);
	// printf ("vec %f\n", sp_obj->center_vec.z);
	return (t);
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


//交点を計算する
t_objects *get_intersection(int x, int y, t_minirt *global_info, double *t)
{
	t_objects	*tmp_o_list;
	double		tmp_t = 0;

	double closest_t = INFINITY; // 最も近い交点までの距離
    t_objects *closest_obj = NULL; // 最も近いオブジェクト

	tmp_o_list = global_info->objs;

	t_vec screen_vec;
	screen_vec.x = 2 * x / (WIDTH - 1.0);
	screen_vec.y = 2 * y / (HEIGHT - 1.0);
	screen_vec.z = 0;
	// 方向ベクトル
	t_vec dir_vec;
	dir_vec = vec_normalize(sub_vec(screen_vec, global_info->cam->view_vec));

	//全てのオブジェクトに対して計算する
	while (tmp_o_list != NULL)
	{
		if (tmp_o_list->obj_type == t_pl)
		{
			tmp_t = pl_intersection(global_info, tmp_o_list, dir_vec);
		}
		else if (tmp_o_list->obj_type == t_sp)
		{
			tmp_t = sp_intersection(global_info, tmp_o_list, dir_vec);
		}
		// 円柱
		// else if(tmp_o_list->obj_type == t_cy){
		// 	tmp_t = cy_intersecton();
		// }
		//tmp_t交点が，現在見つかっている最も近い交点よりも近いならその情報を記憶する
		if (tmp_t > 0 && tmp_t < closest_t)
        {
            closest_t = tmp_t;
            closest_obj = tmp_o_list;
        }
		tmp_o_list = tmp_o_list->next;
	}
	*t = closest_t != INFINITY ? closest_t : -1;
	return closest_obj;
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

bool	draw(t_minirt *global_info, t_mlx *mlx)
{
	int  x;
	int  y;
	double t;
	t_objects *node;

	x = 0;

	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "MiniRT");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &(mlx->bits_per_pixel), &(mlx->line_length), &(mlx->endian));
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			node = NULL;
			// 交点を計算する
			t = 0;
			node = get_intersection(x, y, global_info, &t);
			//交点があれば
			if (t > 0)
			{
				int color = 0;

				if(node->obj_type == t_sp){
					t_vec screen_vec;
					screen_vec.x = 2 * x / (WIDTH - 1.0);
					screen_vec.y = 2 * y / (HEIGHT - 1.0);
					screen_vec.z = 0;
					// 方向ベクトル
					t_vec dir_vec;
					dir_vec = vec_normalize(sub_vec(screen_vec, global_info->cam->view_vec));

					t_sphere sp_tmp = *(t_sphere*)node->content;
					//交点位置
					t_vec init_pos = add_vec(global_info->cam->view_vec, mul_vec(dir_vec, t));

					// 入射ベクトル
					t_vec light_dir = sub_vec(global_info->light->point_vec, init_pos);
					light_dir = vec_normalize(light_dir);

					// 法線ベクトル
					t_vec sp_n = sub_vec(init_pos, sp_tmp.center_vec);
					sp_n = vec_normalize(sp_n);

					dprintf(2, "normal x-%f y-%f z-%f\n", sp_n.x,sp_n.y,sp_n.z);


					double cos_a = InnerProduct(light_dir, sp_n);
					if(cos_a < 0)
						cos_a = 0;


					sp_tmp.color.r *= cos_a * global_info->light->color.r * global_info->light->brightness;
					sp_tmp.color.g *= cos_a * global_info->light->color.g * global_info->light->brightness;
					sp_tmp.color.b *= cos_a * global_info->light->color.b * global_info->light->brightness;

					color = argb_to_hex((sp_tmp.color));
					printf("color %x\n",color);
				}
				else if(node->obj_type == t_pl){
					t_plane *pl_tmp = node->content;
					color = argb_to_hex((pl_tmp->color));
				}
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
				my_mlx_pixel_put(mlx, x, y, 0x00FF0000);
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