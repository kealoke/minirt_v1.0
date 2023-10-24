/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaei <smaei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:17:17 by smaei             #+#    #+#             */
/*   Updated: 2022/10/23 16:34:53 by smaei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*char_dst;
	const unsigned char	*char_src;

	char_dst = (unsigned char *)dst;
	char_src = (const unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (src < dst)
	{
		char_dst += (n - 1);
		char_src += (n - 1);
		while (n--)
			*char_dst-- = *char_src--;
	}
	else
	{
		while (n--)
			*char_dst++ = *char_src++;
	}
	return (dst);
}
