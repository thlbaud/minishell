/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_checker_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:52:42 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/13 06:28:53 by thibaud          ###   ########.fr       */
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

static inline char	*_give_strerror_cmd(t_data *args, char *str)
{
	char	*res;
	
	res = ft_strjoin(str, ": command not found\n");
	if (!res)
		_exit_failure(args);
	return (res);
}

static inline char	*_give_strerror_dir(t_data *args, char *str)
{
	char	*res;
	char	*temp;
	
	temp = ft_strjoin("bash: ", str);
	if (!temp)
		_exit_failure(args);
	res = ft_strjoin(str, ": Is a directory\n");
	free (temp);
	if (!res)
		_exit_failure(args);
	return (res);
}

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
		path_cmd = ft_strjoin(path[i], temp);
		if (!path_cmd)
			_exit_failure(args);
		if (access(path_cmd, X_OK) == 0)
			break ;
		free (path_cmd);
		++i;
	}
	free (temp);
	if (path[i] != 0)
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
	dir_path = opendir(cmd[0]);
	if (dir_path != NULL)
	{
		if (closedir(dir_path) == -1)
			_exit_failure(args);
		_on_error(args, _give_strerror_dir(args, cmd[0]), 126, WRITE);
	}
	if (access(cmd[0], X_OK) == 0 || !env_path)
		return ;
	path_cmd = _give_path(args, env_path, cmd[0]);
	free (cmd[0]);
	cmd[0] = path_cmd;
}
