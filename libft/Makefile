# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzinchen <dzinchen@student.42porto.co      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/18 09:42:25 by dzinchen          #+#    #+#              #
#    Updated: 2023/10/19 11:57:08 by dzinchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_toupper.c ft_tolower.c ft_isascii.c ft_isspace.c ft_strlen.c \
      ft_atoi.c ft_strlen.c ft_atoi.c ft_isprint.c ft_strncmp.c ft_memcmp.c ft_memset.c ft_bzero.c ft_isspecial.c \
      ft_strchr.c ft_strrchr.c ft_memchr.c ft_strlcpy.c ft_memcpy.c ft_memmove.c ft_strdup.c ft_isnumber.c ft_strcmp.c\
      ft_strlcat.c ft_strnstr.c ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_putchar_fd.c \
      ft_putnbr_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_strmapi.c ft_striteri.c ft_itoa.c ft_split.c \
      ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
      ft_lstmap.c ft_lstnew.c ft_lstsize.c \
      ft_printf/ft_printf.c ft_printf/ft_hex_array.c ft_printf/ft_len.c ft_printf/ft_putchar.c \
      ft_printf/ft_puthex.c ft_printf/ft_putnbr.c ft_printf/ft_putpointer.c ft_printf/ft_putstr.c \
      ft_printf/ft_typefinder.c \
      gnl/get_next_line.c gnl/get_next_line_utils.c

C_DEF   = \033[0;39m
C_GREEN = \033[0;92m
C_RED = \033[0;31m
C_YELLOW = \033[0;93m

OBJS = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $*.c -o $*.o

$(NAME):	${OBJS}
		ar rcs ${NAME} ${OBJS}
		@echo "${C_GREEN}[LIBFT COMPILED]${C_DEF}"

all: $(NAME)

clean:
	${RM} ${OBJS}
	@echo "${C_YELLOW}[LIBFT CLEANED]${C_DEF}"

fclean:	
		${RM} ${OBJS}
		${RM} ${NAME}
		@echo "${C_RED}[LIBFT FULL CLEANED]${C_DEF}"

re:	fclean all
	@echo "${C_GREEN}[LIBFT REBUILDED]${C_DEF}"

.PHONY: all clean fclean re

.SILENT:
