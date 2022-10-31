/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:13:48 by retcheba          #+#    #+#             */
/*   Updated: 2022/10/25 16:42:48 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>

# define EXIT 0
# define CMD 1
# define ARG 2
# define FILE 3
# define PIPE 4
# define REDIR_IN 5
# define REDIR_OUT 6
# define DREDIR_IN 7
# define DREDIR_OUT 8
# define $ 9
# define BUILTIN 10

//	STRUCTS
typedef struct s_pid
{
	pid_t			pid;
	int				ok;
	struct s_pid	*next;
}	t_pid;

typedef struct s_struct
{
	char	*buff;
	char	**tab;
	t_list	*lst1;
}	t_struct;

typedef struct s_pipex
{
	int		nb_cmds;
	int		index;
	int		fds_pipe1[2];
	int		fds_pipe2[2];
	char	**cmd;
	char	*cmd_path;
	t_pid		*list;
}	t_pipex;

//	MAIN FUNCTIONS
void	ft_tag_word(t_struct *mini);
void	what_to_execute(t_struct *mini, char **envp);
char	*get_cmd_path(char *cmd, char **envp);

//	PARSING FUNCTIONS
void	parsing(t_struct *mini);
char	**ft_split_minishell(char const *s, char c);

//	PIPEX FUNCTIONS
void	ft_prepare_pipex(t_struct *mini, char **envp);
void	ft_execute_cmds_multipipe(t_pipex *pipex, char ***cmd, char **envp, int *fd_ios[2]);
int		check_cmd(t_pipex *pipex, char **envp);
void	ft_free_var(char *cmd_path, char **cmd);
t_pid	*new_link_pipex(pid_t pid, int ok);
t_pid	*add_link_bottom_pipex(t_pid *list, t_pid *new);
t_pid	*add_link_top_pipex(t_pid *list, pid_t pid, int ok);
void	ft_free_list_pipex(t_pid *list);

//	BUILTINS FUNCTIONS
void	ft_prepare_builtins(t_struct *mini, char **envp);
void	ft_pwd(void);

//	EXECUTE FUNCTIONS
int	ft_prepare_one_cmd(t_struct *mini, char **envp);
void	ft_execute_one_cmd(char **cmd, char **envp, int fd_in, int fd_out);

//	CHAINED-LIST FUNCTIONS
t_list	*new_link(void *content, int tag);
t_list	*add_link_bottom(t_list *lst, t_list *new);
t_list	*add_link_top(t_list *lst, void *content, int tag);
void	ft_free_list(t_list *lst);

//	UTILS FUNCTIONS
void	ft_free_tab(char **tab);
int	ft_strstr(char *str, char * to_find);

#endif
