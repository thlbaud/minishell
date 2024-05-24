/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:38:50 by thibaud           #+#    #+#             */
/*   Updated: 2024/05/24 16:47:14 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "../HDRS/execution.h"
#include "../HDRS/structure.h"
#include "../include/libft/libft.h"

static inline void	_add_history(t_data *args, char *line)
{
	int	fd;

	if (!line || !line[0])
		return ;
	add_history(line);
	fd = open(args->path_history, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		_exit_failure(args);
	if (write(fd, line, ft_strlen(line, 0)) == -1
		|| write(fd, "\n", 1) == -1)
	{
		close (fd);
		_exit_failure(args);
	}
	close (fd);
}

static inline void	_line_error(t_data *args)
{
	rl_clear_history();
	free (args->pid);
	free (args->path_history);
	_freetab(args->env);
	if (write (2, "exit\n", 6) == -1)
		_exit_failure(args);
	exit (24);
}

char	*prompt(char *pwd, t_data *args)
{
	char	*temp;
	char	*line;

	sig_int(0);
	sig_quit(0);
	if (g_sig)
		args->exit_status = g_sig;
	g_sig = 0;
	temp = ft_strjoin (pwd, "$ ");
	if (!temp)
		_exit_failure(args);
	free (pwd);
	line = readline(temp);
	sig_int(1);
	free (temp);
	if (!line)
		_line_error(args);
	if (line[0])
		_add_history(args, line);
	return (line);
}