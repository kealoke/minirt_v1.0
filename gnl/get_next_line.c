/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimoshimo <shimoshimo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:58:01 by smaei             #+#    #+#             */
/*   Updated: 2023/10/30 12:00:52 by shimoshimo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_free(char **buf)
{
	free(*buf);
	*buf = NULL;
	return (NULL);
}

static char	*gnl_line(char **buf, char **save)
{
	int		i;
	char	*save_buf;

	if (gnl_strchr(*save, '\n') == -1)
		save_buf = gnl_strjoin(*save, *buf);
	else
		save_buf = gnl_strdup(*save);
	if (!save_buf)
	{
		gnl_free(buf);
		gnl_free(save);
		return (NULL);
	}
	i = gnl_strchr(save_buf, '\n');
	gnl_free(buf);
	*buf = gnl_substr(save_buf, 0, i + 1);
	gnl_free(save);
	if (!*buf)
		return (gnl_free(&save_buf));
	*save = gnl_substr(save_buf, i + 1, gnl_strlen(save_buf) - i);
	gnl_free(&save_buf);
	if (!*save)
		return (gnl_free(buf));
	return (*buf);
}

static int	loop(char **save, char **buf)
{
	char	*tmp;

	tmp = *save;
	*save = gnl_strjoin(tmp, *buf);
	gnl_free(&tmp);
	gnl_free(buf);
	if (*save)
		return (-2);
	else
		return (0);
}

static char	*gnl_flag(char **buf, char **save, int flag)
{
	char	*save_buf;

	if (flag == -1)
	{
		gnl_free(buf);
		return (gnl_free(save));
	}
	if (!save)
		return (gnl_free(buf));
	if (gnl_strlen(*save) == 0)
	{
		gnl_free(buf);
		gnl_free(save);
		return (NULL);
	}
	save_buf = gnl_strdup(*save);
	gnl_free(save);
	gnl_free(buf);
	return (save_buf);
}

char	*get_next_line(int fd)
{
	char		*buf;
	int			flag;
	static char	*save;

	if (fd < 0)
		return (NULL);
	flag = -2;
	buf = NULL;
	while (flag == -2)
	{
		if (gnl_strchr(save, '\n') == -1)
		{
			buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
			if (!buf)
				return (gnl_free(&save));
			flag = read(fd, buf, BUFFER_SIZE);
			if (flag == -1 || flag == 0)
				return (gnl_flag(&buf, &save, flag));
			buf[flag] = '\0';
		}
		if (gnl_strchr(buf, '\n') != -1 || gnl_strchr(save, '\n') != -1)
			return (gnl_line(&buf, &save));
		flag = loop(&save, &buf);
	}
	return (NULL);
}
