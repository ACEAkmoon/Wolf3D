# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akrushin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/25 16:23:08 by akrushin          #+#    #+#              #
#    Updated: 2018/08/25 16:23:09 by akrushin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= wolf3d

NOC			= \033[0m
OKC			= \033[32m
ERC			= \033[31m
WAC			= \033[33m
TSC			= \033[94;1m

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
FRAMWRKS 	= -lmlx -framework OpenGL -framework AppKit

INC_PATH	= ./includes/
LFT_PATH	= ./includes/libft/
MLX_PATH	= ./includes/minilibx/
OBJ_PATH	= ./objects/
SRC_PATH	= ./resources/

OBJECTS		= $(RESOURCES:.c=.o)
RESOURCES	= main.c reader.c canvas.c color.c input.c output.c threads.c cleaner.c calculate.c

INC_PFIX	= $(addprefix -I,$(INC_PATH))
OBJ_PFIX	= $(addprefix $(OBJ_PATH),$(OBJECTS))
SRC_PFIX	= $(addprefix $(SRC_PATH),$(RESOURCES))

all: $(NAME)

$(NAME): $(OBJ_PFIX)
	@echo
	@make -C $(LFT_PATH)
	@make -C $(MLX_PATH)
	@$(CC) -o $(NAME) $(OBJ_PFIX) -lm -L $(LFT_PATH) -L $(MLX_PATH) -lft $(FRAMWRKS)
	@echo "$(OKC)Wolf3d ready$(NOC)"


$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC_PFIX) -o $@ -c $<
	@echo -n =

clean:
	@make -C $(LFT_PATH) clean
	@make -C $(MLX_PATH) clean
	@rm -rf $(OBJ_PATH)
	@echo "$(WAC)Removing Wolf3d OBJECTS path$(NOC)"

fclean: clean
	@make -C $(LFT_PATH) fclean
	@make -C $(MLX_PATH) clean
	@rm -f $(NAME)
	@echo "$(WAC)Removing Wolf3d executable$(NOC)"

re: fclean 
	$(MAKE) all

.PHONY: all, $(NAME), clean, fclean, re
