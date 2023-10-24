/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaei <smaei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:26:56 by smaei             #+#    #+#             */
/*   Updated: 2022/10/31 17:16:06 by smaei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(const char *haystack,
					const char *needle, size_t h_i, size_t len)
{
	size_t	i;

	i = 0;
	while (needle[i] != '\0')
	{
		if (haystack[i] != needle[i])
			return (0);
		else
			i++;
	}
	if (len < h_i + i)
		return (0);
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t			h_i;
	unsigned int	flag;

	h_i = 0;
	flag = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (h_i < len)
	{
		if (haystack[h_i] == '\0')
			return (NULL);
		if (haystack[h_i] == needle[0])
			flag = ft_check(&haystack[h_i], needle, h_i, len);
		if (flag == 1)
			return ((char *)&haystack[h_i]);
		else
			h_i++;
	}
	return (NULL);
}
