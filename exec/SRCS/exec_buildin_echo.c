/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_echo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:49:44 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/27 14:35:00 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/execution.h"

void	_bi_echo(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr)
{
	int	fd_f[2];

	fd_f[0] = 0;
	fd_f[1] = 1;
	if (s_cmd->file)
		_open_file(args, s_cmd->file, fd_f);
	if (fd_f[0] != 0)
		if (write(fd_f[1] ))
	
}