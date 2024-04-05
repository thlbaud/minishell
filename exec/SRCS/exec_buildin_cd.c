/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:37:51 by thibaud           #+#    #+#             */
/*   Updated: 2024/04/05 18:59:46 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

void	_bi_cd(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr)
{
	int		fd_f[2];

	fd_f[0] = 0;
	fd_f[1] = 1;
	if (s_cmd->file)
		_open_file(args, s_cmd->file, fd_f);
	_pipe_closer(fd_pr, fd_pw, fd_f);
	if (!s_cmd->path_cmd[1])
		return ;
	if (chdir(s_cmd->path_cmd[1]) == -1)
		perror(ft_strjoin("bash: ", s_cmd->path_cmd[0]));
}
