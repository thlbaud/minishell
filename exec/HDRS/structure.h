/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:55:51 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/21 05:11:44 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	STRUCTURE_H
# define STRUCTURE_H
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>

typedef struct s_index
{
	int					i;
	struct s_index		*next;	
}				t_index;

typedef struct s_file
{
	int					redirect;
	int					tmp_len;
	int					*protection;
	char				**name;
	char				**temp;
	struct s_file		*next;

}				t_file;

typedef struct	s_section
{
	char 				**path_cmd;
	char				*pipe;
	t_file				*file;
	struct s_data		*data;
	struct s_section	*prev;
	struct s_section	*next;
}				t_section;

typedef struct s_data
{
	int					pipe[2];
	int					pipe_sec[2];
	char				**env;
	pid_t				*pid;
	t_section			*head;
	struct sigaction	*sa;
	
}				t_data;

typedef enum 
{
	INDEX_LST,
	FILE_LST, 
	SECTION_LST 
} 				e_type;

void	sig_int(void);
void	sig_quit(void);
void	handle_sig(int sig);
void	_looper(t_data *args);

#endif