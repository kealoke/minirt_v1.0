#include "../minirt.h"

//color構図体からintに変換する
int	argb_to_hex(t_color color)
{
	int				res_color;
	unsigned int	a;

	a = 0;
	res_color = ((a & 0xFF) << 24) | ((color.r & 0xFF) << 16) | ((color.g & 0xFF) << 8) | (color.b & 0xFF);
	return (res_color);
}

//rgbの各数字を受け取りt_color型で返す
t_color	get_color_vec(unsigned int red, unsigned int green, unsigned int blue)
{
	t_color res;

	res.r = red;
	res.g = green;
	res.b = blue;
	return (res);
}