# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/17 18:18:37 by roaraujo          #+#    #+#              #
#    Updated: 2022/08/12 11:02:19 by mvieira-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADERS_PATH = ./includes/
SRCS_PATH = ./srcs/
OBJS_PATH = ./objs/
LIBS_PATH = ./Libft/
TEST_PATH = ./test
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -g3 -std=c11 -I $(HEADERS_PATH)
RM = rm -rf
MKDIR = mkdir -p
MAKE_NOPRINT = $(MAKE) --no-print-directory
NAME = minishell
SRC_FILES = main.c \
			init_shell.c \

TESTS=$(wildcard $(TEST_PATH)/*.c)
TESTBINS = $(patsubst $(TEST_PATH)/%.c, $(TEST_PATH)/bin/%, $(TESTS))

LIBFT_A = $(LIBS_PATH)libft.a 
SOURCES = $(addprefix $(SRCS_PATH), $(SRC_FILES))
OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES))
OBJECTS = $(addprefix $(OBJS_PATH), $(OBJ_FILES))
OBJECTS_TEST = $(filter-out ./objs/main.o, $(OBJECTS))


all: $(NAME)


$(LIBFT_A):
	@cd $(LIBS_PATH) && $(MAKE_NOPRINT)
	
$(NAME): $(LIBFT_A) $(OBJECTS) 
	@$(CC) -o $(NAME) $(OBJECTS) $(LIBFT_A) -lreadline

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@$(MKDIR) $(OBJS_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(TEST_PATH)/bin/%: $(TEST_PATH)/%.c
	@$(CC) $< $(OBJECTS_TEST) -o $@  -lcriterion
	
$(TEST_PATH)/bin:
	@$(MKDIR) $@

test: $(NAME) $(TEST_PATH)/bin $(TESTBINS)
	@for test in $(TESTBINS) ; do ./$$test --verbose ; done

bonus: all

run: $(NAME)
	@$(NAME) $(MAP)

valgrind: $(NAME)
	@$(VALGRIND) $(NAME) $(MAP)

clean:
	@$(RM) objs test/bin
	@$(MAKE_NOPRINT) clean -C $(LIBS_PATH)


fclean: clean
	@$(RM) $(NAME)
	@$(MAKE_NOPRINT) fclean -C $(LIBS_PATH)

re: fclean all

.PHONY: all run clean fclean re 