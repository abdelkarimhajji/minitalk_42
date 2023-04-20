# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/20 00:35:56 by ahajji            #+#    #+#              #
#    Updated: 2023/04/20 00:54:43 by ahajji           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = client

NAME2 = server

SRC =  client.c

SRC2 =  ft_putnbr.c server.c

OBJ = $(SRC:.c=.o)

OBJ2 = $(SRC2:.c=.o)

all: $(NAME) $(NAME2)

$(NAME): $(OBJ)
	@cc	 $(OBJ)  -Wall -Wextra -Werror  -o $(NAME)

$(NAME2): $(OBJ2)
	@cc	 $(OBJ2)  -Wall -Wextra -Werror  -o $(NAME2)

clean:
	@rm -rf *.o

fclean:
	@rm -rf $(NAME) $(NAME2)

re: fclean all

.PHONY: all clean fclean re