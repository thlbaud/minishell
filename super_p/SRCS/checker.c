/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:10:26 by thibaud           #+#    #+#             */
/*   Updated: 2024/03/19 19:11:39 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../HDRS/pipex.h"
#include "../include/libft/libft.h"

void	_check_file(char **cmd_path, char *file, int *fd, int cmd_num)
{
	if (cmd_num == -1)
	{
		if (!file[0])
			_write_error("zsh: permission denied : ", file);
		else if (ft_strfull(file, ' ') == 0)
			_write_error("zsh: no such file or directory: ", file);
		else
			return ;
		_error(cmd_path, -1, fd);
	}
	if (access(file, F_OK) == -1 && (cmd_num == 1 || cmd_num == 0))
	{
		_write_error("zsh: no such file or directory: ", file);
		_error(cmd_path, -1, fd);
	}
	else if (access(file, F_OK) == -1 && cmd_num == 2)
		return ;
	if ((access(file, X_OK) == -1 && cmd_num == 0)
		|| (access(file, R_OK) == -1 && cmd_num == 1)
		|| (access(file, W_OK) == -1 && cmd_num == 2))
		_write_error("zsh: permission denied : ", file);
	else
		return ;
	_error(cmd_path, -1, fd);
}

static char	**_env_check(char **env, char **cmd, int *fd)
{
	char	**path;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp("PATH=", env[i], 5) != 0)
		++i;
	if (env[i] == 0)
	{
		ft_putstr_fd("zsh: command not found: ", 2);
		ft_putstr_fd(cmd[0], 2);
		write (2, "\n", 1);
		close(fd[0]);
		close(fd[1]);
		_freetab(cmd);
		exit(EXIT_FAILURE);
	}
	path = ft_split(env[i], ':');
	if (!path)
		_error(cmd, -2, fd);
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

char	**_pathfinder(char **env, char *full_cmd, int	*fd)
{
	char	*path_cmd;
	char	**cmd;

	cmd = ft_split(full_cmd, ' ');
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd[0], '/') != NULL)
	{
		_check_file(cmd, cmd[0], fd, 0);
		return (cmd);
	}
	path_cmd = _give_path(_env_check(env, cmd, fd), cmd[0]);
	if (!path_cmd)
	{
		close(fd[0]);
		close(fd[1]);
		_freetab(cmd);
		free(path_cmd);
		return (NULL);
	}
	free (cmd[0]);
	cmd[0] = path_cmd;
	return (cmd);
}