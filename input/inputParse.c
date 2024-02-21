#include "../minirt.h"

// lineをsplitして構造体に入力する関数
// 1: char *line -> ファイルから読み込んだライン
// 2: t_minirt *world -> 値を入力する構造体
void	parse_line(char *line, t_minirt *world, t_read_flag *flag)
{
	char	**token;

	token = ft_split(line, ' ');
	if (!token)
		return ;
	if (is_match(token[0], "A"))
		set_ambient(token, world, flag);
	else if (is_match(token[0], "C"))
		set_camera(token, world, flag);
	else if (is_match(token[0], "L"))
		set_light(token, world, flag);
	else if (is_match(token[0], "sp"))
		set_sphere(token, world, flag);
	else if (is_match(token[0], "pl"))
		set_plane(token, world, flag);
	else if (is_match(token[0], "cy"))
		set_cylinder(token, world, flag);
}
