/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_export_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:13:48 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/25 16:17:20 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"
#include <stdio.h>

static inline char	*_give_strerror(t_data *args, t_index *lst, char *str)
{
	char	*res;
	char	*temp;
	
	temp = ft_strjoin("bash: export: '", str);
	if (!temp)
	{
		_lstfree(lst, INDEX_LST);
		_exit_failure(args);
	}
	res = ft_strjoin(temp, "': not a valid identifier\n");
	free (temp);
	if (!res)
	{
		_lstfree(lst, INDEX_LST);
		_exit_failure(args);
	}
	return (res);
}

_Bool	_egal_notpresent(t_data *args, t_section *s_cmd, t_index *lst, int i_args)
{
	char	*str_err;
	
	if (_str_no_spe_char(s_cmd->path_cmd[i_args], ft_strlen(s_cmd->path_cmd[i_args], 0)) == 0)
	{
		str_err = _give_strerror(args, lst, s_cmd->path_cmd[i_args]);
		_on_error(args, str_err, 1, WRITE);
		return (0);
	}
	return (1);
}

static inline int	_check_exist(t_index **lst, char **path_cmd, int i_args)
{
	int	i;

	i = 1;
	while (i < i_args)
	{
		if (ft_strncmp(path_cmd[i], path_cmd[i_args],
				ft_strlen(path_cmd[i_args], '=')) == 0)
		{
			while ((*lst)->i != i)
				(*lst) = (*lst)->next;
			(*lst)->i = i_args;
			return (0);
		}
		++i;
	}
	return (1);
}

_Bool	_egal_present(t_data *args, t_section *s_cmd, t_index **lst, int i_args)
{
	t_index	*temp;
	char	*str_err;
	
	temp = NULL;
	if (_str_no_spe_char(s_cmd->path_cmd[i_args], ft_strlen(s_cmd->path_cmd[i_args], '=')) == 0
		|| s_cmd->path_cmd[i_args][0] == '=')
	{
		str_err = _give_strerror(args, *lst, s_cmd->path_cmd[i_args]);
		_on_error(args, str_err, 1, WRITE);
		return (0);
	}
	if (_check_exist(lst, s_cmd->path_cmd, i_args) == 1)
	{
		temp = _lstnew_index(i_args);
		if (!temp)
		{
			_lstfree(*lst, INDEX_LST);
			_exit_failure(args);
		}
		_lstaddback_index(lst, temp);
	}
	return (1);
}