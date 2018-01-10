/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_av_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlyubich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:10:05 by dlyubich          #+#    #+#             */
/*   Updated: 2018/01/09 16:10:06 by dlyubich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_sign(const char *str, int i, t_val *val)
{
	while (str[i] == '-' || str[i] == '+' || str[i] == '0' || str[i] == '#'
	|| str[i] == ' ')
	{
		if (str[i] == '-' && !(val->zero = 0))
			val->minus = 1;
		else if (str[i] == '+')
			val->sign = 1;
		else if (str[i] == '0' && !val->minus)
			val->zero = 1;
		else if (str[i] == '#')
			val->resh = 1;
		else if (str[i] == ' ' && val->sign != 1)
			val->space = 1;
		i++;
	}
	return (i);
}

int		parse_width(const char *str, int i, t_val *val, va_list args)
{
	if (str[i] == '*')
	{
		val->width = va_arg(args, int);
		if (val->width < 0)
		{
			val->width *= -1;
			val->minus = 1;
		}
		i++;
	}
	else
	{
		while (ft_isdigit(str[i]))
		{
			val->width = val->width * 10 + str[i] - '0';
			i++;
		}
	}
	return (i);
}

int		parse_dig(const char *str, int i, t_val *val, va_list args)
{
	i = parse_width(str, i, val, args);
	if (str[i] == '.')
	{
		val->prec = 0;
		i++;
		if (str[i] == '*')
		{
			val->prec = va_arg(args, int);
			if (val->prec < 0)
				val->prec = -1;
			i++;
		}
		else
		{
			while (ft_isdigit(str[i]))
			{
				val->prec = val->prec * 10 + str[i] - '0';
				i++;
			}
		}
	}
	return (i);
}

int		parse_bukva(const char *str, int i, t_val *val)
{
	while (str[i] == 'j' || str[i] == 'l' || str[i] == 'h' || str[i] == 'z')
	{
		if (str[i] == 'z')
			val->size = 6;
		else if (str[i] == 'j' && val->size < 5)
			val->size = 5;
		else if (str[i] == 'l' && val->size < 4)
			i = count_char(str, i, val, 'l');
		else if (str[i] == 'h' && val->size < 2)
			i = count_char(str, i, val, 'h');
		i++;
	}
	return (i);
}

void	parse_next(t_val val, va_list args)
{
	if (val.bukva == 's' || val.bukva == 'S' || val.bukva == 'o'
		|| val.bukva == 'O' || val.bukva == 'u' || val.bukva == 'U'
		|| val.bukva == 'd' || val.bukva == 'D' || val.bukva == 'i'
		|| val.bukva == 'x' || val.bukva == 'X' || val.bukva == 'c'
		|| val.bukva == 'C' || val.bukva == 'p')
		ft_cast(val, args);
	else
		ft_help(val);
}
