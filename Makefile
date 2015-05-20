# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zion <zion@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/26 13:13:47 by rbenjami          #+#    #+#              #
#    Updated: 2015/05/20 21:07:29 by zion             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

export	CC		=	cc

INC				=	-I $(LIBS_DIR)/libft

NAME			=	scop

CFLAGS			=	-Wall -Wextra -Werror -O3 -g -pedantic

INC				+=	-I includes

HEAD			=	includes/$(NAME).h

SRC_DIR			=	srcs/

FILES			=	$(NAME).c

SRC				=	$(addprefix $(SRC_DIR)/, $(FILES))

OBJ				=	$(SRC:.c=.o)

LIBS_DIR		=	libs
LIB				=	-L./$(LIBS_DIR)/libft -lft -lglfw3 -lGL -L/usr/X11/lib -lX11 -lpthread -lXxf86vm -lm -lXrandr -lXcursor -lXinerama -lXi
include			$(LIBS_DIR)/libft/Makefile.sources
OBJ_LIBFT		=	$($(LIBS_DIR)/libft/SRC_LIB:.c=.o)
HEAD_LIBFT		=	$(LIBS_DIR)/libft/libft.h \
					$(LIBS_DIR)/libft/get_next_line.h

all:			$(LIBS_DIR)/libft/libft.a $(NAME)

$(LIBS_DIR)/libft/libft.a:		$(OBJ_LIBFT) $(HEAD_LIBFT)
	@make -C $(LIBS_DIR)/libft

$(NAME):		$(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)
	@printf "\n\033[33mCompilation of %s: \033[32mSuccess \t\
			\033[34m[\033[32m✔\033[34m]\033[0m\n" $(NAME)

$(OBJ):			$(HEAD)

%.o:			%.c $(HEAD)
	@echo -n .
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	@/bin/rm -f $(OBJ)
	@echo "\033[31m"Objects of $(NAME) : deleted"\033[0m"

fclean:			clean
	@/bin/rm -f $(NAME)
	@echo "\033[31m"$(NAME) : deleted"\033[0m"
	@make fclean -C $(LIBS_DIR)/libft
re:				fclean all

.PHONY:			all clean fclean re
