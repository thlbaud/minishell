/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:25:47 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/24 18:36:17 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

static inline void	_exit_error(t_data *args, char *error, char *bad_args,
	t_err id_error)
{
	char	*res;
	char	*temp;

	temp = ft_strjoin("bash: exit: ", bad_args);
	if (!temp)
		_exit_failure(args);
	res = ft_strjoin(temp, error);
	free (temp);
	if (!res)
		_exit_failure(args);
	if (id_error == NOT_NUMERIC)
	{
		_on_error(args, res, 2, WRITE);
		exit (args->exit_status);
	}
	_on_error(args, res, 1, WRITE);
}

static inline int	_numeric_args(t_data *args, char *str)
{
	size_t	i;
	size_t	result;
	int		sign;

	i = -1;
	sign = 1;
	result = 0;
	while ((str[++i] >= 9 && str[i] <= 13) || str[i] == 32)
		;
	if ((str[i] == 45 || str[i] == 43) && str[i + 1] != 0)
		if (str[i++] == 45)
			sign *= -1;
	while (str[i] >= 48 && str[i] <= 57)
		result = result * 10 + (str[i++] - 48);
	if (str[i])
		_exit_error(args, ": numeric argument required\n", str, NOT_NUMERIC);
	return (result % 256 * sign);
}

static inline int	_check_args(t_data *args, t_section *s_cmd)
{
	int	i_args;
	int	res;

	i_args = 1;
	res = EXIT_ERROR;
	while (s_cmd->path_cmd[i_args])
	{
		res = _numeric_args(args, s_cmd->path_cmd[i_args]);
		if (res != EXIT_ERROR && s_cmd->path_cmd[++i_args])
		{
			_exit_error(args, "too many arguments\n", NULL, TOO_MANY);
			return (EXIT_ERROR);
		}
	}
	if (i_args == 1)
	{
		args->exit_status = 0;
		res = 0;
	}
	if (res != EXIT_ERROR)
		args->exit_status = res;
	return (res);
}

void	_bi_exit(t_data *args, t_section *s_cmd)
{
	if (_check_args(args, s_cmd) == EXIT_ERROR)
		return ;
	if (args->count < 2)
		if (write(2, "exit\n", 6) == -1)
			_exit_failure(args);
	if (args->pid)
		free (args->pid);
	if (args->head)
		_lstfree(args->head, SECTION_LST);
	if (args->path_history)
		free (args->path_history);
	if (args->env)
		_freetab(args->env);
	if (args->env_history)
		_freetab(args->env_history);
	exit (args->exit_status);
}
