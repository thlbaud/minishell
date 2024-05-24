/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:06:42 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/24 15:27:00 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>

char	*ft_reset_buff(char	*buff);
char	*get_next_line(int fd);
size_t	gnl_strlen(const char *s);
size_t	gnl_strchr(const char *s, size_t size);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_calloc(size_t nmemb, size_t size);

#endif
