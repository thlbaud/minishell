/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_syntax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:35:51 by avaldin           #+#    #+#             */
/*   Updated: 2024/04/16 17:01:16 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	red_syntax_a(char *line, int i)
{
	if (line[i] == '>')
	{
		if (line[i + 1] == '>' && (!line[i + 1 + skip_space(&line[i + 1])]
				|| line[i + 1 + skip_space(&line[i + 1])] == '<'
				|| line[i + 1 + skip_space(&line[i + 1])] == '|'
				||line[i + 1 + skip_space(&line[i + 1])] == '\n'
				|| line[i + 1 + skip_space(&line[i + 1])] == '>'))
			return (i + 1 + skip_space(&line[i + 1]));
		else if (!line[i + skip_space(&line[i])]
			|| line[i + skip_space(&line[i])] == '<'
			|| line[i + skip_space(&line[i])] == '|'
			|| line[i + skip_space(&line[i])] == '\n')
			return (i + skip_space(&line[i]));
	}
	return (-1);
}

int	red_syntax_b(char *line, int i)
{
	if (line[i] == '<')
	{
		if (line[i + 1] == '<'
			&& (!line[i + 1 + skip_space(&line[i + 1])]
				|| line[i + 1 + skip_space(&line[i + 1])] == '<'
				|| line[i + 1 + skip_space(&line[i + 1])] == '|'
				||line[i + 1 + skip_space(&line[i + 1])] == '\n'
				|| line[i + 1 + skip_space(&line[i + 1])] == '>'))
			return (i + 1 + skip_space(&line[i + 1]));
		else if (!line[i + skip_space(&line[i])]
			|| line[i + skip_space(&line[i])] == '>'
			|| line[i + skip_space(&line[i])] == '|'
			||line[i + skip_space(&line[i])] == '\n')
			return (i + skip_space(&line[i]));
	}
	return (-1);
}

int	red_syntax(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == 39)
			i += skip_quote(&line[i]) + 1;
		else if (red_syntax_a(line, i) != -1)
			return (red_syntax_a(line, i));
		else if (red_syntax_b(line, i) != -1)
			return (red_syntax_b(line, i));
		i++;
	}
	return (0);
}
