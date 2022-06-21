# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 13:01:55 by fkhan             #+#    #+#              #
#    Updated: 2022/06/20 17:55:08 by fkhan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 				= libft_printf.a
CC 					= gcc
FLAGS 				= -Wall -Werror -Wextra
LIB					= ar -rcs
INCLUDES 			= -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS)

LIB_DIRECTORY 		= ../

LIBFT 				= $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY 	= $(LIB_DIRECTORY)libft/
LIBFT_HEADERS 		= $(LIBFT_DIRECTORY)includes/

HEADERS_DIRECTORY 	= ./includes/
HEADERS_LIST 		= ft_printf.h
HEADERS 			= $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY 	= ./sources/
SOURCES_LIST 		= ft_printf.c ft_printf_flags.c pf_putlchar_fd.c \
				  		pf_putlstr_fd.c pf_putlnbr_fd.c ft_digitlen.c \
				  		pf_putlhex_fd.c pf_putlunbr_fd.c pf_putlptr_fd.c \
				  		pf_width.c ft_puthex.c ft_hexlen.c
SOURCES 			= $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY 	= objects/
OBJECTS_LIST 		= $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS				= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# COLORS
GREEN 				= \033[0;32m
RED					= \033[0;31m
RESET 				= \033[0m

all: $(NAME)

$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS)
	@cp $(LIBFT) .
	@mv libft.a $(NAME)
	@$(LIB) $(NAME) $(OBJECTS)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo ".\c"

clean:
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re