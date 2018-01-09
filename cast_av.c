/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_av.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlyubich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 14:35:24 by dlyubich          #+#    #+#             */
/*   Updated: 2018/01/09 14:35:28 by dlyubich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	cast_pointer(t_val val, va_list args)
{
	uintmax_t	ret;
	char		*str;
	char		*tmp;
	char		*buf;

	str = ft_strnew(2);
	str[0] = '0';
	str[1] = 'x';
	ret = (uintmax_t)va_arg(args, void*);
	if (ret == 0 && val.prec != -1)
		buf = str;
	else
	{
		tmp = ft_itoa_base(ret, 16, 0);
		buf = ft_strjoin(str, tmp);
		free(tmp);
		free(str);
	}
	ft_mod(buf, val, 1);
}

void	cast_char(t_val val, va_list args)
{
	char	*str;
	wchar_t *wstr;

	if (val.bukva == 'S' || (val.bukva == 's' && val.size == 3))
	{
		if (!(wstr = va_arg(args, wchar_t*)))
			ft_widestr(L"(null)", val);
		else
			ft_widestr(wstr, val);
	}
	else
	{
		str = NULL;
		if (val.bukva == 's')
		{
			str = va_arg(args, char*);
			if (!str)
				str = ft_strdup("(null)");
			else
				str = ft_strdup(str);
			ft_modchar(str, val);
		}
		else if (val.bukva == 'c' || val.bukva == 'C')
			ft_char(val, args);
	}
}

void	cast_int(t_val val, va_list args)
{
	intmax_t ret;

	if (val.size == 3 || val.bukva == 'D')
		ret = va_arg(args, long);
	else if (val.size == 6)
		ret = va_arg(args, size_t);
	else if (val.size == 5)
		ret = va_arg(args, intmax_t);
	else if (val.size == 4)
		ret = va_arg(args, long long);
	else if (val.size == 2)
		ret = (short)va_arg(args, int);
	else if (val.size == 1)
		ret = (signed char)va_arg(args, int);
	else
		ret = va_arg(args, int);
	ft_mod(ft_itoaint(ret), val, 0);
}

void	cast_unsigned(t_val val, va_list args)
{
	uintmax_t ret;

	if (val.size == 3 || val.bukva == 'U' || val.bukva == 'O')
		ret = va_arg(args, unsigned long);
	else if (val.size == 6)
		ret = va_arg(args, size_t);
	else if (val.size == 5)
		ret = va_arg(args, uintmax_t);
	else if (val.size == 4)
		ret = va_arg(args, unsigned long long);
	else if (val.size == 2)
		ret = (unsigned short)va_arg(args, unsigned int);
	else if (val.size == 1)
		ret = (unsigned char)va_arg(args, unsigned int);
	else
		ret = va_arg(args, unsigned int);
	if (val.bukva == 'u' || val.bukva == 'U')
		ft_mod(ft_itoa_base(ret, 10, 0), val, 1);
	else if (val.bukva == 'o' || val.bukva == 'O')
		ft_mod(ft_itoa_base(ret, 8, 0), val, 1);
	else
		ft_mod(ft_itoa_base(ret, 16, val.bukva == 'X' ? 1 : 0), val, 1);
}

void	ft_cast(t_val val, va_list args)
{
	if (val.bukva == 's' || val.bukva == 'S' ||
		val.bukva == 'c' || val.bukva == 'C')
		cast_char(val, args);
	else if (val.bukva == 'd' || val.bukva == 'D' || val.bukva == 'i')
		cast_int(val, args);
	else if (val.bukva == 'o' || val.bukva == 'O' || val.bukva == 'u'
		|| val.bukva == 'U' || val.bukva == 'x' || val.bukva == 'X')
		cast_unsigned(val, args);
	else if (val.bukva == 'p')
		cast_pointer(val, args);
}
