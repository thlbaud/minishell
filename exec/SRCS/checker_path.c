/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:52:42 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/22 19:31:33 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../HDRS/pipex.h"
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
			exit (EXIT_FAILURE); //RETOUR ERREUR 
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
		exit (EXIT_FAILURE); //RETOUR ERREUR
	while (path[i])
	{
		path_cmd = ft_strjoin(path[i], temp);
		if (!path_cmd)
			exit (EXIT_FAILURE); //RETOUR ERREUR
		if (access(path_cmd, X_OK) == 0)
			break;
		free (path_cmd);
		++i;
	}
	free(temp);
	_freetab(path);
	if (path[i] != 0)
		return (path_cmd);
	free(path_cmd);
	return (NULL);
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
