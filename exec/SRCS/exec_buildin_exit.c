/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:25:47 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/05 19:06:32 by tmouche          ###   ########.fr       */
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
	_freetab(args->env);
	_lstfree(args->head, SECTION_LST);
	exit (EXIT_SUCCESS);
}
