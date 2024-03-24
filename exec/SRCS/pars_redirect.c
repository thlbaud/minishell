/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:01:56 by avaldin           #+#    #+#             */
/*   Updated: 2024/03/24 20:09:14 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/parsing.h"
#include "../include/libft/libft.h"

int red_count(char *line)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '>' || line[i] == '<')
		{
			if (line[i] == line[i + 1])
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

int	red_length(char *line)
{
	int len;
	int i;

	len = 0;
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '	'))
		i++;
	while (line[i] && !(line[i] == ' ' || line[i] == '	' || line[i] == '<' || line[i] == '>' || line[i] == '|'))
	{
		if (line[i] == '"' || line[i] == 39)
		{
			len += skip_quote(&line[i]);
			i += skip_quote(&line[i]) + 1;
		}
		else
			len++;
		i++;
	}
	return (len);
}

int	red_fill(char *line, char *redirect)
{
	int i;
	int i_red;

	i_red = 0;
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '	'))
		i++;
	while (line[i] && !(line[i] == ' ' || line[i] == '	' || line[i] == '<' || line[i] == '>' || line[i] == '|'))
	{
		if (line[i] == '"' || line[i] == 39)
		{
			i_red += write_quote(&line[i], &redirect[i_red]);
			i += skip_quote(&line[i]) + 1;
		}
		else
			redirect[i_red++] = line[i];
		i++;
	}
	redirect[i_red] = '\0';
	return (i);
}

int redirect(t_file *red, char *line)
{
	char	*redirect;
	int		red_count;
	int		i;

	red_count = 1;
	if (line[0] == line[1])
		red_count = 2;
	redirect = ft_calloc(red_length(&line[red_count]) + 1, sizeof(char));
	if (!redirect)
		exit(4); // pas ok
	if (line[0] == '<')
		red->redirect = -1 * red_count;
	else
		red->redirect = red_count;
	i = red_fill(&line[red_count], redirect) + red_count - 1;
	red->name = redirect;
	return(i);
}

char	*pars_red(char *line, t_section *sect)
{
	int 	i;
	t_file	*red;
	t_file	*first_red;

	i = 0;
	first_red = NULL;
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '"' || line[i] == 39)
			i += skip_quote(&line[i]) + 2;
		else if (line[i] == '<' || line[i] == '>')
		{
			red = ft_calloc(1, sizeof(t_file));
			line = str_cut(line, i, i + redirect(red, &line[i]));
			i = 0;
			first_red = ft_redadd_back(first_red, red);
		}
		else
			i++;
	}
	sect->file = first_red;
	return (line);
}