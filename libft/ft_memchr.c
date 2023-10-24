/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaei <smaei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:28:59 by smaei             #+#    #+#             */
/*   Updated: 2022/10/26 15:41:31 by smaei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*char_s;

	char_s = (const unsigned char *)s;
	while (n--)
		if (*char_s++ == (unsigned char)c)
			return ((void *)--char_s);
	return (NULL);
}
