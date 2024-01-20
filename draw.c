#include "minirt.h"

//内積を計算
double InnerProduct(t_vec a, t_vec b){
  return (a.x * b.x + a.y * b.y + a.z * b.z);
}

//平面オブジェクトとレイの交点を求める
double pl_intersection(int x, int y, t_minirt *global_info, t_objects *tmp_o_list){
		t_plane *pl_obj;
		t_vec s_vec;
		t_vec d_vec;
		double t;

		pl_obj = tmp_o_list->content;

		//視点（カメラ）と物体の距離
		s_vec.x = global_info->cam->view_vec.x - pl_obj->point_vec.x;
		s_vec.y = global_info->cam->view_vec.y - pl_obj->point_vec.y;
		s_vec.z = global_info->cam->view_vec.z - pl_obj->point_vec.z;

		// d_vec.x = x + 0.5 - s_vec.x;
		// d_vec.y = y + 0.5 - s_vec.y;
		// // d_vec.z = global_info->cam->view_vec.z

		t = -((InnerProduct(s_vec, pl_obj->normal_vec)/(InnerProduct(global_info->cam->ori_vec, pl_obj->normal_vec))));
		return (t);
}

//判別式Dを求める
double get_sp_test_condition(t_minirt *global_info, t_vec vec, int x, int y, double r){
	double A;
	double B2;
	double C;
	double D;
	t_vec d_vec;

	// d_vec.x = x + 0.5 - vec.x;
	// d_vec.y = y + 0.5 - vec.y;
	// d_vec.z = 0 - r;
	A = InnerProduct(global_info->cam->ori_vec, global_info->cam->ori_vec);
	B2 = InnerProduct(vec, global_info->cam->ori_vec);
	C = InnerProduct(vec, vec) - r*r;
	D =B2*B2-A*C;
	if(D >= 0)
		return ((-B2-sqrt(D))/A);
	return 0;
}

//球体のオブジェクトとレイの交点を求める
double sp_intersection(int x, int y, t_minirt *global_info, t_objects *tmp_o_list){
	t_vec pvc;
	t_sphere *sp_obj;
	double t;

	sp_obj = tmp_o_list->content;

	pvc.x = global_info->cam->view_vec.x - sp_obj->center_vec.x;
	pvc.y = global_info->cam->view_vec.y - sp_obj->center_vec.y;
	pvc.z = global_info->cam->view_vec.z - sp_obj->center_vec.z;

	t = get_sp_test_condition(global_info, pvc, x, y,sp_obj->diameter);
	return (t);
}

//交点を計算する
t_objects *get_intersection(int x, int y, t_minirt *global_info, int *t){
	int i;
	int obj_size;
	t_objects *tmp_o_list;
	double tmp_t;
	t_objects *tmp_node;


	i = 0;
	tmp_o_list = global_info->objs;
	obj_size = get_obj_size(tmp_o_list);
	tmp_node = NULL;
	//全てのオブジェクトに対して計算する
	while(i < obj_size){
		if(tmp_o_list->obj_type == t_pl){
			tmp_t = pl_intersection(x, y, global_info, tmp_o_list);
		}
		else if(tmp_o_list->obj_type == t_sp){
			tmp_t = sp_intersecton(x, y, global_info, tmp_o_list);
		}
		// 円柱
		// else if(tmp_o_list->obj_type == t_cy){
		// 	tmp_t = cy_intersecton();
		// }

		//tmp_t交点が，現在見つかっている最も近い交点よりも近いならその情報を記憶する
		if(tmp_t < *t){
			*t = tmp_t;
			tmp_node = tmp_o_list;
		}
		tmp_o_list = tmp_o_list->next;
		i++;
	}
	return (tmp_node);
}

bool draw (t_minirt *global_info){
	int x;
	int y;
	int obj_no;
	double t;
	t_objects *node;
	int color_h;



	x = - (WIDTH);
	y = -(HEIGHT);
	obj_no = -1;

	while (x <= WIDTH)
	{
		while (y <= HEIGHT)
		{
			// 交点を計算する
			node = get_intersection(x, y, global_info, &t);
			//交点があれば
			if(node){
				//環境光の反射光の放射輝度を計算して【放射輝度】に代入
				//for(全ての光源について繰り返す) {
					//      光源iによるライティングを計算する．

					//      光源iからの光の拡散反射光の放射輝度を計算して【放射輝度】に加算する．

					//      光源iからの光の鏡面反射光の放射輝度を計算して【放射輝度】に加算する．
					//    }

				//    【放射輝度】を色に変換して描画色に設定する．
			}
			else{
				//背景
				color_h = argb_to_hex(0, RGB_back);
				my_mlx_pixel_put(&img, i+ WIDTH/2, j+ HEIGHT/2, color_h);
        	}


			y++;
		}

		x++;
	}

}