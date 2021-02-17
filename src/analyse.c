/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:22:05 by kmacquet          #+#    #+#             */
/*   Updated: 2021/02/17 12:39:25 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			find_converter(char str, char *charset)
{
	size_t	k;

	k = 0;
	while (charset[k])
	{
		if (str == charset[k])
			return (charset[k]);
		k++;
	}
	return (0);
}

void		analyze_flags(char *s, va_list args, t_option *o)
{
	int		tmp;

	if (*s == '-')
	{
		o = ft_init_option(o);
		o->flag_minus = 1;
	}
	else if (*s == '.')
		o->dot = 0;
	else if (*s == '0' && (*(s - 1) < '0' || *(s - 1) > '9'))
		o->flag_zero = 1;
	else if (*s == '*')
	{
		tmp = va_arg(args, int);
		if (*(s - 1) != '.')
		{
			if (o->width < 0)
			{
				o = ft_init_option(o);
				o->flag_minus = 1;
			}
			o->width = tmp;
		}
		if (*(s - 1) == '.')
			o->dot = tmp;
	}
}

t_option	*analyze_format(char *toformat, va_list args, t_option *o)
{
	size_t	i;

	i = 0;
	while (find_converter(toformat[i], "0123456789.-*") && toformat[i])
	{
		if ((find_converter(toformat[i], "0-.*")) != 0)
			analyze_flags(&toformat[i], args, o);
		if (find_converter(toformat[i], "123456789"))
		{
			if (toformat[i - 1] == '.')
			{
				o->dot = ft_atoi(&toformat[i]);
				i = i + ft_intlen(o->dot) - 1;
			}
			else if (toformat[i - 1] != '.')
			{
				o->width = ft_atoi(&toformat[i]);
				i = i + ft_intlen(o->width) - 1;
			}
		}
		i++;
	}
	o->type = toformat[i];
	return (o);
}

void		convert_type_format(t_option *o, va_list args)
{
	int	i;

	i = 0;
	if (o->width < 0)
	{
		o->flag_minus = 1;
		o->width = -o->width;
	}
	if (o->type == 's')
		convert_s(va_arg(args, char*), o, i);
	else if (o->type == 'p')
		convert_p(va_arg(args, long long), o, i);
	else if (o->type == 'd' || o->type == 'i')
		convert_di(va_arg(args, int), o, i);
	else if (o->type == 'X' || o->type == 'x' || o->type == 'u')
		convert_uxx(va_arg(args, unsigned int), o, i);
	else
		convert_c_other(args, o);
}
