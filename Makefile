# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joivanau <joivanau@hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/13 13:45:23 by joivanau          #+#    #+#              #
#    Updated: 2021/12/14 16:10:36 by joivanau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c error_handling.c map.c output_map.c reading.c
OBJ = $(SRC:.c=.o)
CFLAGS = -c -Wall -Werror -Wextra
NAME = fillit
LIBFTPATH = libft/
all:
	@make -C $(LIBFTPATH)
	@gcc $(CFLAGS) $(SRC) -I $(LIBFTPATH)
	@gcc -o fillit $(OBJ) -L $(LIBFTPATH) -lft

clean:
	@rm -rf $(OBJ)
	@make -C libft/ clean
fclean: clean
	@rm -rf $(NAME)
	@make -C libft/ fclean
re: fclean all