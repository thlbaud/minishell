/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_checker_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:52:42 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/27 15:35:54 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
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
			_exit_failure(args);
	}
	return (path);
}

static char	*_path_test(t_data *args, char **path, char *temp, int i)
{
	char	*path_cmd;

	path_cmd = ft_strjoin(path[i], temp);
	if (!path_cmd)
	{
		free (temp);
		_exit_failure(args);
	}
	if (access(path_cmd, F_OK) == 0)
	{
		if (access(path_cmd, X_OK) == -1)
			args->exit_status = 126;
		return (path_cmd);
	}
	free (path_cmd);
	return (NULL);
}

static char	*_give_path(t_data *args, char **path, char *cmd)
{
	char	*path_cmd;
	char	*temp;
	int		i;

	i = 0;
	temp = ft_strjoin("/", cmd);
	if (!temp)
		_exit_failure(args);
	while (path[i])
	{
		path_cmd = _path_test(args, path, temp, i);
		if (path_cmd)
			break ;
		++i;
	}
	free (temp);
	if (path[i] != 0 && cmd[0])
		return (_freetab(path), path_cmd);
	_freetab(path);
	_on_error(args, _give_strerror_cmd(args, cmd), 127, WRITE);
	return (NULL);
}

void	_pathfinder(t_data *args, char **cmd)
{
	char	**env_path;
	char	*path_cmd;
	DIR		*dir_path;

	env_path = _env_check(args);
	if (!env_path)
		return ;
	dir_path = opendir(cmd[0]);
	if (dir_path != NULL)
	{
		if (closedir(dir_path) == -1)
			_exit_failure(args);
		args->exit_status = 126;
		_on_error(args, _give_strerror_dir(args, cmd[0]),
			args->exit_status, WRITE);
	}
	if (access(cmd[0], X_OK) == 0 || !env_path)
		return ;
	path_cmd = _give_path(args, env_path, cmd[0]);
	free (cmd[0]);
	cmd[0] = path_cmd;
}
