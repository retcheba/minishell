SRCS		= main.c ft_tag_word.c what_to_execute.c get_cmd_path.c \
				parsing/parsing.c parsing/ft_split_minishell.c \
				builtins/ft_prepare_builtins.c builtins/pwd.c \
				execute_one_cmd/execute_one_cmd.c execute_one_cmd/ft_prepare_one_cmd.c \
				pipex/ft_prepare_pipex.c pipex/execute_cmds_multipipe.c pipex/pipex_error.c pipex/pipex_utils.c pipex/chained_list_pipex.c \
				utils/heredoc.c utils/chained_list.c utils/minishell_utils.c
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
