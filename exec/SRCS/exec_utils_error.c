/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 23:59:19 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/15 00:08:43 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"


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
