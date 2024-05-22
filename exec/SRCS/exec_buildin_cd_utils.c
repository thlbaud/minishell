/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_cd_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 03:31:26 by thibaud           #+#    #+#             */
/*   Updated: 2024/05/21 23:28:48 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

inline void	_change_dir(t_data *args, t_section *s_cmd, char *old_pwd)
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
	{
		temp = ft_strjoin("OLDPWD=", old_pwd);
		free (old_pwd);
		_export_pwd(args, temp);
	}
}

inline void	_export_pwd(t_data *args, char *pwd)
{
	char	**new_env;
	int		i;

	if (!pwd)
		_exit_failure(args);
	i = 0;
	while (args->env[i])
	{
		if (ft_strncmp(pwd, args->env[i], ft_strlen(pwd, '=')) == 0)
		{
			free (args->env[i]);
			args->env[i] = pwd;
			break ;
		}
		if (!args->env[++i] && (!ft_strncmp(pwd, "PWD=", 4)) == 0)
		{
			new_env = ft_stradd(args->env, pwd);
			if (!new_env)
			{
				free (pwd);
				_exit_failure(args);
			}
			args->env = new_env;
		}
	}
}
