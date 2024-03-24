/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_data_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:46:30 by avaldin           #+#    #+#             */
/*   Updated: 2024/03/24 19:52:22 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/parsing.h"

void	ft_redclear(t_file *lst)
{
	if (lst)
	{
		ft_redclear(lst->next);
		free(lst->name);
		free(lst);
		lst = NULL;
	}
}

void	cmd_clear(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void	ft_sectclear(t_section *lst)
{
	if (lst)
	{
		ft_sectclear(lst->next);
		ft_redclear(lst->file);
		cmd_clear(lst->path_cmd);
		free(lst);
		lst = NULL;
	}
}