/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaei <smaei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:37:09 by smaei             #+#    #+#             */
/*   Updated: 2022/10/31 17:12:49 by smaei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_strlen;

	i = 0;
	if (dst == NULL && dstsize == 0)
		return (ft_strlen(src));
	dst_strlen = ft_strlen(dst);
	if (dst_strlen > dstsize)
		return (dstsize + ft_strlen(src));
	while (src[i] != '\0' && (dst_strlen + i + 1 < dstsize))
	{
		dst[dst_strlen + i] = src[i];
		i++;
	}
	dst[dst_strlen + i] = '\0';
	return (dst_strlen + ft_strlen(src));
}
