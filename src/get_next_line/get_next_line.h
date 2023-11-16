/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:50:43 by vpoirot           #+#    #+#             */
/*   Updated: 2023/03/24 13:26:52 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
size_t	len_str(const char *str);
void	*add_malloc(size_t	size, char	*str);
char	*ft_strjoin(char const *s1, char const *s2);
int		size_count(const char *str);
char	*gnl_eof(char *stock);
void	*ft_calloc(size_t nmemb, size_t size);
int		findstop(char *stock);

#endif
