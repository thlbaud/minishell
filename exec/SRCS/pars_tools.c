/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:00:55 by avaldin           #+#    #+#             */
/*   Updated: 2024/03/25 10:48:10 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/parsing.h"
#include "../include/libft/libft.h"

int skip_quote(char *line)
{
	int i;

	i = 0;
	if (line[i++] == '"')
		while (line[i] && line[i] != '"')
			i++;
	else
		while (line[i] && line[i] != 39)  // a test
			i++;
	if (!line[i])
	{
		printf("no end quote\n");
		exit(1);                          // erreur a gerer
	}
	return (i - 1);
}

int write_quote(char *line, char *dest)
{
	int i;

	i = 0;
	if (line[i++] == '"')
		while (line[i] && line[i] != '"')
		{
			dest[i - 1] = line[i];
			i++;
		}
	else
		while (line[i] && line[i] != 39)  // a test
		{
			dest[i - 1] = line[i];
			i++;
		}
	return (i - 1);

}

char *str_cut(char *line, int start, int end)
{
	int i;
	char *new_line;

	i = 0;
	if (ft_strlen(line, 0) - end + start == 0)
	{
		free(line);
		return (NULL);
	}
	new_line = ft_calloc(ft_strlen(line, 0) - end + start + 1, sizeof(char));
	if (!new_line)
		exit(3); //pas ok
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