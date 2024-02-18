#include "../minirt.h"

//数値を範囲内に収める(min-max)
double clamp(double value, double min, double max) {
    if (value < min)
		return min;
    if (value > max)
		return max;
    return value;
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

//平面オブジェクトとレイの交差判定をする
t_vec_info	pl_intersection(t_minirt *world, t_objects tmp_o_list, t_ray ray)
{
	t_plane	*pl_obj;
	t_vec	s_vec;
	t_vec_info res;

	pl_obj = tmp_o_list.content;
	//視点（カメラ）と物体の距離
	s_vec = sub_vec(ray.pos, pl_obj->pos_vec);
	double denom = InnerProduct(ray.dir, pl_obj->normal_vec);
	if (fabs(denom) > 1e-6) { // 1e-6は0に非常に近い値を表す閾値
		res.t = (-(InnerProduct(s_vec, pl_obj->normal_vec) / denom));
		if(res.t >= 0){
			res.normal = vec_normalize(pl_obj->normal_vec);
			res.color = pl_obj->color;
			res.inter_pos = add_vec(ray.pos, mul_vec(ray.dir, res.t));
			res.light_dir = vec_normalize(sub_vec(world->light->pos_vec, res.inter_pos));
		}
	}
	else
		res.t = -1;
	return (res);
}

//判別式Dを計算し、tを求める
double	get_sp_test_condition(t_vec vec, double r, t_vec dir_vec)
{
	double	a;
	double	b;
	double	c;
	double	d;

	a = InnerProduct(dir_vec, dir_vec);
	b = InnerProduct(vec, dir_vec) * 2;
	c = InnerProduct(vec, vec) - r * r;
	d = b * b - 4 * a * c;
	if(d == 0){
		return ((-b - sqrt(d)) / (2*a));
	}
	else if (d > 0){
		double t1 = (-b - sqrt(d)) / (2*a);
		double t2 = (-b + sqrt(d)) / (2*a);
		// カメラに近い方の交点を選択
		if (t1 > 0 && t1 < t2)
			return t1;
		if (t2 > 0)
			return t2;
	}
	return (d);
}

//球体のオブジェクトとレイの交差判定をしてベクトル情報を返す
t_vec_info	sp_intersection(t_minirt *world, t_objects tmp_o_list, t_ray ray)
{
	t_vec		pvc;
	t_sphere	*sp_obj;
	t_vec_info res;

	sp_obj = tmp_o_list.content;
	pvc = sub_vec(ray.pos, sp_obj->center_vec);
	res.t = get_sp_test_condition(pvc, sp_obj->diameter, ray.dir);

	if(res.t > 0){
		//交点位置
		res.inter_pos = add_vec(ray.pos, mul_vec(ray.dir, res.t));
		// 法線ベクトル
		res.normal = vec_normalize(sub_vec(res.inter_pos, sp_obj->center_vec));
		// 入射ベクトル
		res.light_dir = vec_normalize(sub_vec(world->light->pos_vec, res.inter_pos));
		res.color = sp_obj->color;
	}
	return (res);
}

//オブジェクトにより計算方法を変更する
t_vec_info calc_intersection(t_minirt *world,t_objects node, t_ray ray){

	t_vec_info non;

	non.t = -1;

	if (node.obj_type == t_pl)
			return (pl_intersection(world, node, ray));
	else if (node.obj_type == t_sp)
			return (sp_intersection(world, node, ray));
		// 円柱
		// else if(tmp_o_list->obj_type == t_cy){
		// 	tmp_t = cy_intersecton();
		// }
		//tmp_t交点が，現在見つかっている最も近い交点よりも近いならその情報を記憶する
	return non;
}


//レイとオブジェクトの交点を取得する
//1: t_minirt *world ->ワールド変数
//2: t_vec dir_vec -> ワールドに変換したレイの方向ベクトル
t_vec_info get_intersection(t_minirt *world, t_ray ray)
{
	t_objects	*tmp_o_list;
	t_vec_info closest;
	t_vec_info tmp;

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
	closest.t = closest.t != INFINITY ? closest.t : -1;

	return closest;
}


//環境光の放射輝度を反映したカラーを取得
t_color get_ambient(t_minirt *world){
	t_light_color amb_color;
	t_color res;
	// double r;
	// double g;
	// double b;
	double ambient_ref;
	double ambient_k = 0.1;

	ambient_ref = ambient_k * world->amb->light_intensity;

	// r = ((double)world->amb->color.r)/255.0;
	// g = ((double)world->amb->color.g)/255.0;
	// b = ((double)world->amb->color.b)/255.0;
	amb_color = mul_li_color(world->amb->color, ambient_ref);

	res = sca_mul_color(get_color_vec(255,255,255), ambient_ref);
	return res;
}

//拡散反射の放射輝度を反映したカラーを取得
t_color get_diffuse(t_minirt *world, t_vec_info closest_obj){
	t_light_color dif_color;
	t_color res;
	double diffuse_ref;
	double diffuse_k = 0.5;

	double nl = InnerProduct(closest_obj.light_dir, closest_obj.normal);
	if(nl < 0)
		nl = 0;

	diffuse_ref = diffuse_k * nl * world->light->brightness;

	//ライトカラーと拡散反射の輝度をかける
	dif_color = mul_li_color(world->light->color, diffuse_ref);
	// dif_color = sca_mul_color(world->light->color, diffuse_ref);

	//物体のカラーとライトカラーをかける
	// dif_color = mul_li_ob(dif_color, closest_obj.color);
	res = sca_mul_color(get_color_vec(255,255,255), diffuse_ref);

	return res;
}

t_color get_supecular(t_minirt *world, t_vec_info closest_obj, t_vec dir_vec){

	//鏡面反射の放射輝度
	double supecular_ref;
	double supecular_k = 0.3;
	t_light_color sup_color;
	t_color res;

	double nl = InnerProduct(closest_obj.light_dir, closest_obj.normal);
	if(nl > 0){
		//正反射ベクトルを求める
		t_vec r;
		r = vec_normalize(sub_vec(mul_vec(mul_vec(closest_obj.normal, nl),2), closest_obj.light_dir));

		//視線ベクトルの逆ベクトル
		t_vec v =  vec_normalize(mul_vec(dir_vec, -1));
		double vr = InnerProduct(v, r);

		if(vr < 0)
			vr = 0;
		supecular_ref = supecular_k * world->light->brightness * pow(vr, 10.0);
	}
	else{
		supecular_ref = 0;
	}
	sup_color = mul_li_color(world->light->color, supecular_ref);
	res = sca_mul_color(get_color_vec(255,255,255), supecular_ref);

	return res;
}

//物体にシャドウがかかるかチェックする
bool check_shadow(t_minirt *world, t_vec_info obj){
	t_ray shadow_ray;

	// 交点から光源までのベクトル
	t_vec  i_to_l = sub_vec(world->light->pos_vec, obj.inter_pos);
	shadow_ray.dir = vec_normalize(i_to_l);
	shadow_ray.pos = add_vec(obj.inter_pos,mul_vec(shadow_ray.dir, EPSILON));
	double d_to_light = norm_vec(i_to_l) - EPSILON;


	t_objects	*tmp_o_list;
	t_vec_info closest;
	t_vec_info tmp;

	// 最も近い交点までの距離
	closest.t = INFINITY;
	tmp_o_list = world->objs;
	//全てのオブジェクトに対して計算する
	while (tmp_o_list != NULL)
	{
		// tmp = calc_intersection(world, *tmp_o_list, shadow_ray);
		tmp = get_intersection(world, shadow_ray);
		if (tmp.t > 0 && tmp.t <= d_to_light)
        {
            return true;
        }
		tmp_o_list = tmp_o_list->next;
	}
	return false;
}



bool	draw(t_minirt *world, t_mlx *mlx)
{
	int  x;
	int  y;
	t_vec_info closest_obj;
	int color = 0;
	t_color amb_color;
	t_color dif_color;
	t_color sup_color;
	t_color final_color;
	t_color ref_color;


	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "MiniRT");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &(mlx->bits_per_pixel), &(mlx->line_length), &(mlx->endian));

	// カメラからスクリーンまでの距離
	double d = WIDTH / 2 / tan(world->cam->fov / 2 / 180 * M_PI);

	// カメラからスクリーンの中心へのベクトル
	t_vec dsc = mul_vec(world->cam->ori_vec, d);

	// スクリーンの基底ベクトル
	t_vec esx;
	esx.x = dsc.z / sqrt(dsc.z * dsc.z + dsc.x * dsc.x);
	esx.y = 0;
	esx.z = -dsc.x / sqrt(dsc.z * dsc.z + dsc.x * dsc.x);
	esx = vec_normalize(esx);
	t_vec esy;
	esy = vec_normalize(crossProduct(dsc, esx));

	amb_color = get_ambient(world);
	// printf("amb_color %u, %u, %u\n",amb_color.r, amb_color.g, amb_color.b);
	// printf("%f\n", ((double)255)/255.0 * 0.1 * world->amb->light_intensity);

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			double screen_w = x - (WIDTH - 1) / 2;
			double screen_h = (HEIGHT - 1) / 2 - y;

			t_vec x_vec = mul_vec(esx, screen_w);
			t_vec y_vec = mul_vec(esy, screen_h);
			t_ray ray;
			ray.dir = vec_normalize(add_vec(dsc, add_vec(x_vec, y_vec)));
			ray.pos = world->cam->pos_vec;

			// 視点とぶつかるオブジェクトを計算する
			closest_obj = get_intersection(world, ray);
			//交点があれば
			if (closest_obj.t > 0)
			{
				if (check_shadow(world, closest_obj) == true){
					// final_color = sca_mul_color(closest_obj.color,world->amb->light_intensity);
					// printf("shadow color %u, %u, %u\n",final_color.r,final_color.g,final_color.b);
					final_color = mul_color(closest_obj.color, amb_color);
				}
				else{
					//環境光と鏡面反射のカラーを加える
					dif_color = get_diffuse(world, closest_obj);
					sup_color = get_supecular(world, closest_obj, ray.dir);
					ref_color =  add_color(add_color(amb_color,dif_color),sup_color);
					final_color =  mul_color(closest_obj.color,ref_color);
					// final_color =  add_color(closest_obj.color,add_color(add_color(amb_color,dif_color),sup_color));
					// ref_color =  add_li_color(add_li_color(amb_color,dif_color),sup_color);
					// printf("ref %f,%f,%f\n",ref_color.r, ref_color.g, ref_color.b);
					// final_color = mul_ob_li(closest_obj.color, ref_color);
				}
					// dif_color = get_diffuse(world, closest_obj);
					// sup_color = get_supecular(world, closest_obj, ray.dir);
					// ref_color =  add_color(add_color(amb_color,dif_color),sup_color);
					// printf("ref color %u,%u,%u", ref_color.r, ref_color.g, ref_color.b);
					// final_color =  mul_color(closest_obj.color,ref_color);

				// rgbを0-255の範囲に抑える
				final_color.r = final_color.r/255;
				final_color.g = final_color.g/255;
				final_color.b = final_color.b/255;
				printf("final color %u, %u, %u\n",final_color.r, final_color.g, final_color.b);

				color = argb_to_hex(final_color);

				my_mlx_pixel_put(mlx, x , y, color);
			}
			else
			{
				//背景
				my_mlx_pixel_put(mlx, x, y, BACK_COLOR);
			}
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img, 0, 0);
	mlx_hook(mlx->window, 17, 0, close_win, mlx);
	mlx_loop(mlx->mlx);
	return (true);
}
