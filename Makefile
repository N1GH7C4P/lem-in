#Variables

NAME					= lem-in
INCLUDE					= -I include
LIBFT_LIB				= -L ./libft -lft
LIBFT					= libft
SRC_DIR					= src/
OBJ_DIR					= src/
TEST_DIR				= test/
TEST_EXE				= run_test
CC						= gcc
CFLAGS					= -Wall -Wextra -O3 -Werror
RM						= rm -f

# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

LEMIN_SRC_FILES	= main graph utils node parser edge bfs queue path error ant \
edge_parser output node_parser
TEST_FILES	=	*

LEMIN_SRC 	= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(LEMIN_SRC_FILES)))
LEMIN_OBJ 	= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(LEMIN_SRC_FILES)))
TEST 		= 	$(addprefix $(TEST_DIR), $(addsuffix .test.c, $(TEST_FILES)))

all:			$(NAME)

$(NAME):		$(LEMIN_SRC)
				@make -C $(LIBFT)
				${CC} $(CFLAGS) $(INCLUDE) $(LIBFT_LIB) $(LEMIN_SRC) -o $(NAME)
				@echo "$(GREEN)lemin compiled!$(DEF_COLOR)"


clean:
				@$(RM) -rf $(LEMIN_OBJ)
				@echo "$(BLUE) push_swap object files cleaned!$(DEF_COLOR)"
				@$(RM) -rf $(LEMIN_OBJ)
				@echo "$(BLUE) lemin object files cleaned!$(DEF_COLOR)"
				@make clean -C $(LIBFT)
				@echo "$(BLUE)libft object files cleaned!$(DEF_COLOR)"

fclean:			clean
				@$(RM) -f $(NAME)
				@echo "$(CYAN)lemin binary files cleaned!$(DEF_COLOR)"
				@make clean -C $(LIBFT)
				@$(RM) -f $(LIBFT)/libft.a
				@echo "$(CYAN)libft binary files cleaned!$(DEF_COLOR)"

re:				fclean all
				@echo "$(GREEN)Rebuilt all!$(DEF_COLOR)"

visualize:		all
				sh ./lem-in_visualizer/run_visualizer.sh
visualize_rand:	all
				sh ./lem-in_visualizer/visualize_random.sh
			
.PHONY:			all clean fclean rean fclean re