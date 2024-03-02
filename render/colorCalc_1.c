/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorCalc_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushimom <yushimom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:32:30 by yushimom          #+#    #+#             */
/*   Updated: 2024/03/02 18:32:32 by yushimom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//カラー構造体のb倍 a*b
t_color	sca_mul_color(t_color a, double b)
{
	t_color	res;

	res.r = a.r * b;
	res.g = a.g * b;
	res.b = a.b * b;
	return (res);
}

//カラー構造体の割り算 a/b
t_color	div_color(t_color a, double b)
{
	t_color	res;

	res.r = a.r / b;
	res.g = a.g / b;
	res.b = a.b / b;
	return (res);
}

//カラー構造体同士の掛け算 a*b
t_color	mul_color(t_color a, t_color b)
{
	t_color	res;

	res.r = a.r * b.r;
	res.g = a.g * b.g;
	res.b = a.b * b.b;
	return (res);
}

//カラー構造体同士の足し算 a+b
t_color	add_color(t_color a, t_color b)
{
	t_color	res;

	res.r = a.r + b.r;
	res.g = a.g + b.g;
	res.b = a.b + b.b;
	return (res);
}
