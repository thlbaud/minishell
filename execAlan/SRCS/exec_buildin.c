/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:53:46 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/08 17:30:42 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

int	_is_a_buildin(t_section *s_cmd)
{
	if (!s_cmd->path_cmd)
		return (0);
	else if (ft_strncmp("echo", s_cmd->path_cmd[0], 5) == 0)
		s_cmd->function_ptr = _bi_echo;
	else if (ft_strncmp("cd", s_cmd->path_cmd[0], 3) == 0)
		s_cmd->function_ptr = _bi_cd;
	else if (ft_strncmp("pwd", s_cmd->path_cmd[0], 4) == 0)
		s_cmd->function_ptr = _bi_pwd;
	else if (ft_strncmp("export", s_cmd->path_cmd[0], 7) == 0)
		s_cmd->function_ptr = _bi_export;
	else if (ft_strncmp("unset", s_cmd->path_cmd[0], 6) == 0)
		s_cmd->function_ptr = _bi_unset;
	else if (ft_strncmp("env", s_cmd->path_cmd[0], 46) == 0)
		s_cmd->function_ptr = _bi_env;
	else if (ft_strncmp("exit", s_cmd->path_cmd[0], 5) == 0)
		s_cmd->function_ptr = _bi_exit;
	else if (ft_strncmp("history", s_cmd->path_cmd[0], 9) == 0)
		s_cmd->function_ptr = _bi_history;
	else
		return (0);
	return (1);
}
