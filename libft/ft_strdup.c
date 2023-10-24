/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaei <smaei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:26:42 by smaei             #+#    #+#             */
/*   Updated: 2022/10/31 17:05:47 by smaei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char			*tmp;
	size_t			s_size;
	unsigned int	i;

	s_size = ft_strlen(s1);
	i = 0;
	tmp = (char *)malloc(sizeof(char) * (s_size + 1));
	if (tmp != NULL)
	{
		while (s1[i] != '\0')
		{
			tmp[i] = (char)s1[i];
			i++;
		}
		tmp[i] = '\0';
		return (tmp);
	}
	return (NULL);
}
