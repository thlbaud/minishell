/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:03:40 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/17 14:41:55 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
#include "structure.h"
#include <stdlib.h>

// t_section	*parsing(char *line);
void		ft_redclear(t_file *lst);
void		ft_sectclear(t_section *lst);
t_section	*ft_sectadd_back(t_section *lst, t_section *new);
t_section	*ft_sectadd_back(t_section *lst, t_section *new);

int			skip_quote(char *line);
void	    red_quote_expender(t_section *sect);
void	    redirection(t_data *data, char **env);
char		*str_cut(char *line, int start, int end);
int 		write_quote(char *line, char *dest);
char		*pars_red(char *line, t_section *sect);
void		cleaning_cmd(t_section *sect, char *line);

void		parsing(char *line, char **env, t_data *data);

#endif