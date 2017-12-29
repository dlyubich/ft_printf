#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlyubich <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/29 17:16:42 by dlyubich          #+#    #+#              #
#    Updated: 2017/12/29 17:19:41 by dlyubich         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libftprintf.a

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I libftprintf.h

OBJECTS = cast_av.o ft_width.o itoas.o libft_func.o	libft_func2.o \
		  mod_av.o mod_char.o read_av.o wide_help.o wide_str.o \

SRC = cast_av.c ft_width.c itoas.c libft_func.c libft_func2.c \
	  mod_av.c mod_char.c read_av.c wide_help.c wide_str.c \

all : $(NAME)

$(NAME) : 
	gcc -c $(CFLAGS) $(SRC) $(INCLUDES)
	ar rc $(NAME) $(OBJECTS)

clean : 
	rm -rf $(OBJECTS)

fclean : clean 
	rm -rf $(NAME)

re : fclean all