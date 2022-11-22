SRCS		= main.c ft_tag_word.c what_to_execute.c get_cmd_path.c signal.c \
				parsing/parsing.c parsing/ft_split_minishell.c parsing/ft_substr_minishell.c parsing/replace_env_equivalent.c \
				builtins/ft_prepare_builtins.c builtins/pwd/pwd.c builtins/env/env.c builtins/unset/unset.c\
				builtins/export/export.c builtins/export/utils_export.c builtins/export/check_export_args.c \
				simple_cmd/simple_cmd.c simple_cmd/ft_prepare_simple_cmd.c \
				pipex/prepare_pipex.c pipex/ft_prepare_one_cmd.c pipex/pipex.c pipex/first_cmd.c pipex/even_cmd.c pipex/odd_cmd.c pipex/last_cmd.c \
				pipex/pipex_error.c pipex/pipex_utils.c pipex/chained_list_pipex.c \
				utils/heredoc.c utils/chained_list.c utils/minishell_utils.c utils/minishell_utils2.c
OBJS		= $(addprefix srcs/, $(SRCS:.c=.o))
CC			= clang
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
			@echo "\033[1;92m# ************************ #\033[0m"
			@echo "\033[1;92m#                          #\033[0m"
			@echo "\033[1;92m#      make completed      #\033[0m"
			@echo "\033[1;92m#                          #\033[0m"
			@echo "\033[1;92m# ************************ #\033[0m"

clean:
			@$(RM) $(OBJS)
			@make -s fclean -C libft/
			@echo "\033[1;93m# ************************ #\033[0m"
			@echo "\033[1;93m#                          #\033[0m"
			@echo "\033[1;93m#   make clean completed   #\033[0m"
			@echo "\033[1;93m#                          #\033[0m"
			@echo "\033[1;93m# ************************ #\033[0m"

fclean:		clean
			@$(RM) $(NAME)
			@echo "\033[1;91m# ************************ #\033[0m"
			@echo "\033[1;91m#                          #\033[0m"
			@echo "\033[1;91m#  make fclean completed   #\033[0m"
			@echo "\033[1;91m#                          #\033[0m"
			@echo "\033[1;91m# ************************ #\033[0m"

re:			fclean all

.PHONY:		all clean fclean re
