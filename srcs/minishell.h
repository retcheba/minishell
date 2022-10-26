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

# define EXIT 0
# define CMD 1
# define OPTION 2
# define ARG 3
# define FILE 4
# define PIPE 5
# define REDIR_IN 6
# define REDIR_OUT 7
# define DREDIR_IN 8
# define DREDIR_OUT 9
# define $ 10

//	STRUCTS
typedef struct s_struct
{
	char	*buff;
	char	**tab;
	t_list	*lst1;
}	t_struct;

//	MAIN FUNCTIONS
void	parsing(t_struct *mini);
char	**ft_split_minishell(char const *s, char c);
void	ft_tag_word(t_struct *mini);

//	CHAINED-LIST FUNCTIONS
t_list	*new_link(void *content, int tag);
t_list	*add_link_bottom(t_list *lst, t_list *new);
t_list	*add_link_top(t_list *lst, void *content, int tag);
void	ft_free_list(t_list *lst);

//	UTILS FUNCTIONS
void	ft_free_var(char **tab);
int	ft_strstr(char *str, char * to_find);

#endif
