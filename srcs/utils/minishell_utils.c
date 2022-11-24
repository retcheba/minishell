/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:40:11 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/06 05:20:39 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	if (tab)
		free(tab);
	tab = NULL;
}

int	ft_strstr(char *str, char *to_find)
{
	int	i;

	if (str == NULL || to_find == NULL)
		return (0);
	i = 0;
	while (str[i] && to_find[i] && str[i] == to_find[i])
		i++;
	if (str[i] == '\0' && to_find[i] == '\0')
		return (1);
	return (0);
}

void	check_redirs(t_struct *mini, int *error, int *fd_in, int *fd_out)
{
	t_list	*begin;

	begin = mini->lst1;
	while (mini->lst1 && mini->lst1->tag != PIPE)
	{
		if (mini->lst1->tag == REDIR_IN && mini->lst1->next
			&& mini->lst1->next->tag == FILE)
		{
			*fd_in = open(mini->lst1->next->content, O_RDONLY);
			if (*fd_in == -1 && *error != 1)
			{
				ft_putstr_fd(mini->lst1->next->content, 2);
				ft_putstr_fd(": ", 2);
				perror("");
				*error = 1;
			}
		}
		if (mini->lst1->tag == DREDIR_IN && mini->lst1->next->tag == FILE)
			*fd_in = ft_heredoc(mini->lst1->next->content);
		if (mini->lst1->tag == REDIR_OUT && mini->lst1->next->tag == FILE && *error != 1)
		{
			*fd_out = open(mini->lst1->next->content, O_WRONLY | O_TRUNC \
				| O_CREAT, 0644);
			if (*fd_out == -1 && *error != 1)
			{
				ft_putstr_fd(mini->lst1->next->content, 2);
				ft_putstr_fd(": ", 2);
				perror("");
				*error = 1;
			}
		}
		if (mini->lst1->tag == DREDIR_OUT && mini->lst1->next->tag == FILE && *error != 1)
		{
			*fd_out = open(mini->lst1->next->content, O_WRONLY | O_APPEND \
				| O_CREAT, 0644);
			if (*fd_out == -1 && *error != 1)
			{
				ft_putstr_fd(mini->lst1->next->content, 2);
				ft_putstr_fd(": ", 2);
				perror("");
				*error = 1;
			}
		}
		mini->lst1 = mini->lst1->next;
	}
	mini->lst1 = begin;
}

char	**ft_envp(t_struct *mini)
{
	t_list	*begin;
	int		i;

	if (mini->envp != NULL)
		ft_free_tab(mini->envp);
	i = 0;
	begin = mini->env;
	while (mini->env)
	{
		i++;
		mini->env = mini->env->next;
	}
	mini->env = begin;
	mini->envp = malloc(sizeof(char *) * (i + 1));
	mini->envp[i] = NULL;
	i = 0;
	while (mini->env)
	{
		mini->envp[i] = ft_strdup(mini->env->content);
		i++;
		mini->env = mini->env->next;
	}
	mini->env = begin;
	return (mini->envp);
}
