/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 08:33:29 by avaldin           #+#    #+#             */
/*   Updated: 2024/04/16 16:38:01 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	skip_space(char *line)
{
	int	i;

	i = 1;
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

int	paire_of_quote(char *line)
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

int	pipe_syntax(char *line)
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

int	checking(char *line)
{
	int	i;

	i = -1;
	if (!paire_of_quote(line))
	{
		printf("not enough quote\n");
		return (1);
	}
	if (red_syntax(line))
	{
		printf("bash: syntax error near unexpected token '%c'\n",
			line[red_syntax(line)]);
		return (2);
	}
	if (pipe_syntax(line) != -1)
	{
		printf("bash: syntax error near unexpected token '%c'\n",
			line[pipe_syntax(line)]);
		return (3);
	}
	while (line[++i])
		if (line[i] == '$' && line[i + 1] == '$')
			return (4);
	return (0);
}
