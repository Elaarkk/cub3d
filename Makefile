NAME = cub3D
CC = cc
DEPFLAGS = -MP -MD
RM = rm -rf

MLX_GIT = https://github.com/42paris/minilibx-linux.git
MLXDIR = minilibx-linux
MLX = $(MLXDIR)/libmlx.a

INC = ./includes/

SRCS = ./sources/main.c ./sources/parsing/parsing.c ./sources/parsing/utils_parsing.c \
        ./sources/utils/utils.c ./sources/parsing/get_next_line_utils.c ./sources/parsing/get_next_line.c \
        ./sources//utils/utils2.c ./sources/parsing/get_textures.c ./sources/parsing/get_map.c \
        ./sources/parsing/check_map.c ./sources/parsing/check_textures.c ./sources/engine/raycasting.c \
        ./sources/engine/mlx_utils.c ./sources/engine/loop.c ./sources/engine/raycast_maths.c ./sources/engine/minimap.c \
        ./sources/engine/render_textures.c ./sources/utils/utils3.c ./sources/engine/keyhook.c ./sources/engine/movements.c
        

OBJDIR = ./obj

OBJS = $(addprefix $(OBJDIR)/,$(patsubst %.c,%.o,$(SRCS)))

DEP = $(OBJ:.o=.d)

FLAGS = -Wall -Wextra -Werror -I$(INC) -I$(MLXDIR) -g3
MLXFLAGS = -L$(MLXDIR) -lmlx -lXext -lX11 -lm

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m

all : $(MLX) $(NAME)

$(MLX):
	@if [ ! -d "$(MLXDIR)" ]; then \
		echo "$(YELLOW)Cloning MiniLibX...$(DEFAULT)" ; \
		git clone $(MLX_GIT) $(MLXDIR) ; \
	else \
		echo "$(GREEN)MiniLibX directory already exists.$(DEFAULT)" ; \
	fi
	@echo "$(YELLOW)Compiling MiniLibX...$(DEFAULT)"
	@$(MAKE) -C $(MLXDIR)
	@echo "$(GREEN)MiniLibX compiled!$(DEFAULT)"

$(OBJDIR)/%.o : %.c
	mkdir -p $(@D)
	$(CC) $(FLAGS) $(DEPFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(MLXFLAGS)
	@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJDIR)
	@if [ -d "$(MLXDIR)" ]; then $(MAKE) -C $(MLXDIR) clean; fi
	@echo "$(YELLOW)object files deleted.$(DEFAULT)"

fclean : clean
	$(RM) $(NAME)
	$(RM) -r $(MLXDIR)
	@echo "$(RED)all files deleted.$(DEFAULT)"

re : fclean all

.PHONY:
		cub3D all clean fclean bonus re