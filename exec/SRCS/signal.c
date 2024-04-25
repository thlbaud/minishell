/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:07:34 by avaldin           #+#    #+#             */
/*   Updated: 2024/04/24 12:41:14 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "../HDRS/parsing.h"

static void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = c;
		i++;
	}
	return (s);
}

void	handle_sig_b(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 2);
		rl_redisplay();
	}
}

void	handle_sig_a(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		printf("\n");
		rl_redisplay();
	}
}

void	sig_int(int mode)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	if (!mode)
		sa.sa_handler = &handle_sig_a;
	else
		sa.sa_handler = &handle_sig_b;
	sigaction(SIGINT, &sa, NULL);
}

void	sig_quit(int mode)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	if (!mode)
		sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
