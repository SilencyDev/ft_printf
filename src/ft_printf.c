/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:52:26 by kmacquet          #+#    #+#             */
/*   Updated: 2021/02/17 12:09:10 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	This globale is used to simplify the workflow and reduce the number
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

int				ft_printf(const char *format, ...)
{
	char		*toformat;
	t_option	*o;
	va_list		args;

	if (!(o = malloc(sizeof(t_option))))
		return (-1);
	g_count = 0;
	toformat = (char *)format;
	va_start(args, format);
	while (*toformat)
	{
		if (*toformat == '%')
		{
			toformat++;
			o = analyze_format(toformat, args, ft_init_option(o));
			convert_type_format(o, args);
			toformat = toformat + len_filter(toformat) + 1;
		}
		else
			ft_putchar(*toformat++, 1);
	}
	free(o);
	va_end(args);
	return (g_count);
}
