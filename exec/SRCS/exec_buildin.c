/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:53:46 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/23 08:52:43 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

int	_is_a_buildin(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr)
{
	if (!s_cmd->path_cmd)
		return (0);
	else if (ft_strncmp("echo", s_cmd->path_cmd[0], 4) == 0)
		_bi_echo(args, s_cmd, fd_pw, fd_pr);
	else if (ft_strncmp("cd", s_cmd->path_cmd[0], 2) == 0)
		_bi_cd(args, s_cmd, fd_pw, fd_pr);
	else if (ft_strncmp("pwd", s_cmd->path_cmd[0], 3) == 0)
		_bi_pwd(args, s_cmd, fd_pw, fd_pr);
	else if (ft_strncmp("export", s_cmd->path_cmd[0], 6) == 0)
		_bi_export(args, s_cmd, fd_pw, fd_pr);
	else if (ft_strncmp("unset", s_cmd->path_cmd[0], 6) == 0)
		_bi_unset(args, s_cmd, fd_pw, fd_pr);
	else if (ft_strncmp("env", s_cmd->path_cmd[0], 6) == 0)
		_bi_env(args, s_cmd, fd_pw, fd_pr);
	else if (ft_strncmp("exit", s_cmd->path_cmd[0], 6) == 0)
		_bi_exit(args, s_cmd, fd_pw, fd_pr);
	else if (ft_strncmp("history", s_cmd->path_cmd[0], 6) == 0)
		_bi_history(args, s_cmd, fd_pw, fd_pr);
	else
		return (0);
	if (!s_cmd->prev && !s_cmd->next)
		return (1);
	s_cmd = s_cmd->next;
	return (0);
}
