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
typedef struct s_struct
{
	char	*buff;
	char	**tab;
	t_list	*lst1;
}	t_struct;

//	MAIN FUNCTIONS
void	ft_tag_word(t_struct *mini);
void	what_to_execute(t_struct *mini, char **envp);

//	PARSING FUNCTIONS
void	parsing(t_struct *mini);
char	**ft_split_minishell(char const *s, char c);

//	BUILTINS FUNCTIONS
void	ft_prepare_builtins(t_struct *mini, char **envp);
void	ft_pwd(void);

//	EXECUTE FUNCTIONS
int	ft_prepare_one_cmd(t_struct *mini, char **envp);
void	ft_execute_one_cmd(char **cmd, char **envp);
char	*get_cmd_path(char *cmd, char **envp);

//	CHAINED-LIST FUNCTIONS
t_list	*new_link(void *content, int tag);
t_list	*add_link_bottom(t_list *lst, t_list *new);
t_list	*add_link_top(t_list *lst, void *content, int tag);
void	ft_free_list(t_list *lst);

//	UTILS FUNCTIONS
void	ft_free_tab(char **tab);
int	ft_strstr(char *str, char * to_find);

#endif
