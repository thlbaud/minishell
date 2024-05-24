/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_pwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:16:16 by thibaud           #+#    #+#             */
/*   Updated: 2024/05/23 23:37:21 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

void	_bi_pwd(t_data *args, t_section *s_cmd)
{
	int		res[2];
	char	*buff;

	if (s_cmd)
		s_cmd->fd_f[0] = s_cmd->fd_f[0];
	buff = _define_cwd();
	if (!buff && errno != ENOENT && errno != EACCES)
		_exit_failure(args);
	else if (!buff)
		buff = _get_str(args, "job-working-directory: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
	res[0] = write(1, buff, ft_strlen(buff, 0));
	if (res[0] != -1)
		res[1] = write(1, "\n", 1);
	_close_pipe(args);
	free (buff);
	if (res[0] == -1 || res[1] == -1)
		_exit_failure(args);
	args->exit_status = 0;
}
