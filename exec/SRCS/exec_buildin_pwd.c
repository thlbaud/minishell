/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_pwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:16:16 by thibaud           #+#    #+#             */
/*   Updated: 2024/04/21 22:49:37 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

void	_bi_pwd(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr)
{
	int		fd_f[2];
	int		res[2];
	char	*buff;

	fd_f[0] = 0;
	fd_f[1] = 1;
	if (s_cmd->file)
		_open_file(args, s_cmd->file, fd_f);
	if (fd_f[1] == 1 && s_cmd->next)
		fd_f[1] = fd_pw[1];
	buff = _define_cwd();
	if (!buff)
		_error_exit(args, NULL, 1);
	res[0] = write(fd_f[1], buff, ft_strlen(buff, 0));
	if (res[0] != -1)
		res[1] = write(fd_f[1], "\n", 1);
	_pipe_closer(fd_pr, fd_pw, fd_f);
	free (buff);
	if (res[0] == -1 || res[1] == -1)
		_error_exit(args, NULL, 1);
}
