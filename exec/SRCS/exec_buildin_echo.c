/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_echo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:49:44 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/24 19:24:18 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

static inline _Bool	_srch_flag(char *path)
{
	if (!path)
		return (0);
	if (path[0] != '-')
		return (0);
	if (!ft_strfull(&path[1], 'n'))
		return (1);
	return (0);
}

static inline _Bool	_write_echo(char **path_cmd)
{
	int	res_flag;
	int	i;

	res_flag = _srch_flag(path_cmd[1]);
	i = res_flag + 1;
	while (path_cmd[i] && _srch_flag(path_cmd[i]) == 1)
		++i;
	while (path_cmd[i])
	{
		if (write(1, path_cmd[i], ft_strlen(path_cmd[i], 0)) == -1)
			return (1);
		if (path_cmd[++i])
			if (write(1, " ", 1) == -1)
				return (1);
	}
	if (res_flag == 0 || !path_cmd[1])
		if (write(1, "\n", 1) == -1)
			return (1);
	return (0);
}

void	_bi_echo(t_data *args, t_section *s_cmd)
{
	args->exit_status = _write_echo(s_cmd->path_cmd);
	if (args->exit_status == 1)
		_exit_failure(args);
	args->exit_status = 0;
}
