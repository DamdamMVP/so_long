# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 13:14:31 by dalebran          #+#    #+#              #
#    Updated: 2024/11/02 21:49:09 by dalebran         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

# COMPILER SETTINGS
CC = cc
CFLAGS = -Wall -Wextra -Werror

# FOLDERS
LIBFT_DIR = libft
MLX = minilibx
INC_DIR = inc
OBJ_DIR = obj
SRC_DIR = src

# COLORS
COLOR_DEFAULT = \033[39m\033[49m
COLOR_COMP = \033[92m
COLOR_REMOVE = \033[91m
COLOR_CREATED = \033[94m

# SRCS & OBJS
SRC_FILES = main is_valid_map can_be_finish inits handle_assets draw key_actions
SRC = $(addsuffix .c, $(SRC_FILES))
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJS = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRCS:.c=.o))

# LIBS
LIBFT = $(LIBFT_DIR)/libft.a
LIBMLX = $(MLX)/libmlx42.a
LIBS = $(LIBFT) $(LIBMLX) -lglfw -pthread -lm

# INCLUDES
INC_CUR = $(INC_DIR)
INC_LIBFT = $(LIBFT_DIR)/$(INC_DIR)
INC_MLX42 = $(MLX)/include
INCS = -I $(INC_CUR) -I $(INC_LIBFT) -I $(INC_MLX42)

all: $(LIBFT) $(LIBMLX) $(NAME)
	@echo "$(COLOR_CREATED)$(NAME) created$(COLOR_DEFAULT)"

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(COLOR_DEFAULT)Creation of executable $(NAME)..."
	@$(CC) $(CFLAGS) $(INCS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBMLX): $(MLX)
	@echo "Compitation of MLX42 library..."
	@$(MAKE) -s -C $(MLX)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(COLOR_COMP)	-> Compilation of $<..."
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(LIBFT):
	@echo "$(COLOR_DEFAULT)Compilation of Libft library..."
	@$(MAKE) -s -C $(LIBFT_DIR)

$(MLX):
	@echo "$(COLOR_DEFAULT)Clonage de MLX42 library... Thx to kodokaii"
	@git clone --depth=1 https://github.com/kodokaii/MLX42.git $(MLX)
	@echo "$(COLOR_DEFAULT)Compilation of MLX42 library..."
	@cmake $(MLX) -B $(MLX)

clean:
	@echo "$(COLOR_REMOVE)Cleaning of objects..."
	@rm -f $(OBJS)
	@rm -f $(OBJS_BONUS)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR_BONUS)
	@$(MAKE) -s -C $(MLX) clean
	@$(MAKE) -s -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(COLOR_REMOVE)Cleaning of library files..."
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@rm -rf $(MLX)
	@rm -f $(LIBMLX)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all

test: all
	@echo "$(COLOR_COMP)Compilation & test of $(NAME) with valgrind...$(COLOR_DEFAULT)"
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(filter-out $@,$(MAKECMDGOALS))

norminette:
	@echo "Norminette de $(NAME) et $(LIBFT_DIR)..."
	@if norminette $(SRC_DIR)/ $(SRC_DIR_BONUS)/ $(INC_DIR)/ $(LIBFT_DIR)/$(SRC_DIR)/ $(LIBFT_DIR)/$(INC_DIR)/ | grep -v "OK!" | grep -q "Error!"; then \
		norminette $(SRC_DIR)/ $(SRC_DIR_BONUS)/ $(INC_DIR)/ $(LIBFT_DIR)/$(SRC_DIR)/ $(LIBFT_DIR)/$(INC_DIR)/ | grep -v "OK!" | \
		while read line; do \
			if echo $$line | grep -q "Error!"; then \
				echo "\033[0;31m$$line\033[0m"; \
			else \
				echo "$$line"; \
			fi; \
		done; \
	else \
		echo "\033[0;32mAll files are norminette friendly !\033[0m"; \
	fi

# ========================= BONUS PART ============================

NAME_BONUS = demineur
SRC_DIR_BONUS = src_bonus
OBJ_DIR_BONUS = obj_bonus
SRC_FILES_BONUS = main is_valid_map can_be_finish inits handle_assets draw key_actions utils updates
SRC_BONUS = $(addsuffix .c, $(SRC_FILES_BONUS))
SRCS_BONUS = $(addprefix $(SRC_DIR_BONUS)/, $(SRC_BONUS))
OBJS_BONUS = $(patsubst $(SRC_DIR_BONUS)/%, $(OBJ_DIR_BONUS)/%, $(SRCS_BONUS:.c=.o))

bonus: $(LIBFT) $(LIBMLX) $(NAME_BONUS)
	@echo "$(NAME_BONUS) created"

test_bonus: re bonus
	@echo "Compilation & test of $(NAME_BONUS) with valgrind..."
	@valgrind ./$(NAME_BONUS).a

$(NAME_BONUS): $(OBJS_BONUS)
	@echo "Creation of executable $(NAME_BONUS)..."
	@$(CC) $(CFLAGS) $(INCS) $(OBJS_BONUS) $(LIBS) -o $(NAME_BONUS)
	
$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c
	@mkdir -p $(OBJ_DIR_BONUS)
	@echo "Compilation of $<..."
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

.PHONY: all clean fclean re test bonus norminette
