/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 23:43:26 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/15 23:43:36 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_only_alpha_unset(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(s[i] >= 'A' && s[i] <= 'Z') && !(s[i] >= 'a' && s[i] <= 'z'))
			return (1);
		i++;
	}
	if (i == 0)
		return (1);
	return (0);
}

static t_list	*ft_remove_link(t_list **begin, t_list *current)
{
	t_list	*previous;

	if (ft_strstr(current->content, (*begin)->content))
	{
		previous = current->next;
		free(current);
		current = NULL;
		*begin = previous;
	}
	else
	{
		previous = *begin;
		while (!(ft_strstr(current->content, previous->next->content))
			&& previous)
			previous = previous->next;
		if (previous != NULL)
		{
			previous->next = current->next;
			free(current);
			current = NULL;
		}
	}
	return (previous);
}

static void	ft_remove_in_export(t_struct *mini, char *unset)
{
	t_list	*begin;
	char	*content;
	int		i;

	begin = mini->export;
	while (mini->export)
	{
		content = (char *)mini->export->content;
		i = 0;
		while (content[i] != '=' && content[i] && unset[i]
			&& content[i] == unset[i])
			i++;
		if ((content[i] == '=' && unset[i] == '\0')
			|| (content[i] == '\0' && unset[i] == '\0'))
			mini->export = ft_remove_link(&begin, mini->export);
		mini->export = mini->export->next;
	}
	mini->export = begin;
}

static void	ft_remove_in_env(t_struct *mini, char *unset)
{
	t_list	*begin;
	char	*content;
	int		i;

	begin = mini->env;
	while (mini->env)
	{
		content = (char *)mini->env->content;
		i = 0;
		while (content[i] != '=' && content[i] && unset[i]
			&& content[i] == unset[i])
			i++;
		if ((content[i] == '=' && unset[i] == '\0')
			|| (content[i] == '\0' && unset[i] == '\0'))
			mini->env = ft_remove_link(&begin, mini->env);
		mini->env = mini->env->next;
	}
	mini->env = begin;
}

void	ft_unset(t_struct *mini, char **cmd)
{
	int	i;
	int	error;

	error = 0;
	i = 1;
	while (cmd[i])
	{
		if (is_only_alpha_unset(cmd[i]))
		{
			ft_print_error(cmd[i]);
			error = 1;
		}
		else
		{
			ft_remove_in_export(mini, cmd[i]);
			ft_remove_in_env(mini, cmd[i]);
		}
		i++;
	}
	if (error != 1)
		g_status = 0;
}
