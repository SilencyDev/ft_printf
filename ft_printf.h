/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 13:45:16 by kmacquet          #+#    #+#             */
/*   Updated: 2021/02/15 17:42:56 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_H
# define FT_PRINT_H

# include <stdarg.h>
# include "libft/libft.h"

typedef struct		s_option
{
	int flag_minus;
	int flag_zero;
	int width;
	int dot;
	int a_p;
	char type;
 }					t_option;


int	ft_printf(const char *format, ...);
#endif
