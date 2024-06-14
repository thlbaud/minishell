/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:06:42 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/24 18:01:22 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# include <stdlib.h>
# include <unistd.h>

size_t	gnl_strlen(const char *s);
size_t	gnl_strchr(const char *s, size_t size);
char	*ft_reset_buff(char	*buff);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_calloc(size_t nmemb, size_t size);

char	*get_next_line(int fd);

#endif
