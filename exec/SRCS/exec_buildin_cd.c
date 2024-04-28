/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:37:51 by thibaud           #+#    #+#             */
/*   Updated: 2024/04/28 22:09:22 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"
#include <stdio.h>

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
static inline void	_change_dir(t_data *args, t_section *s_cmd, char	*old_pwd)
{
	char	*temp;

	if (chdir(s_cmd->path_cmd[1]) == -1)
	{
		temp = ft_strjoin("bash: cd: ", s_cmd->path_cmd[1]);
		free (old_pwd);
		if (!temp)
			_exit_failure(args);
		_on_error(args, temp, 1, AUTO);
	}
	else
		_export_oldpwd(args, ft_strjoin("OLDPWD=", old_pwd));
}

static inline _Bool	_check_args(t_data *args, t_section *s_cmd)
{
	int		index;

	index = 0;
	while (s_cmd->path_cmd[index])
		++index;
	if (index <= 2)
		return (1);
	_on_error(args, _get_str(args, "bash: cd: too many args\n"), 1, WRITE);
	return (0);
}

static inline _Bool	_handle_home(t_data *args, t_section *s_cmd, char *home)
{
	char	**new_path;
	char	*strhome;
	char	*temp;

	if (!home)
	{
		_on_error(args, _get_str(args, "bash: cd: HOME not set\n"), 1, WRITE);
		return (0);
	}
	new_path = ft_calloc(sizeof(char *), 3);
	if (!new_path)
		_exit_failure(args);
	new_path[0] = _get_str(args, s_cmd->path_cmd[0]);
	temp = _get_str(args, &home[ft_strlen(home, '=') + 1]);
	strhome = ft_strjoin(temp, "/");
	free(temp);
	if (!strhome)
		_exit_failure(args);
	if (!s_cmd->path_cmd[1])
		new_path[1] = strhome;
	else
	{
		temp = ft_strjoin(strhome, s_cmd->path_cmd[1]);
		free (strhome);
		if (!temp)
			_exit_failure(args);
	}
	_freetab(s_cmd->path_cmd);
	s_cmd->path_cmd = new_path;
	return (1);
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
	if (_check_args(args, s_cmd) == 0)
		return ;
	old_pwd = _define_cwd();
	if (!old_pwd)
		_exit_failure(args);
	if (!s_cmd->path_cmd[1] || s_cmd->path_cmd[1][0] == '~')
		if (_handle_home(args, s_cmd, _getenv(args->env, "HOME=")) == 0)
			return ;
	_change_dir(args, s_cmd, old_pwd);
}
