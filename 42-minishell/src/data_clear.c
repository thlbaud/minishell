/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:46:30 by avaldin           #+#    #+#             */
/*   Updated: 2024/04/17 14:41:42 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_redclear(t_red *lst)
{
	int	i;

	i = -1;
	if (lst)
	{
		ft_redclear(lst->next);
		if (lst->file && *lst->file)
		{
			free(lst->file[0]);
			if (lst->file[1])
				free(lst->file[1]);
			free(lst->file);
			lst->file = NULL;
		}
		if (lst->protection)
		{
			free(lst->protection);
			lst->protection = NULL;
		}
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
		ft_redclear(lst->first_red);
		if (lst->cmd)
			cmd_clear(lst->cmd);
		if (lst->pipe)
			free(lst->pipe);
		free(lst);
		lst = NULL;
	}
}

void	clean_exit(t_data *data)
{
	if (data->first)
		ft_sectclear(data->first);
	free(data);
	exit(66);
}