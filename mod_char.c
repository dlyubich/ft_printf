/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlyubich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:20:34 by dlyubich          #+#    #+#             */
/*   Updated: 2018/01/09 15:20:35 by dlyubich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_modchar_help(char *str, t_val val, char *tmp, int len)
{
	tmp = ft_strnew(val.width - len);
	if (val.zero > 0 && val.space <= 0)
		ft_memset(tmp, '0', val.width - len);
	else
		ft_memset(tmp, ' ', val.width - len);
	if (val.minus > 0)
	{
		g_count += write(1, str, len);
		g_count += write(1, tmp, val.width - len);
	}
	else
	{
		g_count += write(1, tmp, val.width - len);
		g_count += write(1, str, len);
	}
	free(tmp);
}

char		*ft_mod_resh(char *str, t_val val)
{
	char *tmp;

	tmp = str;
	if (val.bukva == 'o' || val.bukva == 'O')
		str = ft_strjoin("0", str);
	else if (val.bukva == 'x' && str[0])
		str = ft_strjoin("0x", str);
	else if (val.bukva == 'X' && str[0])
		str = ft_strjoin("0X", str);
	else
		return (str);
	free(tmp);
	return (str);
}

char		*ft_mod_sign(char *str, t_val val)
{
	char *tmp;

	if (str[0] != '-' && str[0])
	{
		tmp = str;
		if (val.sign)
			str = ft_strjoin("+", str);
		else if (val.space)
			str = ft_strjoin(" ", str);
		else
			return (str);
		free(tmp);
	}
	return (str);
}

void		ft_modchar(char *str, t_val val)
{
	char	*tmp;
	int		len;

	if (val.prec != -1 && val.prec < (int)ft_strlen(str))
	{
		tmp = str;
		str = ft_strsub(str, 0, val.prec);
		free(tmp);
	}
	len = ft_strlen(str);
	if (val.width > len)
		ft_modchar_help(str, val, tmp, len);
	else
		g_count += write(1, str, len);
	free(str);
}

void		ft_help(t_val val)
{
	char	*str;

	if (val.bukva == '\0')
		return ;
	else if (val.width <= 0)
		g_count += write(1, &val.bukva, 1);
	else
	{
		str = ft_strnew(val.width);
		if (val.zero > 0)
			ft_memset(str, '0', val.width);
		else
			ft_memset(str, ' ', val.width);
		if (val.minus > 0)
			str[0] = val.bukva;
		else
			str[val.width - 1] = val.bukva;
		g_count += write(1, str, val.width);
		free(str);
	}
}
