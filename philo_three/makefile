# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 15:34:08 by jacens            #+#    #+#              #
#    Updated: 2020/03/09 06:10:10 by jacens           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
#                                VARIABLES                                     #
# **************************************************************************** #

HEADER		=			philo.h

SRC_PATH	=			.

SRCS_NAME	=			ft_atoi.c ft_checkeat.c ft_checkfork.c ft_parent.c\
						ft_parse.c ft_sleep.c ft_strjoinrem.c main.c

OBJS        =			${SRCS:.c=.o}

NAME		=			philo_three

RM			=			rm -f

FLAGS		=			-g3 -fsanitize=address -Wall -Wextra -Werror

SRCS		=			$(addprefix $(SRC_PATH)/,$(SRCS_NAME))

# **************************************************************************** #
#                                REGLES                                        #
# **************************************************************************** #

all:                            $(NAME)

bonus: all

%.o: %.c                         $(HEADER)
						@echo "\033[0;32m[OK] \033[0m \033[0;33m Compiling:\033[0m" $<
						@gcc $(FLAGS) -I $(HEADER) -c $< -o $@

$(NAME):				$(OBJS) $(HEADER)
						@gcc $(OBJS) $(FLAGS) -o $(NAME) -lm
						@echo "\x1b[36m\n[OK] \033[0m \x1b[35m Compiling philo_three\033[0m"				


clean:
								@echo "\x1b[36m[OK] \033[0m \x1b[34m Removing ALL File object\033[0m"
								@$(RM) $(OBJS)

fclean:                         clean
								@echo "\x1b[36m[OK] \033[0m \x1b[32m All is Removing\033[0m"
								@$(RM) $(NAME)

re:                                fclean all

.PHONY:                         clean fclean
