/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:55:05 by vpoirot           #+#    #+#             */
/*   Updated: 2023/03/27 11:08:03 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	len_str(const char *str)
{
	size_t	a;

	a = 0;
	if (!str)
		return (0);
	while (str[a] != '\0')
		a++;
	return (a);
}

int	findstop(char *stock)
{
	size_t	i;

	i = 0;
	if (!stock)
		return (1);
	while (stock[i])
	{
		if (stock[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	char	*table;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	table = (void *)malloc(nmemb * size);
	if (!table)
		return (0);
	i = 0;
	while (i < (nmemb * size))
	{
		table[i] = 0;
		i++;
	}
	return (table);
}

char	*ft_strjoin2(char const *s1, char const *s2, char *str)
{
	size_t	j;
	size_t	l;

	l = -1;
	j = -1;
	if (s1)
	{
		while (s1[++l] != '\0')
			str[l] = s1[l];
	}
	if (s2)
	{
		while (s2[++j] != '\0')
			str[l + j] = s2[j];
	}
	str[l + j] = '\0';
	free ((char *)s1);
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	lenstock;

	lenstock = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1[0] != '\0')
		lenstock = len_str(s1);
	str = ft_calloc(lenstock + len_str(s2) + 1, sizeof(char));
	if (!str)
	{
		free ((char *)s1);
		s1 = 0;
		return (0);
	}
	return (ft_strjoin2(s1, s2, str));
}
