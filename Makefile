#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yguzman <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/07/18 11:38:09 by yguzman           #+#    #+#              #
#    Updated: 2017/09/28 14:41:53 by yguzman          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC			=		clang

NAME		=		minishell

DIR_SRC		=		./src/

SRCS		=		$(DIR_SRC)main.c					\
					$(DIR_SRC)prompt.c					\
					$(DIR_SRC)builtin/env.c				\
					$(DIR_SRC)builtin/env1.c			\
					$(DIR_SRC)builtin/setenv.c			\
					$(DIR_SRC)token/tokenzer.c			\
					$(DIR_SRC)token/token_tild.c		\
					$(DIR_SRC)builtin/exit.c			\
					$(DIR_SRC)builtin/cd.c				\
					$(DIR_SRC)builtin/echo.c			\
					$(DIR_SRC)builtin/echo1.c			\
					$(DIR_SRC)builtin/unsetenv.c		\
					$(DIR_SRC)tools/term.c				\
					$(DIR_SRC)tools/init.c				\
					$(DIR_SRC)edit_line/edit_line.c		\
					$(DIR_SRC)edit_line/edit_line1.c	\
					$(DIR_SRC)edit_line/editline2.c		\
					$(DIR_SRC)tools/signal.c			\
					$(DIR_SRC)tools/free.c				\
					$(DIR_SRC)msh.c						\
					$(DIR_SRC)exec/read_and_fill_cmd.c	\
					$(DIR_SRC)exec/read_and_fill_cmd1.c	\
					$(DIR_SRC)exec/read_and_fill_cmd2.c	\
					$(DIR_SRC)tools/copy_env.c

OBJS		=		$(SRCS:.c=.o)

CFLAGS		+=		-Iinclude
CFLAGS		+=		-Wall -Wextra

RM			=		rm -f

LIB			=		./libft/libft.a

ECHO		=		printf

all			:		$(NAME)

$(NAME)		:		$(OBJS)
					@make -C libft
					@$(ECHO) "\033[35m[~~~~COMPILATION PROJECT~~~~]\n\033[0m"
					@$(CC) -o $(NAME) -Llibft -lft $(OBJS) && $(ECHO) "\033[33;32m["$@"]\n\033[0m" || $(ECHO) "\033[31m["$@"]\n\033[0m"

%.o			:		%.c
					@$(ECHO) "\033[35m[~~~Comipilation obj //project~~~]-->\033[0m"
					@$(CC) $(CFLAGS) -o $@ -c $< && $(ECHO) "\033[33;32m ["$@"]\n\033[0m" || $(ECHO) "\033[31m ["$@"]\n\033[0m"

clean_lib	:
					@make -C libft clean

clean		:		clean_lib
					@$(ECHO) "\033[31m[~~~~~~Supression des .o //project~~~~~~]\n\033[0m"
					@$(RM) $(OBJS)

fclean_lib	:
					@make -C libft fclean

fclean		:		fclean_lib
					@$(ECHO) "\033[31m[~~~~~~Supression des .o //project~~~~~~]\n\033[0m"
					@$(RM) $(OBJS)
					@$(ECHO) "\033[31m[~~~~Supression du Binaire~~~~]\n\033[0m"
					@$(RM) $(NAME)

re			:		fclean all

depend		:		$(SRCS)
					makedepend -- -Yinclude/ -- $^

.PHONY		:		all depend clean flean re

# DO NOT DELETE THIS LINE -- make depend depends on it.
