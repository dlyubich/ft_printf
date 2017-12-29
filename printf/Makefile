NAME = libftprintf.a

INCLUDES = -I ft_printf.h

SRC =	ft_width.c \
		itoas.c \
		libft_func.c \
		libft_func2.c \
		mod_av.c \
		read_av.c \
		cast_av.c \
		wide_str.c \
		wide_help.c \
		mod_char.c

CFLAGS = -Wall -Wextra -Werror

OBJECTS = $(SRC:.c=.o)

all :	$(NAME)

$(NAME) : $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)

%.o: %.c $(HEADER)
	gcc -c $(CFLAGS) -o $@ $<

clean :
	rm -rf $(OBJECTS)

fclean :	clean
	rm -rf $(NAME)

re :	fclean all