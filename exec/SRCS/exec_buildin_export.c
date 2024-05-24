/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:19:58 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/24 19:18:44 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

static inline _Bool	_export_args(char *str, size_t n)
{
	size_t	index;

	index = 0;
	while (str[index] && index < n)
	{
		if ((str[index] >= 48 && str[index] <= 57)
			|| (str[index] >= 65 && str[index] <= 90)
			|| (str[index] >= 97 && str[index] <= 122)
			|| str[index] == 95)
			++index;
		else
			return (0);
	}
	return (1);
}

static inline _Bool	_do_args(t_data *args, t_section *s_cmd,
		t_index *lst, int i_args)
{
	char	*str_err;

	if (_export_args(s_cmd->path_cmd[i_args],
			ft_strlen(s_cmd->path_cmd[i_args], '=')) == 0
		|| s_cmd->path_cmd[i_args][0] == '='
		|| (s_cmd->path_cmd[i_args][0] >= '0'
		&& s_cmd->path_cmd[i_args][0] <= '9')
		|| s_cmd->path_cmd[i_args][0] == 0)
	{
		str_err = _give_strerror_identifier(args, lst,
				s_cmd->path_cmd[i_args]);
		_on_error(args, str_err, 1, WRITE);
	}
	else if (ft_strrchr(s_cmd->path_cmd[i_args], '='))
	{
		if (_egal_present(args, s_cmd, &lst, i_args) == 0)
			return (1);
		_add_to_env_history(args, s_cmd->path_cmd[i_args]);
	}
	else
		_add_to_env_history(args, s_cmd->path_cmd[i_args]);
	return (0);
}

static inline void	_set_export(t_data *args, t_section *s_cmd)
{
	t_index	*lst;
	int		i_args;

	i_args = 1;
	lst = NULL;
	while (s_cmd->path_cmd[i_args])
	{
		if (_do_args(args, s_cmd, lst, i_args) == 1)
			return ;
		++i_args;
	}
	_export_str(args, s_cmd, lst);
}

void	_bi_export(t_data *args, t_section *s_cmd)
{
	if (!s_cmd->path_cmd[1])
		if (_write_env(args->env_history, NULL) == 0)
			_exit_failure(args);
	_set_export(args, s_cmd);
	args->exit_status = 0;
}
