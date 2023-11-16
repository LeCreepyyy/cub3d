/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:05:14 by vpoirot           #+#    #+#             */
/*   Updated: 2023/11/16 14:05:30 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

void	ft_putstr(char *str, int *size)
{
	int	i;

	i = -1;
	if (!str)
	{
		*size += write(1, "(null)", 6);
		return ;
	}
	while (str[++i])
		*size += write(1, &str[i], 1);
}

void	ft_putnbr(int value, int *size)
{
	char	c;

	if (value == -2147483648)
	{
		*size += write(1, "-2147483648", 11);
		return ;
	}
	if (value < 0)
	{
		*size += write(1, "-", 1);
		value = -value;
	}
	if (value > 9)
		ft_putnbr(value / 10, size);
	c = value % 10 + '0';
	*size += write(1, &c, 1);
}

void	ft_puthexa(unsigned int value, int *size)
{
	char	c;

	if (value > 15)
		ft_puthexa(value / 16, size);
	c = "0123456789abcdef"[value % 16];
	*size += write(1, &c, 1);
}

void	transform_arg(char c, va_list args, int *size)
{
	if (c == 's')
		ft_putstr(va_arg(args, char *), size);
	if (c == 'd')
		ft_putnbr(va_arg(args, int), size);
	if (c == 'x')
		ft_puthexa(va_arg(args, unsigned int), size);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		size;
	va_list	args;

	i = 0;
	size = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
			transform_arg(str[++i], args, &size);
		else
			size += write(1, &str[i], 1);
		i++;
	}
	va_end(args);
	return (size);
}
