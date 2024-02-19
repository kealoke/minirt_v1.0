#include "../minirt.h"

// 数値を範囲内に収める(min-max)
// 1: double value -> 修正したい値
// 2: double min -> 範囲の最小値
// 3: double max -> 範囲の最大値
double clamp(double value, double min, double max) {
    if (value < min)
		return min;
    if (value > max)
		return max;
    return value;
}

//オブジェクトにより交点の計算方法を変更する
// 1: t_minirt *world -> 全体の情報を持つ構造体
// 2: t_objects tmp_o_list -> オブジェクトリストのノード
// 3: t_ray ray -> 交差判定をするレイ
t_vec_info calc_intersection(t_minirt *world,t_objects node, t_ray ray){

	t_vec_info non;

	non.t = -1;

	if (node.obj_type == t_pl)
			return (pl_intersection(world, node, ray));
	else if (node.obj_type == t_sp)
			return (sp_intersection(world, node, ray));
	else if (node.obj_type == t_cy)
		return (cy_intersecton(world, node, ray));
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


//環境光の放射輝度を取得
double get_ambient(t_minirt *world){

	double ambient_ref;
	double ambient_k = 1;

	ambient_ref = ambient_k * world->amb->light_intensity;
	return ambient_ref;
}

//拡散反射の放射輝度を取得
double get_diffuse(t_minirt *world, t_vec_info closest_obj){
	double diffuse_ref;
	double diffuse_k = 1;

	double nl = InnerProduct(closest_obj.light_dir, closest_obj.normal);
	if(nl < 0)
		nl = 0;

	diffuse_ref = diffuse_k * nl * world->light->brightness;

	return diffuse_ref;
}

//鏡面反射の放射輝度を取得
double get_supecular(t_minirt *world, t_vec_info closest_obj, t_vec dir_vec){


	double supecular_ref;
	double supecular_k = 1;

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
	return supecular_ref;
	// return res;
}

//物体にシャドウがかかるかチェックする
// 1: t_minirt *world -> ワールド情報
// 2: t_vec_info obj -> レイと交差するオブジェクト
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
		// tmp = get_intersection(world, shadow_ray);
		tmp = calc_intersection(world, *tmp_o_list, shadow_ray);
		if (tmp.t >= 0 && tmp.t <= d_to_light)
        {
            return true;
        }
		tmp_o_list = tmp_o_list->next;
	}
	return false;
}

//カラーの値を調整して0-255に収める
// 1: t_color color -> 調整したいカラー
t_color adjust_color(t_color color){
	t_color res;

	//ライトのカラーもかけているので255で割って調整する
	res.r = color.r/255;
	res.g = color.g/255;
	res.b = color.b/255;

	// rgbを0-255の範囲に抑える
	res.r = clamp(res.r, 0, 255);
	res.g = clamp(res.g, 0, 255);
	res.b = clamp(res.b, 0, 255);

	return res;
}

//交点の色を求める(影,環境光、拡散反射、鏡面反射)
int get_color(t_minirt *world, t_vec_info closest_obj, t_ray ray, double ra){
	double rr, rd, rs;
	int color;
	t_color rgb_color;
	t_color tmp_light;
	tmp_light.r =255;
	tmp_light.g =255;
	tmp_light.b =255;

	if (check_shadow(world, closest_obj) == true){
		//影がかかる場合は環境光のみ反映させる
		rr = ra;
	}
	else{
		//環境光と鏡面反射を加える
		if(closest_obj.color.g == 255)
			// printf("cycycy\n");
		rd =  get_diffuse(world, closest_obj);
		rs = get_supecular(world, closest_obj, ray.dir);
		rr = ra + rd + rs;
	}
	rgb_color = mul_color(sca_mul_color(closest_obj.color,rr),tmp_light);

	rgb_color = adjust_color(rgb_color);
	color = argb_to_hex(rgb_color);
	return color;

}

// 描写する関数
bool	draw(t_minirt *world, t_mlx *mlx)
{
	int  x;
	int  y;
	t_vec_info closest_obj;
	int color = 0;
	double ra;



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

	//環境光
	ra = get_ambient(world);

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
				color = get_color(world, closest_obj, ray, ra);
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
