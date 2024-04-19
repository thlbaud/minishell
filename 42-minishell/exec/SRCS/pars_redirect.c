/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:01:56 by avaldin           #+#    #+#             */
/*   Updated: 2024/04/19 14:11:10 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/parsing.h"
#include "../include/libft/libft.h"

static int	red_length(char *line)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '	'))
		i++;
	while (line[i] && !(line[i] == ' ' || line[i] == '	' || line[i] == '<'
			|| line[i] == '>'))
	{
		if (line[i] == '"' || line[i] == 39)
		{
			len += skip_quote(&line[i]) + 1;
			i += skip_quote(&line[i]) + 1;
		}
		len++;
		i++;
	}
	return (len);
}

static int	extract_red(t_file *red, char *line, t_data *data)
{
	int		red_count;
	int		i;

	red_count = 1;
	if (line[0] == line[1])
		red_count = 2;
	if (line[0] == '<')
		red->redirect = -1 * red_count;
	else
		red->redirect = red_count;
	i = red_count;
	while (line[i] && (line[i] == ' ' || line[i] == '	'))
		i++;
	red->name[0] = _strdup(line, i, red_length(&line[red_count]));
		if (!red->name[0])
			clean_exit(data);
	return (i + red_length(&line[red_count]));
}

static void	create_red(t_section *sect)
{
	int		i;
	t_file	*red;

	i = 0;
	sect->file = NULL;
	while (sect->pipe && sect->pipe[i])
	{
		if (sect->pipe[i] == '"' || sect->pipe[i] == 39)
			i += skip_quote(&sect->pipe[i]) + 2;
		else if (sect->pipe[i] == '<' || sect->pipe[i] == '>')
		{
			red = ft_calloc(1, sizeof(t_file));
			if (!red)
				clean_exit(sect->data);
			red->name = ft_calloc(3, sizeof(char *));
			if (!red->name)
				clean_exit(sect->data);
			sect->pipe = str_cut(sect->pipe, i, i + extract_red(red, &sect->pipe[i], sect->data) - 1);
			i = 0;
			sect->file = ft_redadd_back(sect->file, red);
		}
		else
			i++;
	}
}

void	redirection(t_data *data, char **env)
{
	t_section	*sect;

	sect = data->head;
	while (sect)
	{
		create_red(sect);
		red_quote_expender(sect);
		red_process_var(sect, env);
		red_union(sect);
		sect = sect->next;
	}
}

/*int red_count(char *line)
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
}*/