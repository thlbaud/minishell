/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:37:51 by thibaud           #+#    #+#             */
/*   Updated: 2024/04/24 01:03:49 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

static inline void	_export_oldpwd(t_data *args, char *old_pwd)
{
	char	**new_env;
	int		i;

	if (!old_pwd)
		_exit_failure(args);
	i = 0;
	while (args->env[i])
	{
		if (ft_strncmp(old_pwd, args->env[i], 7) == 0)
		{
			free (args->env[i]);
			args->env[i] = old_pwd;
			break ;
		}
		if (!args->env[++i])
		{
			new_env = ft_stradd(args->env, old_pwd);
			if (!new_env)
			{
				free (old_pwd);
				_exit_failure(args);
			}
			args->env = new_env;
		}
	}
}
static inline void	_change_directory(t_data *args, t_section *s_cmd, char	*old_pwd)
{
	char	*temp;

	if (chdir(s_cmd->path_cmd[1]) == -1)
	{
		temp = ft_strjoin("bash: cd: ", s_cmd->path_cmd[1]);
		free (old_pwd);
		if (!temp)
			_exit_failure(args);
		_on_error(args, temp, AUTO);
	}
	else
	{
		_export_oldpwd(args, ft_strjoin("OLDPWD=", old_pwd));
		_on_success(args, s_cmd, BUILDIN);
	}
}

void	_bi_cd(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr)
{
	char	*old_pwd;
	int		fd_f[2];

	fd_f[0] = 0;
	fd_f[1] = 1;
	if (s_cmd->file)
		if (_open_file(args, s_cmd->file, fd_f) == 0)
			return ;
	_pipe_closer(fd_pr, fd_pw, fd_f);
	if (!s_cmd->path_cmd[1])
		return ;
	old_pwd = _define_cwd();
	if (!old_pwd)
		_exit_failure(args);
	_change_directory(args, s_cmd, old_pwd);
}
