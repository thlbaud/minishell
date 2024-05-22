/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_checking.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 08:33:29 by avaldin           #+#    #+#             */
/*   Updated: 2024/05/22 11:11:54 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../HDRS/parsing.h"

static int	paire_of_quote(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == 39)
		{
			i += skip_quote(&line[i]) + 1;
			if (!line[i])
				return (0);
		}
		i++;
	}
	return (1);
}

static int	pipe_syntax(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '|')
		return (i);
	while (line[i])
	{
		if (line[i] == '"' || line[i] == 39)
			i += skip_quote(&line[i]) + 1;
		else if (line[i] == '|')
		{
			if (!line[i + skip_space(&line[i])]
				|| line[i + skip_space(&line[i])] == '\n'
				|| line[i + skip_space(&line[i])] == '|')
				return (i + skip_space(&line[i]));
		}
		i++;
	}
	return (-1);
}

int	skip_space(char *line)
{
	int	i;

	i = 1;
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

int	checking(char *line)
{
	int	i;

	i = -1;
	if (!paire_of_quote(line))
		return (printf("not enough quote\n"), 1);
	if (red_syntax(line) || pipe_syntax(line) != -1)
	{
		if (!line[red_syntax(line)])
			printf("bash: syntax error near unexpected token `newline'\n");
		else
			printf("bash: syntax error near unexpected token `%c'\n",
				line[red_syntax(line)]);
		return (2);
	}
	while (line[++i])
		if (line[i] == '$' && line[i + 1] == '$')
			return (printf("two consecutive $\n"), 4);
	return (0);
}
