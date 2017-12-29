#include "ft_printf.h"

char	*ft_mod_resh(char *str, t_val val)
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

char	*ft_mod_sign(char *str, t_val val)
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

char	*pre_join(char *str, int len, char *rem)
{
	char *help;
	char *tmp;


	help = ft_strnew(len);
	ft_memset(help, '0', len);
	str = ft_strjoin(help, str);
	free(help);
	tmp = str;
	str = ft_strjoin(rem, str);
	free(tmp);
	return (str);
}

char	*ft_prec_dig(char *str, t_val val)
{
	char *tmp;
	char *rem;
	int len;

	if (val.sign || val.space || str[0] == '-')
	{
		rem = ft_strnew(1);
		rem[0] = str[0];
		if ((len = ft_strlen(str + 1)) < val.prec)
		{
			tmp = str;
			str = pre_join(str + 1, val.prec - len, rem);
			free(tmp);
		}
		free(rem);
	}
	else if (val.resh && val.bukva != 'i' && val.bukva != 'd' && val.bukva != 'D')
	{
		rem = ft_strsub(str, 0, 2);
		if ((len = ft_strlen(str + 2)) < val.prec)
		{
			tmp = str;
			str = pre_join(str + 2, val.prec - len, rem);
			free(tmp);
		}
		free(rem);
	}
	else if (val.prec > (len = ft_strlen(str)))
		str = pre_join(str, val.prec - len, "");
	return (str);
}

char	*ft_mod_prec(char *str, t_val val)
{
	char *tmp;
	if (val.bukva == 'd' || val.bukva == 'D' || val.bukva == 'i' || val.bukva == 'o' 
		|| val.bukva == 'O' || val.bukva == 'u' || val.bukva == 'U' || val.bukva == 'x' || val.bukva == 'X')
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

void	ft_mod(char *str, t_val val, int un)
{
	if (val.prec == 0 && val.bukva != 'p' && (str[0] == '0' || !str))
		str = ft_strnew(0);
	if (un && val.resh && str[0] != '0')
		str = ft_mod_resh(str, val);
	else if (un == 0 && str[0])
		str = ft_mod_sign(str, val);
	if (val.prec > 0)
		str = ft_mod_prec(str, val);
	if (val.width > 0)
		str = ft_width(str, val);
	g_count += write(1, str, ft_strlen(str));
}