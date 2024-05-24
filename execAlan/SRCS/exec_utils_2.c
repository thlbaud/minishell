/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:32:03 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/23 20:13:44 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../HDRS/parsing.h"
#include "../include/libft/libft.h"

inline int	_size_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return (i);
	while (map[i])
		++i;
	return (i);
}

static char	*apply_var_heredoc(char *token, char **env, int *i, t_data *args)
{
	char	*var;
	int		len_name;

	len_name = 0;
	if (token[*i + 1] == '?')
		return (str_modify(token, *i, 2, ft_itoa(args->exit_status)));
	while (((token[*i + len_name + 1] < 91 && token[*i + len_name + 1] > 64)
		   || (token[*i + len_name + 1] < 123 && token[*i + len_name + 1] > 96)
		   || (token[*i + len_name + 1] < 58 && token[*i + len_name + 1] > 47))
			&& token[*i + len_name + 1] != '"' && token[*i + len_name + 1] != 39)
		len_name++;
	if (!len_name)
		return ((*i)++, token);
	var = find_var(&token[*i + 1], env, len_name);
	if (!var)
		return (str_cut(token, *i, *i + len_name));
	*i += ft_strlen(var, 0);
	token = str_modify(token, *i - ft_strlen(var, 0), len_name + 1, var);
	return (token);
}

char	*_pars_heredoc(t_data *args, t_file *file, char *line)
{
	int		i;

	i = 0;
	while (file && !file->heredoc_protec && line[i])
	{
		if (line[i] == '$')
			line = apply_var_heredoc(line, args->env, &i, args);
		else
			i++;
	}
	return (line);
}
