/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:13:48 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/10 16:57:07 by subrandt         ###   ########.fr       */
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
# include <limits.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/ioctl.h>

# define EXIT 0
# define CMD 1
# define ARG 2
# define FILE 3
# define PIPE 4
# define REDIR_IN 5
# define REDIR_OUT 6
# define DREDIR_IN 7
# define DREDIR_OUT 8
# define PATH 9
# define BUILTIN 10

extern int	g_status;

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
	char	**envp;
	t_list	*lst1;
	t_list	*env;
	t_list	*export;
	t_list	*free_list;
}	t_struct;

typedef struct s_pipex
{
	int		nb_cmds;
	int		**fd_ios;
	int		index;
	int		fds_pipe1[2];
	int		fds_pipe2[2];
	char	**cmd;
	char	*cmd_path;
	t_pid	*list;
}	t_pipex;

//	MAIN FUNCTIONS
void	ft_tag_word(t_struct *mini);
void	what_to_execute(t_struct *mini, char **envp);
char	*get_cmd_path(char *cmd, char **envp);
void	sig_handler(int sig);

//	PARSING FUNCTIONS
void	parsing(t_struct *mini, char **envp);
char	**ft_split_minishell(char const *s, char c);
char	*ft_substr_minishell(char const *s, unsigned int start, size_t len);
char	*replace_env_equivalent(t_struct *mini, char *str, char **envp);
size_t	ft_check_quotes(const char *s, size_t i);
size_t	ft_check_squotes(const char *s, size_t i);

//	PIPEX FUNCTIONS
void	ft_prepare_pipex(t_struct *mini, char **envp);
char	**ft_prepare_one_cmd(t_struct *mini);
void	ft_pipex(t_pipex *pipex, char ***cmd, char **envp, int *fd_ios[2]);
void	first_cmd(t_pipex *pipex, char ***cmds, char **envp, int fd_io[2]);
void	even_cmd(t_pipex *pipex, char ***cmds, char **envp, int fd_io[2]);
void	odd_cmd(t_pipex *pipex, char ***cmds, char **envp, int fd_io[2]);
void	last_cmd(t_pipex *pipex, char ***cmds, char **envp, int fd_io[2]);
int		check_cmd_pipex(t_pipex *pipex, char **envp);
void	ft_free_var(char *cmd_path, char **cmd);
void	ft_free_list_pipex(t_pid *list);
t_pid	*new_link_pipex(pid_t pid, int ok);
t_pid	*add_link_bottom_pipex(t_pid *list, t_pid *new);
t_pid	*add_link_top_pipex(t_pid *list, pid_t pid, int ok);

//	BUILTINS FUNCTIONS
void	ft_prepare_builtins(t_struct *mini);
//pwd
void	ft_pwd(void);
//env
void	ft_init_env(t_struct *mini, char **envp);
void	print_env(t_list *env);
//export
void	ft_init_export(t_struct *mini, char **envp);
void	print_export(t_list *export);
void	check_export_args(t_struct *mini, t_list *next);
//utils export
int		ft_strcmp(char *s1, char *s2);
void	ft_swap_content(t_list **list);
int		is_only_alpha(char *s);
void	ft_print_error(char *cast);
//unset
void	ft_unset(t_struct *mini, t_list *n);

//	SIMPLE CMD FUNCTIONS
int		ft_prepare_simple_cmd(t_struct *mini, char **envp);
void	simple_cmd(char **cmd, char **envp, int fd_io[2]);

//	CHAINED-LIST FUNCTIONS
t_list	*new_link(void *content, int tag);
t_list	*add_link_bottom(t_list *lst, t_list *new);
t_list	*add_link_top(t_list *lst, void *content, int tag);
void	ft_free_list(t_list *lst);
t_list	*ft_listlast(t_list *lst, int i);

//	UTILS FUNCTIONS
int		ft_heredoc(char *stop);
void	ft_free_tab(char **tab);
int		ft_strstr(char *str, char *to_find);
int		check_redir_out(t_struct *mini);
int		check_redir_in(t_struct *mini);
char	**ft_envp(t_struct *mini);
char	*check_empty_dollar(char *result, char *str);
int		is_numeric(char *num);
int		get_status(long long num);

#endif
