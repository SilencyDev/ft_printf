/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:52:26 by kmacquet          #+#    #+#             */
/*   Updated: 2021/02/13 15:17:30 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c, int on)
{
	if (on != 0)
		write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str, int prec, int on)
{
	int	i;

	i = 0;
	if (prec != 0)
		while (*str && str && i < prec)
			i += ft_putchar(*str++, on);
	else if (prec == 0)
		while (*str && str)
			i += ft_putchar(*str++, on);
	return (i);
}

int		ft_strlen(const char *s)
{
	int n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}

int				ft_intlen(long int n)
{
	int			len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

long int		ft_noneg(long int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char		*ft_itoa(int n)
{
	char	*dst;
	int		len;
	int		neg;

	len = ft_intlen(n);
	neg = (n < 0) ? -1 : 1;
	if (!(dst = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	dst[len--] = '\0';
	while (len >= 0)
	{
		dst[len] = '0' + ft_noneg(n % 10);
		n = ft_noneg(n / 10);
		len--;
	}
	if (neg == -1)
		dst[0] = '-';
	return (dst);
}


int					ft_atoi(const char *str)
{
	unsigned int	i;
	int				posneg;
	int				result;

	i = 0;
	result = 0;
	posneg = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			posneg = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * posneg);
}

int			ft_putnbr(long long nb, char *base, int baselen, int on)
{
	static int	i;

	i = 0;
	if (nb < 0)
	{
		i += ft_putchar('-', on);
		nb = -nb;
	}
	if (nb == baselen)
	{
		i += ft_putchar(base[1], on);
	}
	if (nb > baselen)
		ft_putnbr((nb / baselen), base, baselen, on);
	i += ft_putchar(base[nb % baselen], on);

	return (i);
}

int			ft_putnbr_base(long long nbr, char *base, int on)
{
	int	baselen;
	int	i;

	i = 0;
	baselen = ft_strlen(base);
	i = ft_putnbr(nbr, base, baselen, on);

	return (i);
}

int			ft_putptr_base(long long nbr, char *base, int on)
{
	int	i;

	i = 0;
	if (!nbr)
		ft_putstr("(NULL)", 0, 1);
	if (on)
		ft_putstr("0x", 0, 1);
	i = ft_putnbr_base(nbr, base, on) + 2;

	return (i);
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
	option->num_n = 0;
	option->type = 0;
	return (option);
}

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

int		padding(int i, char c)
{
	int	j;

	j = 0;
	while (i-- > 0)
		j += ft_putchar(c, 1);
	return (j);
}

t_option		*analyze_format(char *toformat, va_list args)
{
	char		tmp;
	size_t		i;
	t_option	*option;

	option = ft_init_option();
	i = 0;
	while (!find_converter(toformat[i], "cspdiuxX") && toformat[i])
	{
		if ((tmp = find_converter(toformat[i], "0-.*")) != 0)
		{
			if (toformat[i - 1] && toformat[i - 1] != '.' && toformat[i] == '-')
				option->flag_minus = tmp == '-' ? 1 : 0;
			else if (toformat[i] == '.')
				option->dot = tmp == '.' ? 1 : 0;
			else if (toformat[i - 1] && (toformat[i - 1] < '9' && toformat[i - 1] > '0') && toformat[i] == '0')
				option->flag_zero = tmp == '0' ? 1 : 0;
			else if (toformat[i] == '*' && toformat[i - 1] != '.')
				option->width = tmp == '*' ? va_arg(args, int) : 0;
			else if (toformat[i] == '*' && toformat[i - 1] != '.')
				option->dot = tmp == '*' ? va_arg(args, int) : 0;
		}
		if (find_converter(toformat[i], "1234567890") && toformat[i])
		{
			if (toformat[i - 1] == '.')
				option->dot = ft_atoi(&toformat[i]);
			else
			{
				option->width = ft_atoi(&toformat[i]);
				i = i + ft_intlen(option->width) - 1;
			}
		}
		i++;
	}
	if (find_converter(toformat[i], "cspdiuxX") != 0)
		option->type = find_converter(toformat[i], "cspdiuxX");
	return (option);
}

size_t		len_filter(char *toformat)
{
	size_t	j;

	j = 0;
	while (!find_converter(toformat[j], "cspdiuxX") && *toformat)
		j++;
	if (find_converter(toformat[j], "cspdiuxX"))
		j++;
	return (j);
}

int						convert_type_format(t_option *option, va_list args)
{
	char				*tmp;
	unsigned long int	tmpli;
	int					tmpi;
	unsigned int		tmpui;
	int					i;
	int					j;

	i = 0;
	j = 0;
	tmp = malloc(255);
	if (option->type == 'c')
	{
		if (option->width > 0 && option->flag_minus == 0)
			j += padding(option->width - 1, ' ');
		j += ft_putchar(va_arg(args, int), 1);
		if (option->flag_minus > 0 && option->width > 0)
			j += padding(option->width - 1, ' ');
	}
	if (option->type == 's')
	{
		tmp = va_arg(args, char*);
		i = ft_putstr(tmp, option->dot, 0);
		if (option->width > 0 && option->flag_minus == 0 && option->width > i)
			j += padding(option->width - i, ' ');
		j += ft_putstr(tmp, option->dot, 1);
		if (option->flag_minus > 0 && option->width > 0)
			j += padding(option->width - i, ' ');
	}
	if (option->type == 'p')
	{
		tmpli = va_arg(args, unsigned long int);
		i = ft_putptr_base(tmpli, "0123456789abcdef", 0);
		if (option->width > 0 && option->flag_minus == 0 && option->width > i)
			j += padding(option->width - i, ' ');
		j += ft_putptr_base(tmpli, "0123456789abcdef", 1);
		if (option->flag_minus > 0 && option->width > 0)
			j += padding(option->width - i, ' ');
	}
	if (option->type == 'd' || option->type == 'i')
	{
		tmpi = va_arg(args, int);
		i = ft_putnbr_base(tmpi, "0123456789", 0);
		if (option->flag_minus == 0 && option->width > option->dot)
		{
			if (option->width > i)
				j += padding(option->width - option->dot, ' ');
			else
				j += padding(option->width - i, ' ');
		}
		if (option->flag_zero > 0 || option->dot > i)
			j += padding(option->dot - i, '0');
		j += ft_putnbr_base(tmpi, "0123456789", 1);
		if (option->flag_minus > 0 && option->width > option->dot)
		{
			if (i < option->dot)
				j += padding(option->width - option->dot, ' ');
			else
				j += padding(option->width - i, ' ');
		}
	}
	if (option->type == 'u')
	{
		tmpui = va_arg(args, unsigned int);
		i = ft_putnbr_base(tmpui, "0123456789", 0);
		if (option->flag_minus == 0 && option->width > option->dot)
		{
			if (option->width > i)
				j += padding(option->width - option->dot, ' ');
			else
				j += padding(option->width - i, ' ');
		}
		if (option->flag_zero > 0 || option->dot > i)
			j += padding(option->dot - i, '0');
		j += ft_putnbr_base(tmpui, "0123456789", 1);
		if (option->flag_minus > 0 && option->width > option->dot)
		{
			if (i < option->dot)
				j += padding(option->width - option->dot, ' ');
			else
				j += padding(option->width - i, ' ');
		}
	}
	if (option->type == 'x')
	{
		tmpui = va_arg(args, unsigned int);
		i = ft_putnbr_base(tmpui, "0123456789abcdef", 0);
		if (option->flag_minus == 0 && option->width > option->dot)
		{
			if (option->width > i)
				j += padding(option->width - option->dot, ' ');
			else
				j += padding(option->width - i, ' ');
		}
		if (option->flag_zero > 0 || option->dot > i)
			j += padding(option->dot - i, '0');
		j += ft_putnbr_base(tmpui, "0123456789abcdef", 1);
		if (option->flag_minus > 0 && option->width > option->dot)
		{
			if (i < option->dot)
				j += padding(option->width - option->dot, ' ');
			else
				j += padding(option->width - i, ' ');
		}
	}
	if (option->type == 'X')
	{
		tmpui = va_arg(args, unsigned int);
		i = ft_putnbr_base(tmpui, "0123456789ABCDEF", 0);
		if (option->flag_minus == 0 && option->width > option->dot)
		{
			if (option->width > i)
				j += padding(option->width - option->dot, ' ');
			else
				j += padding(option->width - i, ' ');
		}
		if (option->flag_zero > 0 || option->dot > i)
			j += padding(option->dot - i, '0');
		j += ft_putnbr_base(tmpui, "0123456789ABCDEF", 1);
		if (option->flag_minus > 0 && option->width > option->dot)
		{
			if (i < option->dot)
				j += padding(option->width - option->dot, ' ');
			else
				j += padding(option->width - i, ' ');
		}
	}
	return (j);
}

int				ft_printf(const char *format, ...)
{
	int			count;
	char		*toformat;
	size_t		i;
	t_option	*option;

	count = 0;
	toformat = (char *)format;
	va_list	args;
	va_start(args, format);
	while (*toformat)
	{
		if (*toformat == '%')
		{
			toformat++;
			option = analyze_format(toformat, args);
			i = len_filter(toformat);
			count += convert_type_format(option, args);
			free(option);
			toformat = toformat + i;
		}
		else
			count += ft_putchar(*toformat++, 1);
	}
	va_end(args);
	return (count);
}

int	main(void)
{
	char str[2] = {"he"};
	printf("Hello mr [%c] [%10.2s] [%15p] [%10%05.4d] [%i] [%x] [%X] [%u]\n", 'e', "Pello", str, 7, +56, -213, 526, -527, 50);
	ft_printf("Hello mr [%c] [%10.2s] [%15p] [%10%05.4d] [%i] [%x] [%X] [%u]\n", 'e', "Fello", str, 7, +56, -213, 526, -527, 50);
}
