# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afahs <afahs@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/08 16:00:48 by afahs             #+#    #+#              #
#    Updated: 2025/09/08 16:02:12 by afahs            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[0;33m
BLUE	= \033[0;34m
PURPLE	= \033[0;35m
CYAN	= \033[0;36m
WHITE	= \033[0;37m
RESET	= \033[0m

# Mandatory part
NAME		= philo
SRCDIR		= philo/
SRCFILES	= main.c parsing.c init.c simulation.c monitor.c utils.c cleanup.c
SRCS		= $(addprefix $(SRCDIR), $(SRCFILES))
OBJS		= $(SRCS:.c=.o)
HEADER		= $(SRCDIR)inc/philo.h

# Bonus part
NAME_BONUS	= philo_bonus
SRCDIR_BONUS = philo_bonus/
SRCFILES_BONUS = main_bonus.c parsing_bonus.c init_bonus.c simulation_bonus.c \
				utils_bonus.c cleanup_bonus.c
SRCS_BONUS	= $(addprefix $(SRCDIR_BONUS), $(SRCFILES_BONUS))
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)
HEADER_BONUS = $(SRCDIR_BONUS)inc/philo_bonus.h

# Compilation
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread
RM		= rm -f

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(CYAN)Compiling philosophers...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)✓ Philosophers compiled successfully!$(RESET)"

$(SRCDIR)%.o: $(SRCDIR)%.c $(HEADER)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	@echo "$(CYAN)Compiling philosophers bonus...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS)
	@echo "$(GREEN)✓ Philosophers bonus compiled successfully!$(RESET)"

$(SRCDIR_BONUS)%.o: $(SRCDIR_BONUS)%.c $(HEADER_BONUS)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@$(RM) $(OBJS) $(OBJS_BONUS)
	@echo "$(GREEN)✓ Clean completed!$(RESET)"

fclean: clean
	@echo "$(RED)Removing executables...$(RESET)"
	@$(RM) $(NAME) $(NAME_BONUS)
	@echo "$(GREEN)✓ Full clean completed!$(RESET)"

re: fclean all

norm:
	@echo "$(PURPLE)Checking Norminette...$(RESET)"
	@norminette $(SRCDIR) $(SRCDIR_BONUS) || true

test: $(NAME)
	@echo "$(BLUE)Running basic tests...$(RESET)"
	@echo "$(CYAN)Test 1: Single philosopher (should die)$(RESET)"
	@./$(NAME) 1 800 200 200
	@echo "\n$(CYAN)Test 2: Basic simulation$(RESET)"
	@timeout 10s ./$(NAME) 5 800 200 200 || echo "$(GREEN)Test completed$(RESET)"
	@echo "\n$(CYAN)Test 3: Meal limit test$(RESET)"
	@./$(NAME) 4 800 200 200 5

test_bonus: $(NAME_BONUS)
	@echo "$(BLUE)Running bonus tests...$(RESET)"
	@echo "$(CYAN)Test 1: Single philosopher bonus (should die)$(RESET)"
	@./$(NAME_BONUS) 1 800 200 200
	@echo "\n$(CYAN)Test 2: Basic bonus simulation$(RESET)"
	@timeout 10s ./$(NAME_BONUS) 5 800 200 200 || echo "$(GREEN)Test completed$(RESET)"
	@echo "\n$(CYAN)Test 3: Meal limit bonus test$(RESET)"
	@./$(NAME_BONUS) 4 800 200 200 5

leak_test: $(NAME)
	@echo "$(BLUE)Running valgrind leak test...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		--suppressions=.valgrind_ignore ./$(NAME) 4 800 200 200 5

thread_test: $(NAME)
	@echo "$(BLUE)Running helgrind thread test...$(RESET)"
	@valgrind --tool=helgrind --suppressions=.helgrind_ignore \
		./$(NAME) 4 800 200 200 5

help:
	@echo "$(PURPLE)Available targets:$(RESET)"
	@echo "  $(GREEN)all$(RESET)        - Compile mandatory part"
	@echo "  $(GREEN)bonus$(RESET)      - Compile bonus part"
	@echo "  $(GREEN)clean$(RESET)      - Remove object files"
	@echo "  $(GREEN)fclean$(RESET)     - Remove object files and executables"
	@echo "  $(GREEN)re$(RESET)         - Full recompile"
	@echo "  $(GREEN)norm$(RESET)       - Check norminette"
	@echo "  $(GREEN)test$(RESET)       - Run basic tests on mandatory"
	@echo "  $(GREEN)test_bonus$(RESET) - Run basic tests on bonus"
	@echo "  $(GREEN)leak_test$(RESET)  - Run valgrind memory leak test"
	@echo "  $(GREEN)thread_test$(RESET)- Run helgrind thread safety test"
	@echo "  $(GREEN)help$(RESET)       - Show this help"

.PHONY: all bonus clean fclean re norm test test_bonus leak_test thread_test help