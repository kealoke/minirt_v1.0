/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaei <smaei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:33:54 by yushimom          #+#    #+#             */
/*   Updated: 2024/03/17 15:15:22 by smaei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_world(t_minirt *world)
{
	world->amb = NULL;
	world->cam = NULL;
	world->light = NULL;
	world->objs = NULL;
}

int	main(int argc, char **argv)
{
	bool		flag;
	t_minirt	world;
	t_mlx		mlx;

	flag = input_check(argc, argv);
	if (flag == false)
		return (EXIT_FAILURE);
	init_world(&world);
	open_and_read(argv[1], &world);
	set_mlx(&(world.mlx));
	render(&world);
	return (EXIT_SUCCESS);
}

// __attribute__((destructor))
// static void destructor() {
// 	system("leaks -q minirt");
// }
