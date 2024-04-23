/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:25:47 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/23 15:20:36 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

void	_bi_exit(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr)
{
	int		fd_f[2];

	fd_f[0] = 0;
	fd_f[1] = 1;
	if (s_cmd->file)
		_open_file(args, s_cmd->file, fd_f);
	_pipe_closer(fd_pr, fd_pw, fd_f);
	if (args->pid)
		free (args->pid);
	if (args->head)
		_lstfree(args->head, SECTION_LST);
	if (args->path_history)
		free (args->path_history);
	if (args->env)
		_freetab(args->env);
	exit (EXIT_SUCCESS);
}
