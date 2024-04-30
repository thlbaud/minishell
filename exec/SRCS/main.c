/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:35:44 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/30 20:01:44 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "../HDRS/parsing.h"
#include "../HDRS/structure.h"
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

int	g_err;

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

static inline int	_get_path_history(t_data *args)
{
	char	*temp;
	char	*path;
	int		i;

	temp = _define_cwd();
	if (!temp)
		return (-1);
	i = 2;
	i += ft_strlen(&temp[i], '/');
	++i;
	i += ft_strlen(&temp[i], '/');
	++i;
	path = ft_calloc(sizeof(char), i + 1);
	if (!path)
		return (free (temp), -1);
	ft_strlcpy(path, temp, ++i);
	if (!path)
		return (-1);
	free (temp);
	args->path_history = ft_strjoin(path, ".minishell-history");
	free (path);
	if (!args->path_history)
		return (-1);
	return (0);
}

static inline int	_how_many_cmd(t_section *cmd)
{
	t_section	*temp;
	int			counter;

	temp = cmd;
	counter = 0;
	while (temp)
	{
		temp = temp->next;
		++counter;
	}
	return (counter);
}

static inline void	_execution(t_data *args)
{
	int	i;
	int wstatus;

	wstatus = 0;
	args->count = _how_many_cmd(args->head);	
	args->pid = malloc(sizeof(pid_t) * args->count);
	if (!args->pid)
		exit (EXIT_FAILURE);
	fork_n_exec(args, args->head);
	_close_pipe(args);
	i = -1;
	while (++i < args->count)
		waitpid(args->pid[i], &wstatus, 0);
	if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus))
	{
		if (write(2, "Quit (core         dumped)\n", 28) == -1)
			_exit_failure(args);
	}
	if (args->pid)
		free (args->pid);
	args->pid = NULL;
}

static inline char	*prompt(char *pwd, t_data *args)
{
	char	*temp;
	char	*line;

	sig_int(0);
	sig_quit(0);
	temp = ft_strjoin (pwd, "$ ");
	free (pwd);
	line = readline(temp);
	sig_int(1);
	free (temp);
	if (!line)
	{
		rl_clear_history();
		free (args->pid);
		free (args->path_history);
		_freetab(args->env);
		if (write (2, "exit\n", 6) == -1)
			_exit_failure(args);
		exit (24);
	}
	if (line[0])
		_add_history(args, line);
	return (line);
}

void	_looper(t_data *args)
{
	char				*pwd;
	char				*line;
	
	args->pid = NULL;
	pwd = _define_cwd();
	if (!pwd)
		_exit_failure(args);
	line = prompt(pwd, args);
	parsing(line, args->env, args);
	if (!args->head)
		return ;
	if (!args->head->next && _is_a_buildin(args->head) == 1)
	{
		if (_fd_handler(args, args->head, 0) == 1)
			args->head->function_ptr(args, args->head);
	}
	else
		_execution(args);
	if (args->pid)
		free (args->pid);
	if (args->head)
		_lstfree(args->head, SECTION_LST);
}

int	main(int argc, char **argv, char **env)
{
	t_data	args;
	
	(void)argc;
	(void)argv;
	g_err = 0;
	args.pipe = NULL;
	args.env = _map_cpy(env);
	if (!args.env)
		return (-1);
	if (_get_path_history(&args) == -1)
		return (-1);
	while (42)
		_looper(&args);
	return (0);
}
 