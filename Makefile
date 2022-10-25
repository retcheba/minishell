SRCS		= main.c first_parsing.c ft_split_minishell.c ft_tag_word.c chained_list.c minishell_utils.c
OBJS		= $(addprefix srcs/, $(SRCS:.c=.o))
CC			= gcc
CFLAGS		= -g -Wall -Wextra -Werror
LFLAGS		= -lreadline 
NAME		= minishell
RM			= rm -f
LIBFT		= libft/libft.a

all:		$(NAME)

%.o: %.c
			@$(CC) $(CFLAGS) -c -o $@ $<

$(LIBFT):
			@make -s -C libft/

$(NAME): 	$(OBJS) $(LIBFT)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LFLAGS) -o $(NAME)
			@echo "\e[96m# ************************ #"
			@echo "\e[96m#                          #"
			@echo "\e[96m#      make completed      #"
			@echo "\e[96m#                          #"
			@echo "\e[96m# ************************ #"

clean:
			@$(RM) $(OBJS)
			@make -s fclean -C libft/
			@echo "\e[96m# ************************ #"
			@echo "\e[96m#                          #"
			@echo "\e[96m#   make clean completed   #"
			@echo "\e[96m#                          #"
			@echo "\e[96m# ************************ #"

fclean:		clean
			@$(RM) $(NAME)
			@echo "\e[96m# ************************ #"
			@echo "\e[96m#                          #"
			@echo "\e[96m#  make fclean completed   #"
			@echo "\e[96m#                          #"
			@echo "\e[96m# ************************ #"

re:			fclean all

.PHONY:		all clean fclean re
