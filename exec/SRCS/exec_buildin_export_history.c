/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_export_history.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:21:00 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/20 22:13:45 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

static inline void	_strncpy(char *dst, char *src, int *index, int n)
{
	int	i;

	i = 0;
	while (src[*index] && i < n)
	{
		dst[index[1]] = src[index[0]];
		++index[0];
		++index[1];
		++i;
	}
}

static inline char	*_add_quote(t_data *args, char *cmd)
{
	char	*temp;
	int		index[2];

	temp = ft_calloc(sizeof(char), ft_strlen(cmd, 0) + 3);
	if (!temp)
	{
		free (cmd);
		_exit_failure(args);
	}
	index[0] = 0;
	index[1] = 0;
	_strncpy(temp, cmd, index, ft_strlen(cmd, '=') + 1);
	temp[index[1]] = '"';
	++index[1];
	_strncpy(temp, cmd, index, ft_strlen(&cmd[index[0]], 0));
	temp[index[1]] = '"';
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