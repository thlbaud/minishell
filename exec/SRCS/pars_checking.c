/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_checking.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 08:33:29 by avaldin           #+#    #+#             */
/*   Updated: 2024/05/27 13:20:39 by avaldin          ###   ########.fr       */
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
		return (printf("bash: syntax error near unexpected token `%c'\n",
				line[i]), 1);
	while (line[i])
	{
		if (line[i] == '"' || line[i] == 39)
			i += skip_quote(&line[i]) + 1;
		else if (line[i] == '|')
		{
			if (!line[i + skip_space(&line[i])]
				|| line[i + skip_space(&line[i])] == '\n'
				|| line[i + skip_space(&line[i])] == '|')
				return (printf("bash: syntax error near unexpected"
						" token `%c'\n", line[i + skip_space(&line[i])]), 1);
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

int	white_space(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] != ' ' && line[i] != '	')
			return (0);
		i++;
	}
	return (1);
}

int	checking(char *line)
{
	int	i;

	i = -1;
	if (!paire_of_quote(line))
		return (printf("not enough quote\n"), 1);
	if (red_syntax(line))
	{
		if (!line[red_syntax(line)])
			printf("bash: syntax error near unexpected token `newline'\n");
		else
			printf("bash: syntax error near unexpected token `%c'\n",
				line[red_syntax(line)]);
		return (2);
	}
	if (pipe_syntax(line) != -1 || white_space(line))
		return (1);
	while (line[++i])
	{
		if (line[i] == 39)
			i += skip_quote(&line[i]) + 1;
		else if (line[i] == '$' && line[i + 1] == '$')
			return (printf("bash : syntax error, two consecutive $\n"), 4);
	}
	return (0);
}
