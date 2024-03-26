/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:53:46 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/26 17:45:58 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

void	_is_a_buildin(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr)
{
	if (ft_strncmp("echo", s_cmd->path_cmd[0], 4) == NULL)
		_bi_echo();
	else if (ft_strncmp("cd", s_cmd->path_cmd[0], 2) == NULL)
		_bi_cd();
	else if (ft_strncmp("pwd", s_cmd->path_cmd[0], 3) == NULL)
		_bi_pwd();
	else if (ft_strncmp("export", s_cmd->path_cmd[0], 6) == NULL)
		_bi_export();
	else if (ft_strncmp("unset", s_cmd->path_cmd[0], 6) == NULL)
		_bi_unset();
	else if (ft_strncmp("env", s_cmd->path_cmd[0], 6) == NULL)
		_bi_env();
	else if (ft_strncmp("exit", s_cmd->path_cmd[0], 6) == NULL)
		_bi_exit();
	return ;
}