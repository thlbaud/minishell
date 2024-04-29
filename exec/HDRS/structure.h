/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:55:51 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/29 07:26:07 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	STRUCTURE_H
# define STRUCTURE_H
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#define EXIT_ERROR 360

extern int	g_err;

typedef struct s_index
{
	int					i;
	struct s_index		*next;	
}				t_index;

typedef struct s_file
{
	int					tmp_len;
	int					redirect;
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
	struct s_data		*data; //sert a rien 
	struct s_section	*prev;
	struct s_section	*next;
}				t_section;

typedef struct s_data
{
	int					pipe[2];
	int					pipe_sec[2];
	char				*path_history;
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

typedef enum
{
	WRITE,
	AUTO	
}				e_write;

typedef enum
{
	ALL,
	PARTIAL	
}				e_from;

typedef enum
{
	TOO_MANY,
	NOT_NUMERIC
}				e_err;

typedef enum
{
	HOME,
	OLDPWD
}				e_cdenv;

void	sig_int(int mode);
void	sig_quit(int mode);

void	_looper(t_data *args);

void	_freetab(char **tab);
void	_lstfree(void *lst, e_type typelst);
void	_exit_failure(t_data *args);

#endif