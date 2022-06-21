# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 11:40:15 by fkhan             #+#    #+#              #
#    Updated: 2022/06/20 17:57:31 by fkhan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   				= minitalk
SERVER   			= server
CLIENT   			= client
CC 					= gcc
FLAGS 				= -Wall -Werror -Wextra
INCLUDES 			= -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) \
						-I$(FT_PRINTF_HEADERS)
LIBRARIES 			= -lft -lft_printf \
						-L$(LIBFT_DIRECTORY) -L$(FT_PRINTF_DIRECTORY)

LIB_DIRECTORY 		= ./lib/

LIBFT 				= $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY 	= $(LIB_DIRECTORY)libft/
LIBFT_HEADERS 		= $(LIBFT_DIRECTORY)includes/

FT_PRINTF			= $(FT_PRINTF_DIRECTORY)libft_printf.a
FT_PRINTF_DIRECTORY = $(LIB_DIRECTORY)ft_printf/
FT_PRINTF_HEADERS 	= $(FT_PRINTF_DIRECTORY)includes/

HEADERS_DIRECTORY 	= ./includes/
HEADERS_LIST 		= minitalk.h
HEADERS 			= $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY 	= ./sources/
SOURCES_LIST 		= server.c client.c
SOURCES 			= $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY 	= objects/
OBJECTS_LIST 		= $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS				= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# COLORS
GREEN 				= \033[0;32m
RED 				= \033[0;31m
RESET 				= \033[0m

all: $(SERVER) $(CLIENT)

bonus: all

$(SERVER): $(LIBFT) $(FT_PRINTF) $(OBJECTS_DIRECTORY) $(OBJECTS_DIRECTORY)server.o
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJECTS_DIRECTORY)server.o $(LIBRARIES) -o $(SERVER)
	@echo "\n$(CLIENT): $(GREEN)object files were created$(RESET)"
	@echo "$(CLIENT): $(GREEN)$(CLIENT) was created$(RESET)"

$(CLIENT): $(LIBFT) $(FT_PRINTF) $(OBJECTS_DIRECTORY) $(OBJECTS_DIRECTORY)client.o
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJECTS_DIRECTORY)client.o $(LIBRARIES) -o $(CLIENT)
	@echo "\n$(CLIENT): $(GREEN)object files were created$(RESET)"
	@echo "$(CLIENT): $(GREEN)$(CLIENT) was created$(RESET)"
	
$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo ".\c"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

$(FT_PRINTF):
	@echo "$(NAME): $(GREEN)Creating $(FT_PRINTF)...$(RESET)"
	@$(MAKE) -sC $(FT_PRINTF_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@$(MAKE) -sC $(FT_PRINTF_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(FT_PRINTF)
	@echo "$(NAME): $(RED)$(FT_PRINTF) was deleted$(RESET)"
	@rm -f $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(SERVER)
	@echo "$(NAME): $(RED)$(SERVER) was deleted$(RESET)"
	@rm -f $(CLIENT)
	@echo "$(NAME): $(RED)$(CLIENT) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all bonus clean fclean re