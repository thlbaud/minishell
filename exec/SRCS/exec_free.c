/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:47:51 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/23 16:45:05 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"
#include <stdio.h>

void	_on_error(t_data *args, char *str, e_write write_id)
{
	int	err_handling;
	
	g_err = 1;
	err_handling = 1;
	if (write_id == WRITE)
		err_handling = write(2, str, ft_strlen(str, 0));
	else
		perror(str);
	if (str)
		free (str);
	if (err_handling == -1)
		_exit_failure(args);
	if (args->head)
		_lstfree(args->head, SECTION_LST);
	if (args->pid)
		free (args->pid);
	else
		return ;
	if (args->path_history)
		free (args->path_history);
	if (args->env)
		_freetab(args->env);
	exit (EXIT_FAILURE);
}

char	**_on_success(t_data *args, t_section *s_cmd, e_from from_id)
{
	char	**new;
	
	g_err = 0;
	if (from_id == BUILDIN)
	{
		if (args->head)
			_lstfree(args->head, SECTION_LST);
	}
	if (args->pid)
	{
		free (args->pid);
		if (args->path_history)
			free (args->path_history);
		if (from_id == BUILDIN)
		{
			if (args->env)
				_freetab(args->env);
			exit (EXIT_SUCCESS);
		}
		new = _map_cpy(s_cmd->path_cmd);
		if (!new)
			_exit_failure(args);
		return (new);
	}
	return (NULL);
}