/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:52:26 by kmacquet          #+#    #+#             */
/*   Updated: 2021/02/08 17:02:54 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str && str)
	{
		ft_putchar(*str++);
	}
}

t_option	*ft_init_option(void)
{
	t_option *option;

	if (!(option = malloc(sizeof(t_option))))
		return (NULL);
	option->flag_minus = 0;
	option->flag_zero = 0;
	option->width = 0;
	option->dot = 0;
	option->precision = -1;
	option->flag_pre_va = 0;
	option->num_n = 0;
	option->type = 0;
	return (option);
}

int	find_converter(char *str, char *charset)
{
	while (*charset)
		if (*str == *charset++)
			return (*charset);
	return (0);
}

t_option			*analyze_format(char *toformat)
{
	char			*formated;
	char			tmp;
	size_t			i;
	t_option		*option;

	option = ft_init_option();
	formated = toformat;
	i = 0;
	while (!find_converter(&formated[i], "cspdiuxX") && *formated)
	{
		if ((tmp = find_converter(&formated[i], "-0.*") != 0))
		{
			option->flag_minus = tmp == '-' ? 1 : 0;
			option->flag_zero = tmp == '0' ? 1 : 0;
			option->dot = tmp == '.' ? 1 : 0;
			option->flag_pre_va = tmp == '*' ? 1 : 0;
		}
		if (tmp = find_converter(&formated[i], "cspdiuxX"))
			option->type = tmp;
		i++;
	}
	return (option);
}

size_t	len_filter(char *toformat)
{
	size_t j;

	j = 0;
	while (!find_converter(&toformat[j], "cspdiuxX") && *toformat)
		j++;
	return (j);
}

int					ft_printf(const char *format, ...)
{
	static size_t	count;
	va_list			args;
	char			*toformat;
	size_t			i;
	t_option		*option;

	count = 0;
	toformat = (char *)format;
	va_start(args, format);
	while (*toformat)
	{
		if (*toformat == '%')
		{
			toformat++;
			option = analyze_format(toformat);
			i = len_filter(toformat);
			toformat = toformat + i;
		}
		else
		{
			ft_putchar(va_arg(args, int));
			toformat++;
			count++;
		}
	}
	va_end(args);
	return (count);
}

int	main(void)
{
	printf("Hello mr %c", 'h');
}
