/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:10:26 by thibaud           #+#    #+#             */
/*   Updated: 2024/03/20 13:12:49 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../HDRS/pipex.h"
#include "../include/libft/libft.h"

void	_check_file(t_args *args, char **cmd_path, char *file, int cmd_num)
{
	if (cmd_num == -1)
	{
		if (!file[0])
			_write_error("zsh: permission denied : ", file);
		else if (ft_strfull(file, ' ') == 0)
			_write_error("zsh: no such file or directory: ", file);
		else
			return ;
		_error(args, cmd_path, -1);
	}
	if (access(file, F_OK) == -1 && (cmd_num == 1 || cmd_num == 0))
	{
		_write_error("zsh: no such file or directory: ", file);
		_error(args, cmd_path, -1);
	}
	else if (access(file, F_OK) == -1 && cmd_num == 2)
		return ;
	if ((access(file, X_OK) == -1 && cmd_num == 0)
		|| (access(file, R_OK) == -1 && cmd_num == 1)
		|| (access(file, W_OK) == -1 && cmd_num == 2))
		_write_error("zsh: permission denied : ", file);
	else
		return ;
	_error(args, cmd_path, -1);
}

static char	**_env_check(t_args *args, char **cmd)
{
	char	**path;
	int		i;

	i = 0;
	while (args->env[i] && ft_strncmp("PATH=", args->env[i], 5) != 0)
		++i;
	if (args->env[i] == 0)
	{
		_write_error("zsh: command not found: ", cmd[0]);
		_error(args, cmd, -1);
	}
	path = ft_split(args->env[i], ':');
	if (!path)
		_error(args, cmd, -1);
	return (path);
}

static char	*_give_path(char **path, char *cmd)
{
	char	*path_cmd;
	char	*temp;
	int		i;

	i = 0;
	temp = ft_strjoin("/", cmd);
	if (!temp)
		return (_freetab(path), NULL);
	while (path[i])
	{
		path_cmd = ft_strjoin(path[i], temp);
		if (!path_cmd)
			return (_freetab(path), free(temp), NULL);
		if (access(path_cmd, X_OK) == 0)
			return (_freetab(path), free(temp), path_cmd);
		free (path_cmd);
		++i;
	}
	_freetab(path);
	free(temp);
	_write_error("zsh: command not found: ", cmd);
	return (NULL);
}

char	**_pathfinder(t_args *args, char *full_cmd)
{
	char	*path_cmd;
	char	**cmd;

	cmd = ft_split(full_cmd, ' ');
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd[0], '/') != NULL)
	{
		_check_file(args, cmd, cmd[0], 0);
		return (cmd);
	}
	path_cmd = _give_path(_env_check(args, cmd), cmd[0]);
	if (!path_cmd)
		_error(args, cmd, -1);
	free (cmd[0]);
	cmd[0] = path_cmd;
	return (cmd);
}