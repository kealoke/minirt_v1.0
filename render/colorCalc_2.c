#include "../minirt.h"

//color構図体からintに変換する
// 1: t_color color -> int に変換したい値
int	argb_to_hex(t_color color)
{
	int				res_color;
	unsigned int	a;

	a = 0;
	res_color = ((a & 0xFF) << 24)
		| ((color.r & 0xFF) << 16)
		| ((color.g & 0xFF) << 8)
		| (color.b & 0xFF);
	return (res_color);
}

// 数値を範囲内に収める(min-max)
// 1: double value -> 修正したい値
// 2: double min -> 範囲の最小値
// 3: double max -> 範囲の最大値
double	clamp(double value, double min, double max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

//カラーの値を調整して0-255に収める
// 1: t_color color -> 調整したいカラー
t_color	adjust_color(t_color color)
{
	t_color	res;

	//ライトのカラーもかけているので255で割って調整する
	res.r = color.r / 255;
	res.g = color.g / 255;
	res.b = color.b / 255;
	// rgbを0-255の範囲に抑える
	res.r = clamp(res.r, 0, 255);
	res.g = clamp(res.g, 0, 255);
	res.b = clamp(res.b, 0, 255);
	return (res);
}

//交点の色を求める(影,環境光、拡散反射、鏡面反射)
// 1: t_minirt *world -> ワールド情報
// 2: t_vec_info closest_obj -> 交差する物体のベクトル情報
// 3: t_ray ray -> レイのベクトル情報
// 4: double ra -> 環境光の輝度(normの関係＆定数なので引数として渡している)
int	get_color(t_minirt *world, t_vec_info closest_obj, t_ray ray, double ra)
{
	int		color;
	t_color	rgb_color;
	t_color	ref_color;
	double	rd;
	double	rs;

	ref_color = sca_mul_color(world->amb->color, ra);
	//影がかからない場合、拡散反射と鏡面反射を反映させる
	if (check_shadow(world, closest_obj) == false)
	{
		//環境光と鏡面反射の輝度を取得する
		rd = get_diffuse(world, closest_obj);
		rs = get_supecular(world, closest_obj, ray.dir);
		ref_color = add_color(ref_color, sca_mul_color(world->light->color,
					rd));
		ref_color = add_color(ref_color, sca_mul_color(world->light->color,
					rs));
	}
	rgb_color = mul_color(closest_obj.color, ref_color);
	rgb_color = adjust_color(rgb_color);
	color = argb_to_hex(rgb_color);
	return (color);
}
