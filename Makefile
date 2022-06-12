# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 11:40:15 by fkhan             #+#    #+#              #
#    Updated: 2022/06/12 16:59:05 by fkhan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER   		= server
CLIENT   		= client
LIBFTPRINTF		= libftprintf.a
PRINTFPATH		= lib
CC				= gcc
CFLAGS			= -Wall -Werror -Wextra
LIB 			= ar -rcs
RM				= rm -f

SRCS 			= server.c client.c \

OBJS		 	= $(SRCS:.c=.o)

$(SERVER): 		server.o
				make -C $(PRINTFPATH)
				$(CC) server.o $(PRINTFPATH)/$(LIBFTPRINTF) -o $(SERVER)
				@printf "\e[38;5;46m./$@ successfully build\e[0m\n"

$(CLIENT): 		client.o
				make -C $(PRINTFPATH)
				$(CC) client.o $(PRINTFPATH)/$(LIBFTPRINTF) -o $(CLIENT)
				@printf "\e[38;5;46m./$@ successfully build\e[0m\n"

%.o: 			%.c
				$(CC) $(CFLAGS) -c $< -o $@ -I includes

all: 			$(SERVER) $(CLIENT)

bonus:			all

clean:	 		
				$(RM) $(OBJS)
				make clean -C $(PRINTFPATH)

fclean: 		clean
				$(RM) $(SERVER)
				$(RM) $(CLIENT)
				$(RM) $(PRINTFPATH)/$(LIBFTPRINTF)

re: 			fclean all

.PHONY: 		all bonus clean fclean re