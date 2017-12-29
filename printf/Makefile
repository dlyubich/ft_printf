
NAME = libftprintf.a

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I ft_printf.h

OBJECTS = ft_width.o itoas.o libft_func.o libft_func2.o mod_av.o read_av.o cast_av.o wide_str.o wide_help.o mod_char.o

SRC = ft_width.c itoas.c libft_func.c libft_func2.c mod_av.c read_av.c cast_av.c wide_str.c wide_help.c mod_char.c

all : $(NAME)

$(NAME) :
	gcc -c $(CFLAGS) $(SRC) $(INCLUDES)
	ar rc $(NAME) $(OBJECTS)

clean :
	rm -rf $(OBJECTS)

fclean : clean
	rm -rf $(NAME)

re : fclean all