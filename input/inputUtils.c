/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputUtils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushimom <yushimom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:32:21 by yushimom          #+#    #+#             */
/*   Updated: 2024/03/02 18:32:22 by yushimom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// 文字列の先頭か数字までをintの数値にして返す
//  char *str=255,0,0 -> return (int)255
// 1:char **str -> 変換したい数字を先頭に含む文字列
unsigned int	string_to_int(char **str)
{
	int	ans;

	ans = 0;
	if (!*str)
		return (ans);
	while (ft_isdigit(**str))
	{
		if (ans > (DBL_MAX / 10))
			err_and_exit("float overflow\n");
		ans = ans * 10 + **str - '0';
		(*str)++;
	}
	return (ans);
}

// ft_atod用の関数 符号を返す
static int	get_sign(char **str)
{
	int	sign;

	sign = 1;
	while ((**str) && !ft_isalnum(**str))
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

// char文字列からdouble型に変換する関数
double	ft_atod(char *str)
{
	double	ans;
	double	fraction;
	int		sign;

	if (!str)
		return (0);
	sign = get_sign(&str);
	ans = 0;
	ans = string_to_int(&str);
	fraction = 0.1;
	if (*str == '.')
	{
		++str;
		while (ft_isdigit(*str))
		{
			if (ans > DBL_MAX - (*str - '0') * fraction)
				err_and_exit("float overflow\n");
			ans += (*str - '0') * fraction;
			fraction *= 0.1;
			++str;
		}
	}
	return (sign * ans);
}

//二つの文字列が要素と長さが完全に一致しているか確かめる関数
bool	is_match(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (false);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (false);
	if (ft_strncmp(s1, s2, ft_strlen(s2) + 1))
		return (false);
	return (true);
}

void	*my_malloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		err_and_exit("malloc err\n");
	return (res);
}
