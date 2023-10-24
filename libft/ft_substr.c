/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaei <smaei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:51:43 by smaei             #+#    #+#             */
/*   Updated: 2022/10/20 17:23:39 by smaei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tmp;
	size_t	s_size;
	size_t	i;

	if (s == NULL)
		return (NULL);
	s_size = ft_strlen(s);
	if (s_size < len)
		tmp = malloc(sizeof(char) * (s_size + 1));
	else
		tmp = malloc(sizeof(char) * (len + 1));
	i = 0;
	if (tmp == NULL)
		return (NULL);
	if ((start < s_size) && (len != 0))
	{
		while ((s[start + i] != '\0') && (len > i))
		{
			tmp[i] = s[start + i];
			i++;
		}
	}
	tmp[i] = '\0';
	return (tmp);
}
