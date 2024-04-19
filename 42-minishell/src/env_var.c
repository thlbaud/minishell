/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:20:59 by avaldin           #+#    #+#             */
/*   Updated: 2024/04/16 17:47:26 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ambigous_var(t_red *red, char **env, int i, int j)
{
	char	*var;
	int		len;

	len = 0;
	while ((red->temp[i][j + len + 1] < 91 && red->temp[i][j + len + 1] > 64)
		|| (red->temp[i][j + len + 1] < 123 && red->temp[i][j + len + 1] > 96)
		|| (red->temp[i][j + len + 1] < 58 && red->temp[i][j + len + 1] > 47))
		len++;
	var = find_var(&red->temp[i][j + 1], env, len);
	if (!var)
		return (0);
	i = 0;
	j = 0;
	while (var[i] && var[i] != ' ')
		i++;
	if (var[i] == ' ')
	{
		while (j < red->tmp_len)
			free(red->temp[j++]);
		free(red->temp);
		red->temp = NULL;
		return (1);
	}
	return (0);
}

char	*find_var(char *name, char **env, int len)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(name, env[i], len))
		i++;
	if (!env[i] || !env[i][len + 1])
		return (NULL);
	return (ft_strdup(env[i], len + 1, -1));
}

char	*apply_var(char *token, char **env, int *i)
{
	char	*var;
	int		len_name;

	len_name = 0;
	while ((token[*i + len_name + 1] < 91 && token[*i + len_name + 1] > 64)
		|| (token[*i + len_name + 1] < 123 && token[*i + len_name + 1] > 96)
		|| (token[*i + len_name + 1] < 58 && token[*i + len_name + 1] > 47))
		len_name++;
	if (token[*i + 1] <= '9' && token[*i + 1] >= '0')
		len_name = 1;
	if (!len_name)
		return ((*i)++, token);
	var = find_var(&token[*i + 1], env, len_name);
	if (!var)
		return (str_cut(token, *i, *i + len_name));
	*i += ft_strlen(var);
	token = str_modify(token, *i - ft_strlen(var), len_name + 1, var);
	return (token);
}

void	check_var(t_red *red, char **env, int i)
{
	int		j;

	j = 0;
	while (red->temp && red->temp[i] && red->temp[i][j])
	{
		if (red->temp[i][j] == '$')
		{
			if (!red->temp[i][j + 1] && red->protection[i + 1] != 0
				&& red->protection[i] == 0)
				red->temp[i] = str_cut(red->temp[i], j, j + 1);
			else if (ambigous_var(red, env, i, j))
				return ;
			else
				red->temp[i] = apply_var(red->temp[i], env, &j);
		}
		else
			j++;
	}
}

void	red_process_var(t_section *first, char **env)
{
	t_section	*sect;
	t_red		*red;
	int			i;

	sect = first;
	while (sect)
	{
		red = sect->first_red;
		while (red)
		{
			i = -1;
			while (red->temp && red->temp[++i])
				if (red->protection[i] != 2)
					check_var(red, env, i);
			red = red->next;
		}
		sect = sect->next;
	}
}
