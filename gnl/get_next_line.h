/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaei <smaei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:57:48 by smaei             #+#    #+#             */
/*   Updated: 2023/05/20 14:33:33 by smaei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*gnl_strdup(const char *s1);
size_t	gnl_strlen(const char *str);
char	*gnl_strjoin(char *s1, char *s2);
int		gnl_strchr(char *str, char chr);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*get_next_line(int fd);

#endif
