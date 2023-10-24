/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushimom <yushimom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:13:19 by smaei             #+#    #+#             */
/*   Updated: 2023/05/07 18:14:12 by yushimom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_size;
	size_t	s2_size;
	char	*join;
	size_t	i;

	i = 0;
	if (s1 == NULL)
		return ((char *)s2);
	if (s2 == NULL)
		return ((char *)s1);
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (s1_size + s2_size + 1));
	if (join == NULL)
		return (NULL);
	join = (char *)ft_memcpy(join, s1, s1_size);
	while (i < s2_size)
	{
		join[s1_size + i] = s2[i];
		i++;
	}
	join[s1_size + i] = '\0';
	return (join);
}
