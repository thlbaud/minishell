/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_history_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche < tmouche@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:27:40 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/02 17:24:18 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

static inline void _history_error(t_data *args, char *error, char *bad_args)
{
	char	*res;
	char	*temp;
	
	temp = ft_strjoin("bash: history: ", bad_args);
	if (!temp)
		_exit_failure(args);
	res = ft_strjoin(temp, error);
	free (temp);
	if (!res)
		_exit_failure(args);
	_on_error(args, res, 1, WRITE);
}

static inline int	_numeric_args_history(t_data *args, char *str)
{
	size_t	i;
	size_t	result;

	i = -1;
	result = 0;
	while ((str[++i] >= 9 && str[i] <= 13) || str[i] == 32)
		;
	if (str[i] == 43 && str[i + 1] != 0)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
		result = result * 10 + (str[i++] - 48);
	if (str[i])
		_history_error(args, ": numeric argument required\n", str);
	return (result);
}

inline int	_check_args_history(t_data *args, t_section *s_cmd)
{
	int		i_args;
	int 	res;

	i_args = 1;
	res = -2;
	if (s_cmd->path_cmd[i_args])
	{
		res = _numeric_args_history(args, s_cmd->path_cmd[i_args]);
		if (s_cmd->path_cmd[++i_args])
		{
			_history_error(args, "too many arguments\n", NULL);
			return (-1);
		}
	}
	return (res);
}