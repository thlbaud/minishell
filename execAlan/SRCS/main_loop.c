/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:27:07 by thibaud           #+#    #+#             */
/*   Updated: 2024/05/24 16:23:40 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "../HDRS/parsing.h"
#include "../HDRS/execution.h"
#include "../HDRS/structure.h"
#include "../include/libft/libft.h"

static void	_exec_nofork(t_data *args)
{
	int	temp_stdin;
	int	temp_stdout;
	
	args->count = 1;
	temp_stdin = dup(0);
	temp_stdout = dup(1);
	if (temp_stdin == -1 || temp_stdout == -1)
		_exit_failure(args);
	close (temp_stdin);
	close (temp_stdout);
	if (_fd_handler(args, args->head, 0) == 1)
		args->head->function_ptr(args, args->head);
	if (args->head->file)
	{
		dup2(temp_stdin, 0);
		dup2(temp_stdout, 1);
	}
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
	int	wstatus[2];

	wstatus[0] = 0;
	wstatus[1] = 0;
	args->count = _how_many_cmd(args->head);
	args->pid = malloc(sizeof(pid_t) * args->count);
	if (!args->pid)
		exit (EXIT_FAILURE);
	fork_n_exec(args, args->head);
	_close_pipe(args);
	i = 0;
	while (i != -1 || errno == EINTR)
	{
		i = waitpid(0, &wstatus[0], 0);
		if (i == args->pid[args->count - 1])
			wstatus[1] = wstatus[0];
	}
	args->exit_status = WEXITSTATUS(wstatus[1]);
	if (WIFSIGNALED(wstatus[1]) && WTERMSIG(wstatus[1]) == 3)
	{
		if (write(2, "Quit (core dumped)\n", 18) == -1)
			_exit_failure(args);
		args->exit_status = 131;
	}
}

static char	*_pwd_looper(t_data *args)
{
	char	*pwd;

	pwd = ft_strdup(_getenv(args->env, "PWD"));
	if (pwd)
		return (pwd);
	pwd = _define_cwd();
	if (!pwd && errno != ENOENT && errno != EACCES)
		_exit_failure(args);
	if (!pwd)
		pwd = _get_str(args, ".");
	return (pwd);
}

void	_looper(t_data *args)
{
	char	*pwd;
	char	*line;

	args->pid = NULL;
	args->pipe = NULL;
	pwd = _pwd_looper(args);
	if (!pwd)
		_exit_failure(args);
	line = prompt(pwd, args);
	parsing(line, args->env, args);
	if (!args->head)
		return ;
	if (!args->head->next && _is_a_buildin(args->head) == 1)
		_exec_nofork(args);
	else
		_execution(args);
	_lstfree(args->head, SECTION_LST);
	if (args->pid)
		free (args->pid);
	args->head = NULL;
}