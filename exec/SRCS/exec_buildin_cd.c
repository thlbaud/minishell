/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:37:51 by thibaud           #+#    #+#             */
/*   Updated: 2024/05/21 23:04:48 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

static inline void	_home_case(t_data *args, t_section *s_cmd, char **new_path,
	char *search)
{
	char	*strhome;
	char	*temp;

	temp = NULL;
	if (!s_cmd->path_cmd[1])
		new_path[1] = _get_str(args, search);
	else
	{
		if (s_cmd->path_cmd[1][1] != '/')
		{
			temp = ft_strjoin(search, "/");
			if (!temp)
			{
				_freetab(new_path);
				_exit_failure(args);
			}
		}
		strhome = ft_strjoin(temp, &s_cmd->path_cmd[1][1]);
		if (temp)
			free (temp);
		if (!strhome)
			_exit_failure(args);
		new_path[1] = strhome;
	}
}

static inline _Bool	_spe_case(t_data *args, t_section *s_cmd, char *search,
	e_cdenv id_search)
{
	char	**new_path;

	if (!search)
	{
		if (id_search == HOME)
			_on_error(args, _get_str(args, "bash: cd: HOME not set\n"),
				1, WRITE);
		else if (id_search == OLDPWD)
			_on_error(args, _get_str(args, "bash: cd: OLDPWD not set\n"),
				1, WRITE);
		return (0);
	}
	new_path = ft_calloc(sizeof(char *), 3);
	if (!new_path)
		_exit_failure(args);
	new_path[0] = _get_str(args, s_cmd->path_cmd[0]);
	if (id_search == OLDPWD)
		new_path[1] = _get_str(args, search);
	else if (id_search == HOME)
		_home_case(args, s_cmd, new_path, search);
	_freetab(s_cmd->path_cmd);
	s_cmd->path_cmd = new_path;
	return (1);
}

static inline _Bool	_handling_spe(t_data *args, t_section *s_cmd)
{
	if (ft_strncmp(s_cmd->path_cmd[1], "~", 2) == 0
		|| ft_strncmp(s_cmd->path_cmd[1], "~/", 3) == 0
		|| !s_cmd->path_cmd[1])
	{
		if (_spe_case(args, s_cmd, _getenv(args->env, "HOME="), HOME) == 0)
			return (0);
	}
	else if (ft_strncmp(s_cmd->path_cmd[1], "-", 2) == 0)
	{
		if (_spe_case(args, s_cmd, _getenv(args->env, "OLDPWD="), OLDPWD) == 0)
			return (0);
	}
	return (1);
}

static inline _Bool	_check_args(t_data *args, t_section *s_cmd)
{
	int		index;

	index = 0;
	while (s_cmd->path_cmd[index])
		++index;
	if (index <= 2)
		return (1);
	_on_error(args, _get_str(args, "bash: cd: too many arguments\n"), 1, WRITE);
	return (0);
}

void	_bi_cd(t_data *args, t_section *s_cmd)
{
	char	*temp;
	char	*pwd;

	if (_check_args(args, s_cmd) == 0)
		return ;
	if (s_cmd->path_cmd[1])
		if (!s_cmd->path_cmd[1][0])
			return ;
	pwd = _define_cwd();
	if (!pwd)
		_exit_failure(args);
	if (_handling_spe(args, s_cmd) == 0)
		return ;
	_change_dir(args, s_cmd, pwd);
	pwd = _define_cwd();
	if (!pwd)
		_exit_failure(args);
	temp = ft_strjoin("PWD=", pwd);
	free (pwd);
	_export_pwd(args, temp);
}
