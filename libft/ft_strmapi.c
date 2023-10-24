/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaei <smaei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:36:36 by smaei             #+#    #+#             */
/*   Updated: 2022/10/31 17:13:53 by smaei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	s_size;
	char	*result;
	size_t	i;

	if (s == NULL || f == NULL)
		return (NULL);
	s_size = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * (s_size + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[s_size] = '\0';
	return (result);
}
