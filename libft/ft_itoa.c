/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaei <smaei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:03:23 by smaei             #+#    #+#             */
/*   Updated: 2022/10/31 17:01:41 by smaei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(long n, unsigned int flag)
{
	unsigned int	size;

	size = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		size++;
		n = n / 10;
	}
	if (flag == 1)
		size++;
	return (size);
}

static int	loop(char *result, long n, unsigned int i)
{
	if (n < 10)
		result[i] = n + '0';
	else
	{
		i = loop(result, n / 10, i);
		result[++i] = (n % 10) + '0';
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*result;
	unsigned int	size;
	long			long_n;
	unsigned int	flag;

	long_n = n;
	flag = 0;
	if (long_n < 0)
	{
		long_n = -long_n;
		flag = 1;
	}
	size = count(long_n, flag);
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (result == NULL)
		return (NULL);
	if (flag == 1)
	{
		result[0] = '-';
		loop(result, long_n, 1);
	}
	else
		loop(result, long_n, 0);
	result[size] = '\0';
	return (result);
}
