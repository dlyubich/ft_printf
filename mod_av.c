/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_av.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlyubich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:06:53 by dlyubich          #+#    #+#             */
/*   Updated: 2018/01/09 15:06:54 by dlyubich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*pre_join(char *str, int len, char *rem, int pl)
{
	char *help;
	char *tmp;

	help = ft_strnew(len);
	ft_memset(help, '0', len);
	tmp = str;
	str = ft_strjoin(help, str + pl);
	free(tmp);
	free(help);
	tmp = str;
	str = ft_strjoin(rem, str);
	free(tmp);
	return (str);
}

void		prec_dig_help(char **str, t_val val, char *rem)
{
	int len;

	rem = ft_strsub(*str, 0, 2);
	if ((len = ft_strlen(*str + 2)) < val.prec)
		*str = pre_join(*str, val.prec - len, rem, 2);
	free(rem);
}

char		*ft_prec_dig(char *str, t_val val)
{
	char	*tmp;
	char	*rem;
	int		len;

	rem = NULL;
	tmp = NULL;
	if (val.sign || val.space || str[0] == '-')
	{
		rem = ft_strnew(1);
		rem[0] = str[0];
		if ((len = ft_strlen(str + 1)) < val.prec)
			str = pre_join(str, val.prec - len, rem, 1);
		free(rem);
	}
	else if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		prec_dig_help(&str, val, rem);
	else if (val.prec > (len = ft_strlen(str)))
		str = pre_join(str, val.prec - len, "", 0);
	return (str);
}

char		*ft_mod_prec(char *str, t_val val)
{
	char *tmp;

	if (val.bukva == 'd' || val.bukva == 'D' || val.bukva == 'i' ||
		val.bukva == 'o' || val.bukva == 'O' || val.bukva == 'u' ||
		val.bukva == 'U' || val.bukva == 'x' || val.bukva == 'X' ||
		val.bukva == 'p')
		str = ft_prec_dig(str, val);
	else if (val.bukva == 's' || val.bukva == 'S')
	{
		if ((int)ft_strlen(str) > val.prec)
		{
			tmp = str;
			str = ft_strsub(str, 0, val.prec);
			free(tmp);
		}
	}
	return (str);
}

void		ft_mod(char *str, t_val val, int un)
{
	if (val.prec == 0 && val.bukva != 'p' && (str[0] == '0' || !str))
	{
		if (str)
			free(str);
		str = ft_strnew(0);
	}
	if (un && val.resh && str[0] != '0')
		str = ft_mod_resh(str, val);
	else if (un == 0 && str[0])
		str = ft_mod_sign(str, val);
	if (val.prec > 0)
		str = ft_mod_prec(str, val);
	if (val.width > 0)
		str = ft_width(str, val);
	g_count += write(1, str, ft_strlen(str));
	free(str);
}
