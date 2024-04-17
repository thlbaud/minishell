/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_expender.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:38:27 by avaldin           #+#    #+#             */
/*   Updated: 2024/04/16 16:58:10 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	quote_count(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == '"' || line[i] == 39)
		{
			i += skip_quote(&line[i]) + 1;
			count++;
		}
		i++;
	}
	return (count);
}

int	temp_filling(t_red *red)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (red->file[0][++i])
	{
		if (red->file[0][i] == '"' || red->file[0][i] == 39)
		{
			if (i != j)
				red->temp[red->tmp_len++] = ft_strdup(red->file[0], j, i - j);
			red->temp[red->tmp_len] = ft_calloc(skip_quote(
						&red->file[0][i]) + 1, sizeof(char));
			if (!red->temp[red->tmp_len])
				return (0);
			red->protection[red->tmp_len++] = 2;
			if (red->file[0][i] == '"')
				red->protection[red->tmp_len - 1] = 1;
			i += write_quote(&red->file[0][i], red->temp[red->tmp_len - 1]) + 1;
			j = i + 1;
		}
	}
	if (i != j)
		red->temp[red->tmp_len++] = ft_strdup(red->file[0], j, i - j);
	return (1);
}

void	red_quote_expender(t_section *sect)
{
	t_red	*red;

	red = sect->first_red;
	while (red)
	{
		red->temp = ft_calloc(2 * quote_count(red->file[0]) + 2,
				sizeof(char *));
		if (!red->temp)
			clean_exit(sect->data);
		red->protection = ft_calloc(2 * quote_count(red->file[0]) + 2,
				sizeof(int));
		if (!red->protection)
			clean_exit(sect->data);
		if (!temp_filling(red))
			clean_exit(sect->data);
		red = red->next;
	}
}
