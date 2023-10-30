/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimoshimo <shimoshimo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:58:05 by smaei             #+#    #+#             */
/*   Updated: 2023/10/30 12:02:33 by shimoshimo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strdup(const char *s1)
{
	char			*tmp;
	size_t			s_size;
	unsigned int	i;

	if (s1 == NULL)
		return (NULL);
	s_size = gnl_strlen(s1);
	i = 0;
	tmp = (char *)malloc(sizeof(char) * (s_size + 1));
	if (tmp != NULL)
	{
		while (s1[i] != '\0')
		{
			tmp[i] = (char)s1[i];
			i++;
		}
		tmp[i] = '\0';
		return (tmp);
	}
	return (NULL);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL)
		return (gnl_strdup(s2));
	s1_len = gnl_strlen(s1);
	s2_len = gnl_strlen(s2);
	str = malloc(sizeof(char) * (s1_len + s2_len) + 1);
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
		str[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*tmp;
	size_t	s_size;
	size_t	i;

	if (s == NULL)
		return (NULL);
	s_size = gnl_strlen(s);
	if (s_size < len)
		tmp = malloc(sizeof(char) * (s_size + 1));
	else
		tmp = malloc(sizeof(char) * (len + 1));
	i = 0;
	if (tmp == NULL)
		return (NULL);
	if ((start < s_size) && (len != 0))
	{
		while ((s[start + i] != '\0') && (len > i))
		{
			tmp[i] = s[start + i];
			i++;
		}
	}
	tmp[i] = '\0';
	return (tmp);
}

int	gnl_strchr(char *str, char chr)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == chr)
			return (i);
		i++;
	}
	return (-1);
}
