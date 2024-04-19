/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_data_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:46:30 by avaldin           #+#    #+#             */
/*   Updated: 2024/04/19 14:25:35 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../HDRS/parsing.h"

void	ft_redclear(t_file *lst)
{
	int	i;

	if (lst)
	{
		ft_redclear(lst->next);
		if (lst->name)
		{
			if (lst->name[0])
			{
				free(lst->name[0]);
				lst->name[0] = NULL;
			}
			if (lst->name[1])
			{
				free(lst->name[1]);
				lst->name[1] = NULL;
			}
			free(lst->name);
			lst->name = NULL;
		}
		if (lst->protection)
		{
			free(lst->protection);
			lst->protection = NULL;
		}
		i = -1;
		while (++i < lst->tmp_len)
			if (lst->temp && lst->temp[i])
			{
				free(lst->temp[i]);
				lst->temp[i] = NULL;
			}
		free(lst->temp);
		lst->temp = NULL;
		free(lst);
		lst = NULL;
	}
}

void	cmd_clear(char **cmd)
{
	int	i;

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
		if (lst->next)
			ft_sectclear(lst->next);
		ft_redclear(lst->file);
		if (lst->path_cmd)
			cmd_clear(lst->path_cmd);
		if (lst->pipe)
			free(lst->pipe);
		free(lst);
		lst = NULL;
	}
}

void	clean_exit(t_data *data)
{
	if (data->head)
		ft_sectclear(data->head);
	free(data);
	exit(66);
}