/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:00:55 by avaldin           #+#    #+#             */
/*   Updated: 2024/04/19 16:42:55 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/parsing.h"
#include "../include/libft/libft.h"

int	skip_quote(char *line)
{
	int	i;

	i = 0;
	if (line[i++] == '"')
		while (line[i] && line[i] != '"')
			i++;
	else
		while (line[i] && line[i] != 39)
			i++;
	return (i - 1);
}

int	write_quote(char *line, char *dest)
{
	int	i;

	i = 0;
	if (line[i++] == '"')
	{
		while (line[i] && line[i] != '"')
		{
			dest[i - 1] = line[i];
			i++;
		}
	}
	else
	{
		while (line[i] && line[i] != 39)
		{
			dest[i - 1] = line[i];
			i++;
		}
	}
	return (i - 1);
}

char	*str_cut(char *line, int start, int end)
{
	int		i;
	char	*new_line;

	i = 0;
	if (ft_strlen(line, 0) - end + start == 0)
		return (free(line), NULL);
	new_line = ft_calloc(ft_strlen(line, 0) - end + start + 1, sizeof(char));
	if (!new_line)
		exit(1);
	while (i < start)
	{
		new_line[i] = line[i];
		i++;
	}
	i = 0;
	while (line[end + i] && line[end + i + 1])
	{
		new_line[start + i] = line[end + i + 1];
		i++;
	}
	new_line[start + i] = '\0';
	free(line);
	return (new_line);
}

char	*_strdup(const char *s, int start, int len)
{
	int		i;
	char	*str;

	if (!s || len == 0)
		return (NULL);
	if (len == -1)
		str = ft_calloc((ft_strlen((char *)s, 0) - start + 1), sizeof(char));
	else
		str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (s[++i + start] && len--)
		str[i] = s[i + start];
	str[i] = '\0';
	return (str);
}

char	*str_modify(char *str, int i, int len, char *add)
{
	char	*new_str;
	int		j;
	int		k;

	if (!str)
		return (add);
	if (!add || !add[0])
		return (str);
	new_str = ft_calloc(ft_strlen(str, 0) - len + ft_strlen(add, 0) + 1,
			sizeof(char));
	if (!new_str)
		exit (1);
	j = -1;
	k = -1;
	while (++j < i)
		new_str[j] = str[j];
	while (add[++k])
		new_str[j + k] = add[k];
	j--;
	while (str[len + ++j])
		new_str[j + k] = str[j + len];
	new_str[j + k] = '\0';
	free(str);
	free(add);
	return (new_str);
}
