/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:52:42 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/21 16:07:30 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../HDRS/pipex.h"
#include "../include/libft/libft.h"

static char	**_env_check(t_data *args, char **cmd)
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

void	_pathfinder(t_data *args, char **cmd)
{
	char	*path_cmd;
	
	if (ft_strchr(cmd[0], '/') != NULL)
		if (access(cmd[0], X_OK) != -1)
			return ;
	path_cmd = _give_path(_env_check(args, cmd), cmd[0]);
	if (!path_cmd)
		_error(args, cmd, -1);
	free (cmd[0]);
	cmd[0] = path_cmd;
}
