/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaei <smaei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:20:01 by smaei             #+#    #+#             */
/*   Updated: 2022/10/19 17:26:55 by smaei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	size;
	size_t	i;

	if (s == NULL)
		return ;
	size = ft_strlen(s);
	i = 0;
	while (i < size)
	{
		write(fd, &s[i], 1);
		i++;
	}
}
