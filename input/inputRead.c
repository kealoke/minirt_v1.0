#include "../minirt.h"

//bool構造体を初期化する関数
void	init_flags(t_read_flag *flag)
{
	flag->amb_f = false;
	flag->cam_f = false;
	flag->light_f = false;
	flag->obj_f = false;
}

//ファイルから設定が全て取得できているか確認する関数
bool	file_identifer_check(t_read_flag flag)
{
	if (flag.amb_f == false)
		return (false);
	if (flag.cam_f == false)
		return (false);
	if (flag.light_f == false)
		return (false);
	if (flag.obj_f == false)
		return (false);
	return (true);
}

// ファイルオープンして読み込む関数
// 1: char *file -> 読み込みたいファイル
// 2: t_minirt &world -> 読み込んだ情報を格納する構造体
void	open_and_read(char *file, t_minirt *world)
{
	int			fd;
	char		*file_line;
	bool		ckeck_flag;
	t_read_flag	flag;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		err_and_exit("failed to open file\n");
	while (true)
	{
		file_line = get_next_line(fd);
		if (!file_line)
			break ;
		parse_line(file_line, world, &flag);
	}
	ckeck_flag = file_identifer_check(flag);
	if (!ckeck_flag)
		err_and_exit("your rt file is missing some identifer\n");
}
