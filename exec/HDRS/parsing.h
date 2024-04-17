/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:03:40 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/17 17:46:30 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
#include "structure.h"
#include <stdlib.h>

void		ft_redclear(t_file *lst);
void		ft_sectclear(t_section *lst);
t_section	*ft_sectadd_back(t_section *lst, t_section *new);
t_section	*ft_sectadd_back(t_section *lst, t_section *new);

void		red_union(t_section *sect);
void		red_process_var(t_section *first, char **env);

int			skip_quote(char *line);
int 		write_quote(char *line, char *dest);

void		cleaning_cmd(t_section *sect, char *line);
char		*apply_var(char *token, char **env, int *i);
void	    red_quote_expender(t_section *sect);
void	    redirection(t_data *data, char **env);
void		command(t_section *first, char **env);

int			checking(char *line);
int			red_syntax(char *line);
char		*str_cut(char *line, int start, int end);
char		*pars_red(char *line, t_section *sect);
void		cleaning_cmd(t_section *sect, char *line);

void		clean_exit(t_data *data);

void		parsing(char *line, char **env, t_data *data);

#endif