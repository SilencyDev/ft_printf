/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:19:47 by kmacquet          #+#    #+#             */
/*   Updated: 2021/02/17 11:48:37 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

int					ft_putnbr(long long nb, char *base, int on)
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

int					ft_putnbr_base(long nbr, char *base, int on)
{
	int	i;

	i = 0;
	i = ft_putnbr(nbr, base, on);
	return (i);
}

int					ft_putptr_base(unsigned long int nbr, char *base, int on)
{
	int	i;

	i = 0;
	i = ft_putptr(nbr, base, on);
	return (i);
}
