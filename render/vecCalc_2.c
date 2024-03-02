/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecCalc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushimom <yushimom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:33:46 by yushimom          #+#    #+#             */
/*   Updated: 2024/03/02 18:33:49 by yushimom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//ベクトルの足し算　a+b
t_vec	add_vec(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

//ベクトルの引き算　a-b
t_vec	sub_vec(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}
