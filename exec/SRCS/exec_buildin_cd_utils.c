/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_cd_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 03:31:26 by thibaud           #+#    #+#             */
/*   Updated: 2024/05/16 21:01:08 by tmouche          ###   ########.fr       */
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
		_export_oldpwd(args, ft_strjoin("OLDPWD=", old_pwd));
}

inline void	_export_oldpwd(t_data *args, char *old_pwd)
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