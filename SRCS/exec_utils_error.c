/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 23:59:19 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/24 17:03:14 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

inline int	_write_cwd_error(void)
{
	write(2, "job-working-directory: error retrieving current directory:\
			getcwd: cannot access parent directories:\
			No such file or directory\n", 127);
	return (-1);
}

inline char	*_give_strerror_identifier(t_data *args, t_index *lst, char *str)
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

inline char	*_give_strerror_cmd(t_data *args, char *str)
{
	char	*res;
	char	*temp;

	temp = ft_strjoin("bash: ", str);
	if (!temp)
		_exit_failure(args);
	res = ft_strjoin(temp, ": command not found\n");
	free (temp);
	if (!res)
		_exit_failure(args);
	return (res);
}

inline char	*_give_strerror_dir(t_data *args, char *str)
{
	char	*res;
	char	*temp;

	temp = ft_strjoin("bash: ", str);
	if (!temp)
		_exit_failure(args);
	res = ft_strjoin(temp, ": Is a directory\n");
	free (temp);
	if (!res)
		_exit_failure(args);
	return (res);
}
