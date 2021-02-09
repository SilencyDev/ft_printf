/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:52:26 by kmacquet          #+#    #+#             */
/*   Updated: 2021/02/09 16:45:01 by kmacquet         ###   ########.fr       */
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
		ft_putchar(*str++);
}

int		ft_strlen(const char *s)
{
	int n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}

void			ft_putnbr(long long nb, char *base, int baselen)
{
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb == baselen)
	{
		ft_putchar(base[1]);
	}
	if (nb > baselen)
		ft_putnbr((nb / baselen), base, baselen);
	ft_putchar(base[nb % baselen]);
}

void			ft_putnbr_base(long long nbr, char *base)
{
	int			baselen;

	baselen = ft_strlen(base);
	ft_putnbr(nbr, base, baselen);
}

void			ft_putptr_base(long long nbr, char *base)
{
	if (!nbr)
		ft_putstr("(NULL)");
	ft_putstr("0x");
	ft_putnbr_base(nbr, base);
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

int	find_converter(char str, char *charset)
{
	size_t k;

	k = 0;
	while (charset[k])
		if (str == charset[k++])
			return (charset[--k]);
	return (0);
}

t_option			*analyze_format(char *toformat)
{
	char			tmp;
	size_t			i;
	t_option		*option;

	option = ft_init_option();
	i = 0;
	while (!find_converter(toformat[i], "cspdiuxX") && toformat[i])
	{
		if ((tmp = find_converter(toformat[i], "-0.*") != 0))
		{
			option->flag_minus = tmp == '-' ? 1 : 0;
			option->flag_zero = tmp == '0' ? 1 : 0;
			option->dot = tmp == '.' ? 1 : 0;
			option->flag_pre_va = tmp == '*' ? 1 : 0;
		}
		i++;
	}
	if (find_converter(toformat[i], "cspdiuxX") != 0)
		option->type = find_converter(toformat[i], "cspdiuxX");
	return (option);
}

size_t	len_filter(char *toformat)
{
	size_t j;

	j = 0;
	while (!find_converter(toformat[j], "cspdiuxX") && *toformat)
		j++;
	if (find_converter(toformat[j], "cspdiuxX"))
		j++;
	return (j);
}

void	convert_type_format(t_option *option, va_list args)
{
	if (option->type == 'c')
		ft_putchar(va_arg(args, int));
	if (option->type == 's')
		ft_putstr(va_arg(args, char*));
	if (option->type == 'p')
		ft_putptr_base(va_arg(args, unsigned long int), "0123456789abcdef");
	if (option->type == 'd' || option->type == 'i')
		ft_putnbr_base(va_arg(args, int), "0123456789");
	if (option->type == 'u')
		ft_putnbr_base(va_arg(args, unsigned int), "0123456789");
	if (option->type == 'x')
		ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef");
	if (option->type == 'X')
		ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF");
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
			convert_type_format(option, args);
			free(option);
			toformat = toformat + i;
		}
		else
		{
			ft_putchar(*toformat++);
			count++;
		}
	}
	va_end(args);
	return (count);
}

int	main(void)
{
	char str[2] = {"he"};
	ft_printf("Hello mr %c %s %p %d %i %x %X %u\n", 'h', "hello", str, +56, -213, 526, -527, -78);
	printf("Hello mr %c %s %p %d %i %x %X %u\n", 'h', "hello", str, +56, -213, 526, -527, -78);
}
