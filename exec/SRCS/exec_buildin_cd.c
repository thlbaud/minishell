/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:37:51 by thibaud           #+#    #+#             */
/*   Updated: 2024/04/21 22:52:32 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

void	_cd_old_pwd(t_data *args, char *old_pwd)
{
	t_section	temp;
	char		*cmd[3];
	char		*name_cmd;

	temp.next = NULL;
	temp.prev = NULL;
	temp.file = NULL;
	name_cmd = "EXPORT";
	cmd[0] = name_cmd;
	cmd[1] = ft_strjoin("OLDPWD=", old_pwd);
	cmd[2] = NULL;
	if (!cmd[1])
		_error_exit(args, NULL, 1);
	temp.path_cmd = cmd;
	_bi_export(args, &temp, NULL, NULL);
	free (cmd[1]);
}

void	_bi_cd(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr)
{
	
	char	*old_pwd;
	int		fd_f[2];

	fd_f[0] = 0;
	fd_f[1] = 1;
	if (s_cmd->file)
		_open_file(args, s_cmd->file, fd_f);
	_pipe_closer(fd_pr, fd_pw, fd_f);
	if (!s_cmd->path_cmd[1])
		return ;
	old_pwd = _define_cwd();
	if (!old_pwd)
		_error_exit(args, NULL, 1);
	if (chdir(s_cmd->path_cmd[1]) == -1)
		perror(ft_strjoin("bash: ", s_cmd->path_cmd[0]));
	else
		_cd_old_pwd(args, old_pwd);
}
