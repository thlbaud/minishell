/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:47:51 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/09 05:10:56 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"
#include <stdio.h>

void	_freeint(int **tab, int size)
{
	int	i;

	i = 0;
	while (i < size - 1 && tab[i])
	{
		free (tab[i]);
		++i;
	}
	free (tab);
}

void	_exec_failed(char **cmd, char **env, char *not_found)
{
	if (write(2, not_found, ft_strlen(not_found, 0)) == -1 ||
		write(2, ": command not found\n", 21) == -1)
	{
		_freetab(cmd);
		_freetab(env);
		exit (1);
	}
	_freetab(cmd);
	_freetab(env);
	g_err = 127;
	exit (127);
}

void	_on_error(t_data *args, char *str, int err, e_write write_id)
{
	int	err_handling;
	
	g_err = err;
	err_handling = 1;
	if (write_id == WRITE)
		err_handling = write(2, str, ft_strlen(str, 0));
	else
		perror(str);
	if (str)
		free (str);
	if (err_handling == -1)
		_exit_failure(args);
	if (args->pipe)
		_freeint(args->pipe, args->count);
	if (args->pid)
		free (args->pid);
	else
		return ;
	if (args->head)
		_lstfree(args->head, SECTION_LST);
	if (args->path_history)
		free (args->path_history);
	if (args->env)
		_freetab(args->env);
	exit (g_err);
}


char	**_on_success(t_data *args, t_section *s_cmd, e_from from_id)
{
	char	**new;
	
	g_err = 0;
	if (args->pipe)
		_freeint(args->pipe, args->count);
	if (args->pid)
		free (args->pid);
	if (args->path_history)
		free (args->path_history);
	if (from_id == ALL)
	{
		if (args->head)
			_lstfree(args->head, SECTION_LST);
		if (args->env)
			_freetab(args->env);
		exit (EXIT_SUCCESS);
	}
	new = _map_cpy(s_cmd->path_cmd);
	if (!new)
		_exit_failure(args);
	if (args->head)
		_lstfree(args->head, SECTION_LST);
	return (new);
}
