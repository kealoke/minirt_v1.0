/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaei <smaei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:10:02 by smaei             #+#    #+#             */
/*   Updated: 2022/10/31 17:16:30 by smaei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (c == '\0')
		return ((char *)&s[s_len]);
	while (i <= s_len)
	{
		if (s[s_len - i] == (char)c)
			return ((char *)&s[s_len - i]);
		i++;
	}
	return (NULL);
}
