/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:58:26 by avaldin           #+#    #+#             */
/*   Updated: 2024/04/17 09:25:45 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	add_section(t_data *data, char *line, int start, int end)
{
	t_section	*sect;

	sect = ft_calloc(1, sizeof(t_section));
	if (!sect)
		clean_exit(data);
	sect->pipe = ft_strdup(line, start, end - start);
	if (!sect->pipe)
		clean_exit(data);
	data->first = ft_sectadd_back(data->first, sect);
	sect->data = data;
}

void	create_section(char *line, t_data *data)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	data->first = NULL;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == 39)
			i += skip_quote(&line[i]) + 1;
		else if (line[i] == '|' || !line[i])
		{
			add_section(data, line, j, i);
			j = i + 1;
		}
		i++;
	}
	add_section(data, line, j, i);
}

void	parsing(char *line, char **env, t_data *data)
{
	if (checking(line))
	{
		data->first = NULL;
		return ;
	}
	create_section(line, data);
	redirection(data, env);
	command(data->first, env);
}
