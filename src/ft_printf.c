/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:52:26 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/26 17:36:12 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	This global is used to simplify the workflow and reduce the number
**	of step needed to backup the count from putchar
*/
int	g_count;

int				ft_putchar(char c, int on)
{
	if (on != 0)
	{
		write(1, &c, 1);
		g_count++;
	}
	return (1);
}

int			ft_putstr(char *str, int prec, int on)
{
	int	i;

	i = 0;
	if (prec > 0)
		while (*str && str && i < prec)
			i += ft_putchar(*str++, on);
	else if (prec < 0)
		while (*str && str)
			i += ft_putchar(*str++, on);
	return (i);
}

void	padding(int i, char c)
{
	while (i-- > 0)
		ft_putchar(c, 1);
}

char		*set_base(char c)
{
	if (c == 'p' || c == 'x')
		return ("0123456789abcdef");
	else if (c == 'd' || c == 'i' || c == 'u')
		return ("0123456789");
	else if (c == 'X')
		return ("0123456789ABCDEF");
	return (0);
}

int				ft_printf(const char *format, ...)
{
	char		*toformat;
	t_option	o;
	va_list		args;

	g_count = 0;
	toformat = (char *)format;
	va_start(args, format);
	while (*toformat)
	{
		if (*toformat == '%')
		{
			toformat++;
			toformat = analyze_format(toformat, args, ft_init_option(&o));
			convert_type_format(&o, args);
		}
		else
			ft_putchar(*toformat++, 1);
	}
	va_end(args);
	return (g_count);
}
