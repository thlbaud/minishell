/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_export_history.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:21:00 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/14 22:22:53 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

static inline char	*_add_quote(t_data *args, char *cmd)
{
	char	*temp;
	int		i_cmd;
	int		i_temp;
	
	temp = ft_calloc(sizeof(char), ft_strlen(cmd, 0) + 3);
	if (!temp)
	{
		free (cmd);
		_exit_failure(args);
	}
	i_cmd = 0;
	i_temp = 0;
	while (cmd[i_cmd] != '=')
	{
		temp[i_temp] = cmd[i_cmd];
		++i_temp;
		++i_cmd;
	}
	temp[i_temp] = cmd[i_cmd];
	++i_temp;
	++i_cmd;
	temp[i_temp] = '"';
	++i_temp;
	while (cmd[i_cmd])
	{
		temp[i_temp] = cmd[i_cmd];
		++i_temp;
		++i_cmd;
	}
	temp[i_temp] = '"';
	free (cmd);
	return (temp);
}

static inline void	_add_line_history(t_data *args, char **env_history, char *cmd)
{
	char	**new_env_history;
	int		size_history;
	int		i;
	
	size_history = _size_map(env_history);
	new_env_history = ft_calloc(sizeof(char *), size_history + 2);
	if (!new_env_history)
	{
		free (cmd);
		_exit_failure(args);
	}
	if (ft_strrchr(cmd, '='))
		cmd = _add_quote(args, cmd);
	i = 0;
	while (i < size_history)
	{
		new_env_history[i] = env_history[i];
		++i; 
	}
	new_env_history[i] = cmd;
	if (env_history)
		free (env_history);
	args->env_history = new_env_history;
}

void	_add_to_env_history(t_data *args, char *new_cmd)
{
	char	*declare;
	char	*expand_cmd;

	declare = ft_strdup("export ");
	if (!declare)
		_exit_failure(args);
	expand_cmd = ft_strjoin(declare, new_cmd);
	free (declare);
	if (!expand_cmd)
		_exit_failure(args);
	_add_line_history(args, args->env_history, expand_cmd);
}