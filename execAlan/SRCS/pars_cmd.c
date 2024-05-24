/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:53:12 by avaldin           #+#    #+#             */
/*   Updated: 2024/04/29 16:19:35 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/parsing.h"
#include "../include/libft/libft.h"

static void	bad_var(t_section *sect)
{
	int	i;

	i = 0;
	while (sect->pipe[i])
	{
		if (sect->pipe[i] == '"' || sect->pipe[i] == 39)
			i += skip_quote(&sect->pipe[i]) + 2;
		else if (sect->pipe[i] == '$' && (sect->pipe[i + 1] == '"'
				|| sect->pipe[i + 1] == 39))
			sect->pipe = str_cut(sect->pipe, i, i);
		else
			i++;
	}
}

static void	cmd_process_var(t_section *sect, char **env)
{
	int	i;
	int	flag;

	i = 0;
	flag = -1;
	bad_var(sect);
	while (sect->pipe && sect->pipe[i])
	{
		if (sect->pipe[i] == '"')
			flag = -flag;
		if (sect->pipe[i] == 39 && flag == -1)
			i += skip_quote(&sect->pipe[i]) + 2;
		else if (sect->pipe[i] == '$')
			sect->pipe = apply_var(sect->pipe, env, &i, sect);
		else
			i++;
	}
}

void	command(t_section *first, char **env)
{
	t_section	*sect;

	sect = first;
	while (sect)
	{
		cmd_process_var(sect, env);
		cleaning_cmd(sect, sect->pipe);
		sect = sect->next;
	}
}

// int cmd_count(char *line)
// {
// 	int count;
// 	int	i;

// 	i = 0;
// 	count = 0;
// 	while (line[i] && line[i] != '|')
// 	{
// 		if (line[i] != ' ' && line[i] != '	')
// 		{
// 			count++;
// 			while (line[i] && line[i] != ' ' && line[i] != '	')
// 			{
// 				if (line[i] == '"' || line[i] == 39)
// 					i += skip_quote(&line[i]) + 1;
// 				i++;
// 			}
// 		}
// 		i++;
// 	}
// 	return (count);
// }

// int cmd_len(char *line)
// {
// 	int i;
// 	int len;

// 	i = 0;
// 	len = 0;
// 	while (line[i] && line[i] != '|' && line[i] != ' ' && line[i] != '	')
// 	{
// 		if (line[i] == '"' || line[i] == 39)
// 		{
// 			len += skip_quote(&line[i]);
// 			i += skip_quote(&line[i]) + 2;
// 		}
// 		else
// 		{
// 			len++;
// 			i++;
// 		}
// 	}
// 	return (len);
// }

// int add_cmd(char *line, char *cmd)
// {
// 	int i;
// 	int len;

// 	i = 0;
// 	len = 0;
// 	while (line[i] && line[i] != '|' && line[i] != ' ' && line[i] != '	')
// 	{
// 		if (line[i] == '"' || line[i] == 39)
// 		{
// 			len += write_quote(&line[i], &cmd[len]);
// 			i += skip_quote(&line[i]) + 2;
// 		}
// 		else
// 		{
// 			cmd[len] = line[i];
// 			len++;
// 			i++;
// 		}
// 	}
// 	return (i);
// }

// void	cleaning_cmd(t_section *sect, char *line)
// {
// 	int		i;
// 	int 	i_cmd;
// 	char	**cmd;

// 	i = 0;
// 	i_cmd = 0;
// 	cmd = ft_calloc(cmd_count(line) + 1, sizeof(char *));
// 	if (!cmd)
// 		exit (10);  // pas ok
// 	while (line[i] && line[i] != '|')
// 	{
// 		if (line[i] != ' ' && line[i] != '	')
// 		{
// 			cmd[i_cmd] = ft_calloc(cmd_len(&line[i]) + 1, sizeof(char));
// 			i += add_cmd(&line[i], cmd[i_cmd]);
// 			i_cmd++;
// 		}
// 		else
// 			i++;
// 	}
// 	sect->path_cmd = cmd;
// }