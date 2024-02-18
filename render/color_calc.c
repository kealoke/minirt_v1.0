#include "../minirt.h"

//カラー構造体のb倍
t_color sca_mul_color(t_color a, double b){
	t_color res;

	res.r = a.r * b;
	res.g = a.g * b;
	res.b = a.b * b;
	return res;
}

//ライトカラー構造体のb倍
t_light_color mul_li_color(t_light_color a, double b){
	t_light_color res;

	res.r = a.r * b;
	res.g = a.g * b;
	res.b = a.b * b;
	return res;
}

//オブジェクトとライトの掛け算(t_colorで返す)
t_color mul_ob_li(t_color obj, t_light_color light){
	t_color res;

	res.r = (unsigned int)light.r * obj.r;
	res.g = (unsigned int)light.g * obj.g;
	res.b = (unsigned int)light.b * obj.b;
	return res;
}

// ライトとオブジェクトの掛け算(t_lightcolorで返す)
t_light_color mul_li_ob(t_light_color light, t_color obj){
	t_light_color res;

	res.r = light.r * (double)obj.r;
	res.g = light.g * (double)obj.g;
	res.b = light.b * (double)obj.b;
	return res;
}


//ライトカラー構造体同士の足し算
t_light_color add_li_color(t_light_color a, t_light_color b){
	t_light_color res;

	res.r = a.r + b.r;
	res.g = a.g + b.g;
	res.b = a.b + b.b;
	return res;
}

//カラー構造体同士の掛け算
t_color mul_color(t_color a, t_color b){
	t_color res;

	res.r = a.r * b.r;
	res.g = a.g * b.g;
	res.b = a.b * b.b;
	return res;
}

//カラー構造体同士の足し算
t_color add_color(t_color a, t_color b){
	t_color res;

	res.r = a.r + b.r;
	res.g = a.g + b.g;
	res.b = a.b + b.b;
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

//rgbの各数字を受け取りt_color型で返す
t_color get_color_vec(unsigned int red, unsigned int green, unsigned int blue){
	t_color res;

	res.r = red;
	res.g = green;
	res.b = blue;
	return res;
}