/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushimom <yushimom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:37:29 by smaei             #+#    #+#             */
/*   Updated: 2024/03/07 17:22:18 by yushimom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(long result, const char str, unsigned int flag)
{
	long	check;

	check = LONG_MAX / 10;
	if (result < check)
		return (0);
	if (result == check)
	{
		if (flag == 1 && str > '8')
			return (-1);
		else if (flag == 0 && str > '7')
			return (1);
		else
			return (0);
	}
	if (flag == 1)
		return (-1);
	return (1);
}

static long	ft_change(const char *str, unsigned int flag)
{
	long			result;
	unsigned int	i;
	int				long_flag;

	i = 0;
	result = 0;
	while (('0' <= str[i]) && (str[i] <= '9'))
	{
		result *= 10;
		result += str[i] - '0';
		i++;
		if (('0' <= str[i]) && (str[i] <= '9'))
			long_flag = ft_check(result, str[i], flag);
		if (long_flag == 1)
			return (LONG_MAX);
		if (long_flag == -1)
			return (LONG_MIN);
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	unsigned int	i;
	unsigned int	flag;
	long			result;

	i = 0;
	flag = 0;
	result = 0;
	while (((8 < str[i]) && (str[i] < 14)) || str[i] == ' ')
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			flag = 1;
		i++;
	}
	if (('0' <= str[i]) && (str[i] <= '9'))
		result = ft_change(&str[i], flag);
	if (flag == 1 && result != LONG_MIN)
		result = -(result);
	return (result);
}
