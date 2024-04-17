/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:41:44 by avaldin           #+#    #+#             */
/*   Updated: 2024/04/17 10:09:40 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	null_red(t_red *red)
{
	int	i;

	i = 0;
	while (i < red->tmp_len)
	{
		if (red->temp[i] && red->temp[i][0])
			return (0);
		i++;
	}
	i = 0;
	while (i < red->tmp_len)
	{
		if (red->protection[i])
		{
			red->file[1] = ft_calloc(1, sizeof(char));
			return (1);
		}
		i++;
	}
	red->file[1] = NULL;
	return (1);
}

char	*temp_join(t_red *red)
{
	int		i;
	char	*file;

	i = 0;
	file = NULL;
	while (i < red->tmp_len && !file)
	{
		if (!red->temp[i] || !red->temp[i][0])
			i++;
		else
			file = ft_strdup(red->temp[i++], 0, -1);
	}
	while (i < red->tmp_len)
	{
		if (red->temp[i] && red->temp[i][0])
		{
			file = str_modify(file, (int) ft_strlen(file), 0,
						ft_strdup(red->temp[i], 0, -1));
		}
		i++;
	}
	return (file);
}

void	red_union(t_section *sect)
{
	t_red	*red;

	red = sect->first_red;
	while (red)
	{
		if (red->temp && !null_red(red))
		{
			red->file[1] = temp_join(red);
		}
		red = red->next;
	}
}
