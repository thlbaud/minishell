/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:53:12 by avaldin           #+#    #+#             */
/*   Updated: 2024/04/17 17:59:12 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/parsing.h"
#include "../include/libft/libft.h"

static int	cmd_count(char *line)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			count++;
			while (line[i] && line[i] != ' ')
			{
				if (line[i] == '"' || line[i] == 39)
					i += skip_quote(&line[i]) + 1;
				i++;
			}
		}
		else
			i++;
	}
	return (count);
}

static int	cmd_len(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '"' || line[i] == 39)
		{
			len += skip_quote(&line[i]);
			i += skip_quote(&line[i]) + 2;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static int	add_cmd(char *line, char *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '"' || line[i] == 39)
		{
			len += write_quote(&line[i], &cmd[len]);
			i += skip_quote(&line[i]) + 2;
		}
		else
		{
			cmd[len] = line[i];
			len++;
			i++;
		}
	}
	return (i);
}

void	cleaning_cmd(t_section *sect, char *line)
{
	int		i;
	int		i_cmd;
	char	**cmd;

	i = 0;
	i_cmd = 0;
	cmd = ft_calloc(cmd_count(line) + 1, sizeof(char *));
	if (!cmd)
		clean_exit(sect->data);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '	')
		{
			cmd[i_cmd] = ft_calloc(cmd_len(&line[i]) + 1, sizeof(char));
			if (!cmd[i_cmd])
				clean_exit(sect->data);
			i += add_cmd(&line[i], cmd[i_cmd]);
			i_cmd++;
		}
		else
			i++;
	}
	sect->path_cmd = cmd;
}
