# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/24 19:53:29 by yufukuya          #+#    #+#              #
#    Updated: 2020/10/04 14:14:39 by yufukuya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3d
CC := gcc
CFLAGS := -g -Wall -Werror -Wextra

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	PLATFORM := LINUX
endif
ifeq ($(UNAME_S),Darwin)
	PLATFORM := MACOS
endif

ifeq ($(PLATFORM),LINUX)
LIBS := -L. -I/usr/local/include -L/usr/local/lib -L./minilibx-linux -lmlx_Linux -lX11 -lXext -lm -lbsd
MINILIBX_DIR := minilibx-linux
MINILIBX := libmlx_Linux.a
RUN_SCRIPT := run_mlx_linux.sh
endif

ifeq ($(PLATFORM),MACOS)
LIBS := libmlx.dylib -framework OpenGL -framework Appkit
MINILIBX_DIR := minilibx
MINILIBX := libmlx.dylib
RUN_SCRIPT := run_mlx_macos.sh
endif

INCLUDES := includes
SRCS := ${shell find ./srcs/ -type f -name "*.c"}
OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

$(OBJS): %.o: %.c
	$(CC) -c $(CFLAGS) -I. -I$(INCLUDES) -I$(LIBFT_DIR) -I$(MINILIBX_DIR) $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)
	make -C $(LIBFT_DIR) bonus

$(MINILIBX):
	make -C $(MINILIBX_DIR)
	cp $(MINILIBX_DIR)/$(MINILIBX) .

.PHONY: all clean fclean re

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(MINILIBX)
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MINILIBX_DIR)

re: fclean all

norm:
	norminette srcs/*.c includes/*.h

find:
	find ./srcs -name *.c
