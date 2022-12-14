# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 15:29:08 by mvieira-          #+#    #+#              #
#    Updated: 2022/09/07 16:08:45 by ghenaut-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADERS_PATH = ./includes/
SRCS_PATH = ./srcs/
OBJS_PATH = ./objs/
LIBS_PATH = ./Libft/
CC = cc
CFLAGS = -g -g3 -I $(HEADERS_PATH) -Wall -Wextra -Werror 
RM = rm -rf
MKDIR = mkdir -p
MAKE_NOPRINT = $(MAKE) --no-print-directory
NAME = minishell
SRC_FILES = main.c \
			minishell.c \
			parser.c \
			parser_utils.c \
			parser_utils2.c \
			expander.c \
			cleanup.c \
			lexer.c \
			env.c \
			executer_child.c \
			executer_error.c \
			executer_utils.c \
			executer_utils2.c \
			executor_handler.c \
			here_doc.c \
			env_bi.c \
			pwd.c \
			cd.c \
			echo.c \
			executer_builtin.c \
			export_bi.c \
			unset_bi.c \
			exit_bi.c \
			utils.c \
			signals.c \
			export_bi_utils.c \
			executer_parser.c \

LIBFT_A = $(LIBS_PATH)libft.a 
SOURCES = $(addprefix $(SRCS_PATH), $(SRC_FILES))
OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES))
OBJECTS = $(addprefix $(OBJS_PATH), $(OBJ_FILES))
#echo "dasdasd    asdsad" "dasdasdsa" hello "hello     world"

all: $(NAME)


$(LIBFT_A):
	@cd $(LIBS_PATH) && $(MAKE_NOPRINT)
	
$(NAME): $(LIBFT_A) $(OBJECTS) 
	@$(CC) -o $(NAME) $(OBJECTS) $(LIBFT_A) -lreadline

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@$(MKDIR) $(OBJS_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: all

clean:
	@$(RM) objs test/bin
	@$(MAKE_NOPRINT) clean -C $(LIBS_PATH)


fclean: clean
	@$(RM) $(NAME)
	@$(MAKE_NOPRINT) fclean -C $(LIBS_PATH)

re: fclean all

.PHONY: all run clean fclean re 