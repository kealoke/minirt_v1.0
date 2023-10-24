/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaei <smaei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:27:52 by smaei             #+#    #+#             */
/*   Updated: 2022/10/20 17:27:15 by smaei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	i;
	size_t	start;
	size_t	end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	end = ft_strlen(s1);
	start = 0;
	while (ft_strchr(set, s1[i++]))
		start++;
	while (ft_strchr(set, s1[end]))
		end--;
	end++;
	if (start == end)
		trim = ft_substr(s1, start, ft_strlen(s1));
	else
		trim = ft_substr(s1, start, end - start);
	return (trim);
}
