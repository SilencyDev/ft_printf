/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:52:26 by kmacquet          #+#    #+#             */
/*   Updated: 2021/02/16 16:27:36 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	g_count = 0;

int	ft_putchar(char c, int on)
{
	if (on != 0)
	{
		write(1, &c, 1);
		g_count++;
	}
	return (1);
}

int	ft_putstr(char *str, int prec, int on)
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

int					ft_putptr(unsigned long int nb, char *base, int on)
{
	static int		i;
	unsigned int	baselen;

	baselen = ft_strlen(base);
	i = 0;
	if (nb == baselen)
	{
		i += ft_putchar(base[1], on);
	}
	if (nb > baselen)
		ft_putptr((nb / baselen), base, on);
	i += ft_putchar(base[nb % baselen], on);

	return (i);
}

int				ft_putnbr(long long nb, char *base, int on)
{
	static int	i;
	int			baselen;

	baselen = ft_strlen(base);
	i = 0;
	if (nb < 0)
	{
		ft_putchar('-', 0);
		nb = -nb;
	}
	if (nb == baselen)
	{
		i += ft_putchar(base[1], on);
	}
	if (nb > baselen)
		ft_putnbr((nb / baselen), base, on);
	i += ft_putchar(base[nb % baselen], on);

	return (i);
}

int		ft_putnbr_base(long nbr, char *base, int on)
{
	int	i;

	i = 0;
	i = ft_putnbr(nbr, base, on);

	return (i);
}

int		ft_putptr_base(unsigned long int nbr, char *base, int on)
{
	int	i;

	i = 0;
	i = ft_putptr(nbr, base, on);

	return (i);
}

t_option	*ft_init_option(t_option *o)
{
	o->flag_minus = 0;
	o->flag_zero = 0;
	o->width = 0;
	o->dot = -1;
	o->a_p = 0;
	o->type = 0;
	return (o);
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

t_option	*analyze_format(char *toformat, va_list args, t_option *o)
{
	size_t	i;
	int		tmp;

	i = 0;
	while (find_converter(toformat[i], "0123456789.-*") && toformat[i])
	{
		if ((find_converter(toformat[i], "0-.*")) != 0)
		{
			if (toformat[i] == '-')
			{
				o = ft_init_option(o);
				o->flag_minus = 1;
			}
			else if (toformat[i] == '.')
				o->dot = 0;
			else if (toformat[i] == '0' && (toformat[i - 1] < '0' || toformat[i - 1] > '9'))
				o->flag_zero = 1;
			else if (toformat[i] == '*')
			{
				tmp = va_arg(args, int);
				if (toformat[i - 1] != '.')
				{
					if (o->width < 0)
						o = ft_init_option(o);
					o->width = tmp;
				}
				if (toformat[i - 1] == '.')
					o->dot = tmp;
			}
		}
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

size_t		len_filter(char *toformat)
{
	size_t	j;

	j = 0;
	while (find_converter(toformat[j], "0123456789.-*") && *toformat)
		j++;
	return (j);
}

char	*set_base(char c)
{
	if (c == 'p' || c == 'x')
		return ("0123456789abcdef");
	else if (c == 'd' || c == 'i' || c == 'u')
		return ("0123456789");
	else if (c == 'X')
		return ("0123456789ABCDEF");
	return (0);
}

void	convert_s(char *s, t_option *o)
{
	int	i;

	if (s == NULL)
		s = "(null)";
	i = ft_putstr(s, o->dot, 0);
	o->a_p = o->dot < i ? o->dot : i;
	if (o->dot < 0)
		o->a_p = i;
	if (o->flag_minus == 0 && o->width > o->a_p && o->a_p > -1)
	{
		if (o->flag_zero == 1 && o->dot != 0)
			padding(o->width - o->a_p, '0');
		else
			padding(o->width - o->a_p, ' ');
	}
	ft_putstr(s, o->a_p, 1);
	if (o->flag_minus > 0 && o->width > o->a_p)
		padding(o->width - o->a_p, ' ');
}

void	convert_di(int nb, t_option *o)
{
	int	i;

	i = ft_putnbr_base(nb, set_base(o->type), 0);
	o->a_p = o->dot > i ? o->dot : i;
	if (nb < 0)
		o->width--;
	if (o->dot < 0)
		o->a_p = i;
	if (o->dot == 0 && nb == 0)
		o->a_p = 0;
	if (o->flag_minus == 0 && o->width > o->a_p)
	{
		if (o->flag_zero == 1 && o->dot < 0)
		{
			if (nb < 0)
				ft_putchar('-', 1);
			padding(o->width - o->a_p, '0');
		}
		else
			padding(o->width - o->a_p, ' ');
	}
	if (nb < 0 && !(o->flag_zero == 1 && o->dot < 0))
		ft_putchar('-', 1);
	o->dot = nb < 0 ? o->dot++ : o->dot;
	o->dot > i ? padding(o->dot - i, '0') : 0;
	if (!(nb == 0 && o->dot == 0))
		ft_putnbr_base(nb, set_base(o->type), 1);
	if (o->flag_minus > 0 && o->width > o->a_p)
		padding(o->width - o->a_p, ' ');
}

void	convert_uxx(unsigned int nb, t_option *o)
{
	int	i;

	i = ft_putnbr_base(nb, set_base(o->type), 0);
	o->a_p = o->dot > i ? o->dot : i;
	if (o->dot < 0)
		o->a_p = i;
	if (o->dot == 0 && nb == 0)
		o->a_p = 0;
	if (o->flag_minus == 0 && o->width > o->a_p)
	{
		if (o->flag_zero == 1 && o->dot < 0)
			padding(o->width - o->a_p, '0');
		else
			padding(o->width - o->a_p, ' ');
	}
	o->dot > i ? padding(o->dot - i, '0') : 0;
	if (!(nb == 0 && o->dot == 0))
		ft_putnbr_base(nb, set_base(o->type), 1);
	if (o->flag_minus > 0 && o->width > o->a_p)
		padding(o->width - o->a_p, ' ');
}

void	convert_p(unsigned long int nb, t_option *o)
{
	int i;

	i = ft_putptr_base(nb, set_base(o->type), 0);
	o->a_p = o->dot > i ? o->dot : i;
	if (o->dot < 0)
		o->a_p = i;
	if (o->flag_minus == 0 && o->width > o->a_p)
	{
		if (o->flag_zero == 1 && o->dot != 0)
			padding(o->width - (o->a_p + 2), '0');
		else
			padding(o->width - (o->a_p + 2), ' ');
	}
	ft_putstr("0x", -1, 1);
	if (o->flag_zero > 0 || o->dot > i)
		padding(o->dot - i, '0');
	ft_putptr_base(nb, set_base(o->type), 1);
	if (o->flag_minus > 0 && o->width > o->a_p)
		padding(o->width - (o->a_p + 2), ' ');
}

void	convert_type_format(t_option *o, va_list args)
{
	int	i;

	i = 0;
	if (o->width < 0)
	{
		o->flag_minus = 1;
		o->width = -o->width;
	}
	if (o->type == 's')
		convert_s(va_arg(args, char*), o);
	else if (o->type == 'p')
		convert_p(va_arg(args, long long), o);
	else if (o->type == 'd' || o->type == 'i')
		convert_di(va_arg(args, int), o);
	else if (o->type == 'X' || o->type == 'x' || o->type == 'u')
		convert_uxx(va_arg(args, unsigned int), o);
	else
	{
		if (o->flag_minus == 0)
		{
			if (o->flag_zero > 0)
				padding(o->width - 1, '0');
			else
				padding(o->width - 1, ' ');
		}
		if (o->type == 'c' && o->dot != 0)
			ft_putchar(va_arg(args, int), 1);
		else if (o->dot != 0)
			ft_putchar(o->type, 1);
		if (o->flag_minus == 1)
			padding(o->width - 1, ' ');
	}
}

int				ft_printf(const char *format, ...)
{
	char		*toformat;
	size_t		i;
	t_option	*o;

	toformat = (char *)format;
	va_list	args;
	va_start(args, format);
	if (!(o = malloc(sizeof(t_option))))
		return (-1);
	while (*toformat)
	{
		if (*toformat == '%')
		{
			toformat++;
			o = analyze_format(toformat, args, ft_init_option(o));
			i = len_filter(toformat);
			convert_type_format(o, args);
			toformat = toformat + i + 1;
		}
		else
			ft_putchar(*toformat++, 1);
	}
	free(o);
	va_end(args);
	return (g_count);
}

// #include <limits.h>

// int	main(void)
// {
// 	char str[2] = {"he"};
// 	printf("Hello mr [%010c] [%010.7s] [%-20.14p] [%10.5.4d] [%i] [%x] [%X] [%u]\n", 'e', "Pello", str, 7, +56, -213, 526, -527, 50);
// 	ft_printf("Hello mr [%010c] [%010.7s] [%-20.14p] [%10.5.4d] [%i] [%x] [%X] [%u]\n", 'e', "Fello", str, 7, +56, -213, 526, -527, 50);
// 	printf("p [ 0*%0-*.*d*0 0*%0*.*d*0 ]\n", 6, 2, 102, 10, 21, -101);
// 	ft_printf("f [ 0*%0-*.*d*0 0*%0*.*d*0 ]\n", 6, 2, 102, 10, 21, -101);
// 	printf("p [%.-10x]\n", 100000);
// 	ft_printf("f [%.-10x]\n", 100000);
// 	printf("p [%.*x]\n", -10,100000);
// 	ft_printf("f [%.*x]\n", -10,100000);
// 	printf("p [%0x]\n", 0);
// 	ft_printf("f [%0x]\n", 0);
// 	printf("p [%1.x]\n", 0);
// 	ft_printf("f [%1.x]\n", 0);
// 	printf("p [%011.2x]\n", 1000000);
// 	ft_printf("f [%011.2x]\n", 1000000);
// 	printf("p [%-9.1s]\n",NULL);
// 	ft_printf("f [%-9.1s]\n",NULL);
// }
