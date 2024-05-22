/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:58:26 by avaldin           #+#    #+#             */
/*   Updated: 2024/04/30 19:18:04 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/parsing.h"
#include "../include/libft/libft.h"

static void	add_section(t_data *data, char *line, int start, int end)
{
	t_section	*sect;

	sect = ft_calloc(1, sizeof(t_section));
	if (!sect)
		clean_exit(data);
	sect->pipe = _strdup(line, start, end - start);
	if (!sect->pipe)
		clean_exit(data);
	sect->fd_f[0] = 0;
	sect->fd_f[1] = 1;
	data->head = ft_sectadd_back(data->head, sect);
	sect->data = data;
}

static void	create_section(char *line, t_data *data)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	data->head = NULL;
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
	if (line && line[0] && !checking(line))
	{
		create_section(line, data);
		redirection(data, env);
		command(data->head, env);
	}
	else
	{
		data->exit_status = 2;
		if (line && !line[0])
			data->exit_status = 0;
		data->head = NULL;
	}
}
