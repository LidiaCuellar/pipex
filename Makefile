# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcuellar <lcuellar@student42.madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/05 16:07:12 by lcuellar          #+#    #+#              #
#    Updated: 2024/04/05 17:58:00 by lcuellar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
LIBFT = ./libft/libft.a
CFLAGS = -Wall -Werror -Wextra 

OBJECTS_FOLDER = ./obj/

MANDATORY_FOLDER = ./mandatory/
MANDATORY_SOURCES = $(addprefix $(MANDATORY_FOLDER), pipex.c helper.c)
MANDATORY_OBJECTS = $(subst $(MANDATORY_FOLDER),$(OBJECTS_FOLDER),$(MANDATORY_SOURCES:.c=.o))

all: $(OBJECTS_FOLDER) $(NAME)

$(OBJECTS_FOLDER):
	mkdir $(OBJECTS_FOLDER)

$(NAME): $(LIBFT) $(MANDATORY_OBJECTS)
	cc $(CFLAGS) $(MANDATORY_OBJECTS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft

$(OBJECTS_FOLDER)%.o: $(MANDATORY_FOLDER)%.c $(MANDATORY_FOLDER)pipex.h
	cc $(CFLAGS) -c $< -o $@
	
clean:
	rm -rf $(OBJECTS_FOLDER)*
	rm -r $(OBJECTS_FOLDER)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all