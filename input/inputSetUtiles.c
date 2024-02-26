#include "../minirt.h"

//ファイル内ベクトルの文字情報を数値に変換して返す関数
double	get_number(char *str, int *i, int *j)
{
	char	*tmp;
	double	res;

	tmp = ft_substr(str, *i, *j - *i);
	*i = *j + 1;
	*j = *i;
	res = ft_atod(tmp);
	free(tmp);
	return (res);
}

// 文字列をvec構造体に変換する関数
// 1: char *str -> 変換したい文字列[x,y,z]
// 2: t_vec *vec -> 変換後の値を入れる構造体
void	set_vec(char *str, t_vec *vec)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return ;
	while (str[j] && str[j] != ',')
		j++;
	vec->x = get_number(str, &i, &j);
	while (str[j] && str[j] != ',')
		j++;
	vec->y = get_number(str, &i, &j);
	while (str[j])
		j++;
	vec->z = get_number(str, &i, &j);
}

// 文字列をRGB構造体に変換する関数
// return : 値が[0,255]の範囲ならtrue それ以外はfalseを返す
// 1: char *str -> 変換したい文字列 [0,255,255]など
// 2: t_color *color -> 変換後の値を格納するt_color構造体
bool	set_rgb_color(char *str, t_color *color)
{
	char	*tmp;

	tmp = str;
	color->r = string_to_int(&str);
	if (255 < color->r || (*tmp != '0' && color->r == 0))
		return (false);
	str++;
	tmp = str;
	color->g = string_to_int(&str);
	if (255 < color->g || (*tmp != '0' && color->g == 0))
		return (false);
	str++;
	tmp = str;
	color->b = string_to_int(&str);
	if (255 < color->b || (*tmp != '0' && color->b == 0))
		return (false);
	return (true);
}
