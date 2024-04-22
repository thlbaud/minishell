/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_unset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:11:54 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/21 22:52:14 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

static inline void	_erase_args(t_data *args, int skip)
{
	char	**new_env;
	int		i;

	i = 0;
	while (args->env[i])
		++i;
	new_env = ft_calloc(sizeof(char *), i);
	if (!new_env)
		_error_exit(args, NULL, 1);
	i = 0;
	while (args->env[i])
	{
		if (i != skip)
			new_env[i] = args->env[i];
		++i;
	}
	_freetab(args->env);
	args->env = new_env;
}

void	_bi_unset(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr)
{
	int		fd_f[2];
	int		i_args;
	int		i_env;

	fd_f[0] = 0;
	fd_f[1] = 1;
	if (s_cmd->file)
		_open_file(args, s_cmd->file, fd_f);
	_pipe_closer(fd_pr, fd_pw, fd_f);
	i_args = 1;
	while (s_cmd->path_cmd[i_args])
	{
		i_env = 0;
		while (args->env[i_env])
		{
			if (ft_strncmp(s_cmd->path_cmd[i_args], args->env[i_env],
					ft_strlen(s_cmd->path_cmd[i_args], 0)) == 0)
			{
				_erase_args(args, i_env);
				break ;
			}
			++i_env;
		}
		++i_args;
	}
}
