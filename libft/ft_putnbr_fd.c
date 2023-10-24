/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaei <smaei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:32:05 by smaei             #+#    #+#             */
/*   Updated: 2022/10/19 16:16:09 by smaei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	num;
	long	n_long;

	n_long = n;
	if (n_long < 0)
	{
		write(fd, "-", 1);
		n_long = -(long)n;
		num = n_long % 10 + '0';
	}
	else
		num = n_long % 10 + '0';
	if (n_long < 10)
		ft_putchar_fd(num, fd);
	else
	{
		ft_putnbr_fd(n_long / 10, fd);
		ft_putchar_fd(num, fd);
	}		
}
