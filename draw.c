#include "minirt.h"

//ベクトルの足し算
t_vec add_vec(t_vec a, t_vec b, double t){
	t_vec res;

	res.x = a.x + b.x * t;
	res.y = a.y + b.y * t;
	res.z = a.z + b.z * t;
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


//color構図体からintに変換する
int	argb_to_hex(t_color *color)
{
	int	res_color;
	int	a;

	a = 255;
	res_color = ((a & 0xFF) << 24) | ((color->r & 0xFF) << 16) | ((color->g & 0xFF) << 8) | (color->b & 0xFF);
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
	double	B2;
	double	C;
	double	D;
	// t_vec	d_vec;

	// d_vec.x = x + 0.5 - vec.x;
	// d_vec.y = y + 0.5 - vec.y;
	// d_vec.z = 0 - r;
	A = InnerProduct(dir_vec, dir_vec);
	B2 = InnerProduct(vec, dir_vec);
	C = InnerProduct(vec, vec) - r * r;
	D = B2 * B2 - A * C;
	if (D >= 0)
		return ((-B2 - sqrt(D)) / A);
	return (-1);
}

//球体のオブジェクトとレイの交差判定をする
double	sp_intersection(t_minirt *global_info, t_objects *tmp_o_list, t_vec dir_vec)
{
	t_vec		pvc;
	t_sphere	*sp_obj;
	double		t;

	sp_obj = tmp_o_list->content;
	pvc.x = global_info->cam->view_vec.x - sp_obj->center_vec.x;
	pvc.y = global_info->cam->view_vec.y - sp_obj->center_vec.y;
	pvc.z = global_info->cam->view_vec.z - sp_obj->center_vec.z;
	t = get_sp_test_condition(pvc, sp_obj->diameter, dir_vec);
	return (t);
}

// ベクトルの正規化
t_vec	vec_normalize(t_vec a)
{
	t_vec res;
	double mag = InnerProduct(a,a);
	res.x = a.x / mag;
	res.y = a.y / mag;
	res.z = a.z / mag;
	return (res);
}


//交点を計算する
t_objects	*get_intersection(int x, int y, t_minirt *global_info, double *t)
{
	int			i;
	int			obj_size;
	t_objects	*tmp_o_list;
	double		tmp_t;
	t_objects	*tmp_node;

	i = 0;
	*t = 0;
	tmp_o_list = global_info->objs;
	obj_size = get_obj_size(tmp_o_list);
	tmp_node = NULL;

	t_vec screen_vec;
	screen_vec.x = 2 * x / WIDTH - 1.0;
	screen_vec.y = 2 * y / HEIGHT - 1.0;
	screen_vec.z = 0;
	// 方向ベクトル
	t_vec dir_vec;
	dir_vec = vec_normalize(sub_vec(screen_vec, global_info->cam->view_vec));


	//全てのオブジェクトに対して計算する
	while (i < obj_size)
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
		if (tmp_t < *t || i == 0)
		{
			*t = tmp_t;
			tmp_node = tmp_o_list;
		}
		tmp_o_list = tmp_o_list->next;
		i++;
	}
	// printf("%p\n", tmp_node);
	return (tmp_node);
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

bool	draw(t_minirt *global_info)
{
	int x;
	int y;
	double t;
	t_objects *node;

	x = -(WIDTH);
	y = -(HEIGHT);
	node = NULL;

	global_info->libs = my_malloc(sizeof(t_libx));
	global_info->libs->data = my_malloc(sizeof(t_data));

	global_info->libs->mlx = mlx_init();
	global_info->libs->window = mlx_new_window(global_info->libs->mlx, WIDTH,
			HEIGHT, "MiniRT");
	global_info->libs->data->img = mlx_new_image(global_info->libs->mlx, WIDTH,
			HEIGHT);
	global_info->libs->data->addr = mlx_get_data_addr(global_info->libs->data->img,
			&global_info->libs->data->bits_per_pixel,
			&global_info->libs->data->line_length,
			&global_info->libs->data->endian);

	while (x <= WIDTH)
	{
		while (y <= HEIGHT)
		{
			// 交点を計算する
			node = get_intersection(x, y, global_info, &t);
			//交点があれば
			if (node)
			{
				// int color = 0;

				// if(node->obj_type == t_sp){
				// 	t_sphere *sp_tmp = node->content;
				// 	color = argb_to_hex(&(sp_tmp->color));
				// }
				// else if(node->obj_type == t_pl){
				// 	t_sphere *pl_tmp = node->content;
				// 	color = argb_to_hex(&(pl_tmp->color));
				// }
				// printf("%d\n", color);
				my_mlx_pixel_put(global_info->libs->data, x + WIDTH / 2, y
						+ HEIGHT / 2, 0xFFFFFF);
				//環境光の反射光の放射輝度を計算して【放射輝度】に代入
				//for(全ての光源について繰り返す) {
				//      光源iによるライティングを計算する．

				//      光源iからの光の拡散反射光の放射輝度を計算して【放射輝度】に加算する．

				//      光源iからの光の鏡面反射光の放射輝度を計算して【放射輝度】に加算する．
				//    }

				//    【放射輝度】を色に変換して描画色に設定する．
			}
			else
			{
				//背景
				my_mlx_pixel_put(global_info->libs->data, x + WIDTH / 2, y
						+ HEIGHT / 2, 0x000000);
			}
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(global_info->libs->mlx, global_info->libs->window,
			global_info->libs->data->img, 0, 0);
	mlx_hook(global_info->libs->window, 17, 0, close_win, global_info->libs);
	mlx_loop(global_info->libs->mlx);
	return (true);
}