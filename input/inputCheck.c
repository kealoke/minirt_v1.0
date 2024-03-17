/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputCheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaei <smaei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:31:52 by yushimom          #+#    #+#             */
/*   Updated: 2024/03/17 15:05:45 by smaei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// 入力チェックする関数
// 1: int argc -> mainのargc
// 2: char **argv -> mainのargv
bool	input_check(int argc, char **argv)
{
	char	**file_path;
	int		size;
	int		filename_size;

	if (argc < 2 || 3 < argc)
		return (input_error(USAGE));
	file_path = ft_split(argv[1], '/');
	size = 0;
	while (file_path[size] != '\0')
		size++;
	filename_size = ft_strlen(file_path[size - 1]);
	if (!ft_strnstr(file_path[size - 1], ".rt", ft_strlen(file_path[size - 1]))) {
		free_double_array(file_path);
		return (input_error("Error: input argument is not correct\n"));
	}
	if (ft_strlen(file_path[size - 1]) == 3
		|| !is_match(&file_path[size - 1][filename_size - 3], ".rt")) {
		free_double_array(file_path);	
		return (input_error("Error: input argument is not correct\n"));
	}
	free_double_array(file_path);
	return (true);
}

// Vecの範囲を確認する関数
//  x,y,zが[-1, 1]の範囲ならtrue 一つでも外れてたらfalse
// 1: t_vec vec -> 確認したいベクトル
bool	check_vec_range(t_vec vec)
{
	if (vec.x < -1.0 || 1.0 < vec.x)
		return (false);
	if (vec.y < -1.0 || 1.0 < vec.y)
		return (false);
	if (vec.z < -1.0 || 1.0 < vec.z)
		return (false);
	if (norm_vec(vec) > 1)
		return (false);
	return (true);
}

void	adjust_cam_vec(t_vec *vec)
{
	if (vec->x == 0 && vec->z == 0)
	{
		if (vec->y == 1 || vec->y == -1)
			vec->x = 0.0001;
	}
}
