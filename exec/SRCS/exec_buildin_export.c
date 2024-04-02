/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:19:58 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/02 20:24:50 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

static void	_export_str(t_data *args, t_section *s_cmd, t_index *lst)
{
	char	**new_env;
	char	*temp;
	size_t	len;
	int		i;
	
	while (lst)
	{
		len = ft_strlen(s_cmd->path_cmd[lst->i], 0);
		temp = ft_calloc(sizeof(char), len + 1);
		if (!temp)
		{
			//_free_lst(lst);
			_error_exit(args, s_cmd->path_cmd[0]);
		}
		ft_strlcpy(temp, s_cmd->path_cmd[lst->i], len + 1);
		i = 0;
		while (args->env[i])
		{
			if (ft_strncmp(args->env[i], temp, ft_strlen(temp, '=')) == 0)
			{
				free (args->env[i]);
				args->env[i] = temp;
				break ;
			}
			if (!args->env[++i])
			{
				new_env = ft_stradd(args->env, temp);
				if (!new_env)
				{
					free (temp);
					//_free_lst(lst);
					_error_exit(args, s_cmd->path_cmd[0]);
				}
				args->env = new_env;
				break ;
			}
		}
		lst = lst->next;
	}
}

static int	_check_exist(t_index **lst, char **path_cmd, int i_args)
{
	int	i;

	i = 1;
	while (i < i_args)
	{
		if (ft_strncmp(path_cmd[i], path_cmd[i_args], ft_strlen(path_cmd[i_args], '=')) == 0)
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

void	_bi_export(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr)
{
	t_index	*lst;
	t_index	*temp;
	int		fd_f[2];
	int		i_args;

	fd_f[0] = 0;
	fd_f[1] = 1;
	if (s_cmd->file)
		_open_file(args, s_cmd->file, fd_f);
	_pipe_closer(fd_pr, fd_pw, fd_f);
	i_args = 1;
	lst = NULL;
	while (s_cmd->path_cmd[i_args])
	{
		if (ft_strrchr(s_cmd->path_cmd[i_args], '='))
		{
			if (_check_exist(&lst, s_cmd->path_cmd, i_args) == 1)
			{
				temp = _lstnew_index(i_args);
				if (!temp)
				{
					//_lstfree_index(lst);
					_error_exit(args, NULL);
				}
				_lstaddback_index(&lst, temp);
			}
		}
		++i_args;
	}
	_export_str(args, s_cmd, lst);
	return ;
}
