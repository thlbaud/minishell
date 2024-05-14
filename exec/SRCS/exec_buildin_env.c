/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:58:59 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/14 21:35:14 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

_Bool	_write_env(char **env, char *pre_str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (pre_str)
			if (write(STDOUT_FILENO, pre_str, ft_strlen(pre_str, 0)) == -1
				|| write(STDOUT_FILENO, " ", 1) == -1)
				return (0);
		if (write(STDOUT_FILENO, env[i], ft_strlen(env[i], 0)) == -1
			|| write(STDOUT_FILENO, "\n", 1) == -1)
			return (0);
		++i;
	}
	return (1);
}

void	_bi_env(t_data *args, t_section *s_cmd)
{
	char	*error;
	int		res;

	printf("open past\n");
	if (s_cmd->path_cmd[1])
	{
		_close_pipe(args);
		error = ft_strdup("env: Too much arguments\n");
		if (!error)
			_exit_failure(args);
		_on_error(args, error, 1, WRITE);
		return ;
	}
	res = _write_env(args->env, NULL);
	_close_pipe(args);
	if (res == -1)
		_exit_failure(args);
}
