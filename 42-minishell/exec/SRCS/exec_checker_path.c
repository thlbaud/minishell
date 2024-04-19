/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_checker_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:52:42 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/19 10:39:34 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

static char	**_env_check(t_data *args)
{
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	while (args->env[i] && ft_strncmp("PATH=", args->env[i], 5) != 0)
		++i;
	if (args->env[i] != 0)
	{
		path = ft_split(args->env[i], ':');
		if (!path)
			_error_exit(args, NULL, 1);
	}
	return (path);
}

static char	*_give_path(t_data *args, char **path, char *cmd)
{
	char	*path_cmd;
	char	*temp;
	int		i;

	i = 0;
	temp = ft_strjoin("/", cmd);
	if (!temp)
		_error_exit(args, NULL, 1);
	while (path[i])
	{
		path_cmd = ft_strjoin(path[i], temp);
		if (!path_cmd)
			_error_exit(args, NULL, 1);
		if (access(path_cmd, X_OK) == 0)
			break ;
		free (path_cmd);
		++i;
	}
	free(temp);
	if (!path[i])
	{
		_freetab(path);
		return (NULL);
	}
	_freetab(path);
	return (path_cmd);
}

void	_pathfinder(t_data *args, char **cmd)
{
	char	**env_path;
	char	*path_cmd;

	env_path = _env_check(args);
	if (access(cmd[0], X_OK) == 0 || !env_path)
		return ;
	path_cmd = _give_path(args, env_path, cmd[0]);
	if (!path_cmd)
		return ;
	free (cmd[0]);
	cmd[0] = path_cmd;
}
