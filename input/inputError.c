/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputError.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaei <smaei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:01:46 by smaei             #+#    #+#             */
/*   Updated: 2024/03/17 15:01:47 by smaei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	input_error(char *msg)
{
	printf("%s", msg);
	return (false);
}

void	err_and_exit(char *msg)
{
	printf("Error: %s", msg);
	exit(EXIT_FAILURE);
}
