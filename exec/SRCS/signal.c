/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:07:34 by avaldin           #+#    #+#             */
/*   Updated: 2024/04/17 18:12:13 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "../HDRS/parsing.h"

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		printf("\n");
		rl_redisplay();
	}
}

void	sig_int(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_sig;
	sigaction(SIGINT, &sa, NULL);
}

void	sig_quit(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
