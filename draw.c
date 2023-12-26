#include "minirt.h"

void get_distance(double **distance, t_objects *tmp_o_list, t_minirt *global_info){
	t_sphere *sp_tmp;
	t_plane *pl_tmp;
	t_cylinder *cy_tmp;

	if (tmp_o_list->obj_type == t_sp){
		sp_tmp = tmp_o_list->content;
		*distance[0] = global_info->cam->view_vec.x - sp_tmp->center_vec.x;
		*distance[1] = global_info->cam->view_vec.y - sp_tmp->center_vec.y;
		*distance[2] = global_info->cam->view_vec.z - sp_tmp->center_vec.z;
	}
	else if (tmp_o_list->obj_type == t_pl){
		pl_tmp = tmp_o_list->content;
		*distance[0] = global_info->cam->view_vec.x - pl_tmp->point_vec.x;
		*distance[1] = global_info->cam->view_vec.y - pl_tmp->point_vec.y;
		*distance[2] = global_info->cam->view_vec.z - pl_tmp->point_vec.z;
	}
	else if (tmp_o_list->obj_type == t_cy){
		cy_tmp = tmp_o_list->content;
		*distance[0] = global_info->cam->view_vec.x - sp_tmp->center_vec.x;
		*distance[1] = global_info->cam->view_vec.y - sp_tmp->center_vec.y;
		*distance[2] = global_info->cam->view_vec.z - sp_tmp->center_vec.z;
	}
}


double pl_intersection(t_minirt *global_info, t_objects *tmp_o_list){
		t_plane *pl_obj;

		pl_obj = tmp_o_list->content;


}

double get_intersection(int x, int y, t_minirt *global_info){
	int i;
	int obj_size;
	t_objects *tmp_o_list;
	double t;
	double tmp_t;


	i = 0;

	tmp_o_list = global_info->objs;
	obj_size = get_obj_size(tmp_o_list);
	//全てのオブジェクトに対して計算する
	while(i < obj_size){
		if(tmp_o_list->obj_type == t_pl){
			tmp_t = pl_intersection();
		}
		else if(tmp_o_list->obj_type == t_sp){
			tmp_t = sp_intersecton();
		}
		else if(tmp_o_list->obj_type == t_cy){
			tmp_t = cy_intersecton();
		}
		//tmp_t交点が，現在見つかっている最も近い交点よりも近いならその情報を記憶する
		if(tmp_t < t){
			t = tmp_t;
		}
		tmp_o_list = tmp_o_list->next;
		i++;
	}
	return (t);

}

bool draw (t_minirt *global_info){
	int x;
	int y;
	int obj_no;


	x = - (WIDTH);
	y = -(HEIGHT);
	obj_no = -1;


	while (x <= WIDTH)
	{
		while (y <= HEIGHT)
		{
			// 交点を計算する
			get_intersection();
			//交点があれば
			 //環境光の反射光の放射輝度を計算して【放射輝度】に代入
			 //for(全ての光源について繰り返す) {
   				//      光源iによるライティングを計算する．

    			//      光源iからの光の拡散反射光の放射輝度を計算して【放射輝度】に加算する．

   				//      光源iからの光の鏡面反射光の放射輝度を計算して【放射輝度】に加算する．
    			//    }

    		//    【放射輝度】を色に変換して描画色に設定する．


			y++;
		}

		x++;
	}

}