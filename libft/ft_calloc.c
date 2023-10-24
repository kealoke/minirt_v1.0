/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaei <smaei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:03:38 by smaei             #+#    #+#             */
/*   Updated: 2022/10/19 17:15:19 by smaei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*m;

	if ((count == 0) || (size == 0))
	{
		m = (void *)malloc(1);
		ft_bzero(m, 1);
		return (m);
	}
	if (count > SIZE_MAX / size)
		return (NULL);
	m = (void *)malloc(count * size);
	if (m == NULL)
		return (NULL);
	ft_bzero(m, count * size);
	return (m);
}
