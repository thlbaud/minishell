/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_data_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:46:30 by avaldin           #+#    #+#             */
/*   Updated: 2024/04/17 18:11:47 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../HDRS/parsing.h"

void	ft_redclear(t_file *lst)
{
	int	i;

	i = -1;
	if (lst)
	{
		ft_redclear(lst->next);
		if (lst->name)
		{
			free(lst->name[0]);
			if (lst->name[1])
				free(lst->name[1]);
			free(lst->name);
		}
		if (lst->protection)
			free(lst->protection);
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
		//printf("lst = %p, lst->pipe = %s, lst->next = %p\n", lst, lst->pipe, lst->next);
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