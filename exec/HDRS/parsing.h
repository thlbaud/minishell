/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:03:40 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/24 20:08:36 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
#include "structure.h"
#include <stdlib.h>

t_section	*parsing(char *line);
t_section	*ft_sectadd_back(t_section *lst, t_section *new);
t_file		*ft_redadd_back(t_file *lst, t_file *new);
int			skip_quote(char *line);
char 		*str_cut(char *line, int start, int end);
int 		write_quote(char *line, char *dest);
char		*pars_red(char *line, t_section *sect);
void		ft_sectclear(t_section *lst);
void		ft_redclear(t_file *lst);
void		cleaning_cmd(t_section *sect, char *line);

#endif