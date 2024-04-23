/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_checker_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:52:42 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/24 00:57:34 by thibaud          ###   ########.fr       */
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
	free(temp);
	if (path[i] != 0)
		return (_freetab(path), path_cmd);
	return (_freetab(path), NULL);
}

void	_pathfinder(t_data *args, char **cmd)
{
	char	**env_path;
	char	*path_cmd;

	if (!cmd)
		return ;
	env_path = _env_check(args);
	if (access(cmd[0], X_OK) == 0 || !env_path)
		return ;
	path_cmd = _give_path(args, env_path, cmd[0]);
	if (!path_cmd)
		return ;
	free (cmd[0]);
	cmd[0] = path_cmd;
}
