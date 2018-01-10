/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlyubich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 13:18:34 by dlyubich          #+#    #+#             */
/*   Updated: 2017/12/22 13:18:36 by dlyubich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <wchar.h>

# define A(x) ((x) < 0 ? -(x) : (x))

int	g_count;

# define BIT7 127
# define BIT11 2047
# define BIT16 65535
# define BIT21 2097151
# define BIT26 67108863
# define BIT31 2147483647

typedef	struct	s_values
{
	int			minus;
	int			sign;
	int			zero;
	int			resh;
	int			space;

	int			width;
	int			prec;
	int			size;
	char		bukva;

}				t_val;

int				ft_printf(const char *format, ...);
void			ft_cast(t_val val, va_list args);
char			*ft_itoaint(intmax_t value);
char			*ft_itoa_base(unsigned long long value, int base, int flag);
char			*ft_width(char *str, t_val val);
void			ft_mod(char *str, t_val val, int un);
int				ft_isdigit(int c);
char			*ft_strnew(size_t size);
void			*ft_memset(void *b, int c, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlen(const char *s);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
int				ft_tolower(int c);
char			*ft_mod_prec(char *str, t_val val);
void			ft_widestr(wchar_t *d, t_val val);
void			ft_place_char(int size, char c);
int				ft_check_len_wch(char **data);
void			ft_wputstr(char **d);
void			ft_char(t_val val, va_list args);
char			*ft_strdup(char *src);
void			ft_modchar(char *str, t_val val);
char			*ft_mod_resh(char *str, t_val val);
char			*ft_mod_sign(char *str, t_val val);
int				parse_sign(const char *str, int i, t_val *val);
int				parse_dig(const char *str, int i, t_val *val, va_list args);
int				parse_bukva(const char *str, int i, t_val *val);
void			parse_next(t_val val, va_list args);
void			ft_help(t_val val);
int				count_char(const char *str, int i, t_val *val, char c);

#endif
