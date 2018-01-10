/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_av.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlyubich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:39:27 by dlyubich          #+#    #+#             */
/*   Updated: 2018/01/09 15:39:27 by dlyubich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_bminone(void *s, size_t n)
{
	unsigned long i;
	unsigned char *new;

	i = 0;
	new = (unsigned char*)s;
	while (i < n)
	{
		new[i] = 0;
		i++;
	}
}

int			count_char(const char *str, int i, t_val *val, char c)
{
	int counter;

	counter = 0;
	while (str[i] == c)
	{
		counter++;
		i++;
	}
	if (counter % 2)
		val->size = c == 'l' ? 3 : 2;
	else
		val->size = c == 'l' ? 4 : 1;
	return (i - 1);
}

int			parse_args(const char *str, int i, va_list args)
{
	t_val	val;
	int		tmp;

	ft_bminone(&val, sizeof(val));
	val.prec = -1;
	while (1)
	{
		tmp = i;
		i = parse_sign(str, i, &val);
		i = parse_dig(str, i, &val, args);
		i = parse_bukva(str, i, &val);
		if (tmp == i)
			break ;
	}
	val.bukva = str[i];
	parse_next(val, args);
	if (!str[i])
		return (i);
	return (i + 1);
}

static int	ft_my_printf(const char *str, va_list args)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '%' && (i += 2))
				g_count += write(1, "%", 1);
			else
				i = parse_args(str, ++i, args);
		}
		else
		{
			g_count += write(1, &str[i], 1);
			i++;
		}
	}
	return (g_count);
}

int			ft_printf(const char *format, ...)
{
	va_list args;
	int		res;

	va_start(args, format);
	g_count = 0;
	res = ft_my_printf(format, args);
	va_end(args);
	return (res);
}
