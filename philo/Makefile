# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afahs <afahs@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/08 16:00:48 by afahs             #+#    #+#              #
#    Updated: 2025/09/10 08:08:08 by afahs            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[0;33m
CYAN	= \033[0;36m
PURPLE	= \033[0;35m
RESET	= \033[0m

# Project
NAME		= philo
SRCDIR		= src
INCDIR		= inc
OBJDIR		= obj

SRCFILES	= main.c parsing.c init.c simulation.c monitor.c utils.c cleanup.c
SRCS		= $(addprefix $(SRCDIR)/, $(SRCFILES))
OBJS		= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

HEADER		= $(INCDIR)/philo.h

# Compiler
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread -I$(INCDIR)
RM		= rm -f

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(CYAN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ Build successful!$(RESET)"

# Compile objects into obj/
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@$(RM) -r $(OBJDIR)
	@echo "$(GREEN)✓ Clean completed!$(RESET)"

fclean: clean
	@echo "$(RED)Removing executable...$(RESET)"
	@$(RM) $(NAME)
	@echo "$(GREEN)✓ Full clean completed!$(RESET)"

re: fclean all

norm:
	@echo "$(PURPLE)Checking Norminette...$(RESET)"
	@norminette $(SRCDIR) $(INCDIR) || true

.PHONY: all clean fclean re norm