/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaei <smaei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:14:20 by smaei             #+#    #+#             */
/*   Updated: 2022/10/31 17:40:59 by smaei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(char const *s, char c)
{
	unsigned int	c_count;
	unsigned int	i;

	c_count = 0;
	i = 0;
	if (c == '\0' && s[0] != '\0')
		return (1);
	if (s[i] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if ((s[i] != c) && ((s[i + 1] == c) || s[i + 1] == '\0'))
			c_count++;
		i++;
	}
	return (c_count);
}

static int	ft_split_main(char **result, char const *s, char c)
{
	unsigned int	start;
	unsigned int	end;
	unsigned int	i;

	start = 0;
	end = 0;
	i = 0;
	while (s[end] != '\0' && s[start] != '\0')
	{
		if (s[start] && s[start] != c)
		{
			while ((s[end] != c) && (s[end] != '\0'))
				end++;
			result[i++] = ft_substr(s, start, end - start);
			if (result[i - 1] == NULL)
				return (0);
			start = end;
		}
		else
			start++;
		end = start;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	size;
	char			**result;
	unsigned int	flag;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	size = count(s, c);
	result = (char **)malloc(sizeof(char *) * (size + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	flag = ft_split_main(result, s, c);
	if (flag == 0)
	{
		while (result[i] != NULL)
			free(result[i]);
		free(result);
		return (NULL);
	}
	result[size] = NULL;
	return (result);
}
