/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:53:12 by avaldin           #+#    #+#             */
/*   Updated: 2024/04/16 16:50:34 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	bad_var(t_section *sect)
{
	int	i;

	i = 0;
	while (sect->pipe[i])
	{
		if (sect->pipe[i] == '"' || sect->pipe[i] == 39)
			i += skip_quote(&sect->pipe[i]) + 2;
		else if (sect->pipe[i] == '$' && (sect->pipe[i + 1] == '"'
				|| sect->pipe[i + 1] == 39))
			sect->pipe = str_cut(sect->pipe, i, i);
		else
			i++;
	}
}

void	cmd_process_var(t_section *sect, char **env)
{
	int	i;

	i = 0;
	bad_var(sect);
	while (sect->pipe[i])
	{
		if (sect->pipe[i] == 39)
			i += skip_quote(&sect->pipe[i]) + 2;
		if (sect->pipe[i] == '$')
			sect->pipe = apply_var(sect->pipe, env, &i);
		else
			i++;
	}
}

void	command(t_section *first, char **env)
{
	t_section	*sect;

	sect = first;
	while (sect)
	{
		cmd_process_var(sect, env);
		cleaning_cmd(sect, sect->pipe);
		sect = sect->next;
	}
}
