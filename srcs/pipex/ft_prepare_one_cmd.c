/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_one_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:33:23 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/08 20:34:22 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_len_cmd(t_struct *mini)
{
	t_list	*begin;
	int		len;

	len = 0;
	begin = mini->lst1;
	while (mini->lst1 && mini->lst1->tag != PIPE)
	{
		if (mini->lst1->tag == CMD || mini->lst1->tag == BUILTIN)
		{
			len++;
			mini->lst1 = mini->lst1->next;
			while (mini->lst1 && mini->lst1->tag != PIPE)
			{
				if (mini->lst1->tag == ARG)
					len++;
				mini->lst1 = mini->lst1->next;
			}
			break ;
		}
		mini->lst1 = mini->lst1->next;
	}
	mini->lst1 = begin;
	return (len);
}

static char	**fill_tab_cmd(t_struct *mini, char **cmd)
{
	t_list	*begin;
	int		len;

	len = 0;
	begin = mini->lst1;
	while (mini->lst1 && mini->lst1->tag != PIPE)
	{
		if (mini->lst1->tag == CMD || mini->lst1->tag == BUILTIN)
		{
			cmd[len] = ft_substr(mini->lst1->content, 0, \
				ft_strlen(mini->lst1->content));
			mini->lst1 = mini->lst1->next;
			while (mini->lst1 && mini->lst1->tag != PIPE)
			{
				if (mini->lst1->tag == ARG)
				{
					len++;
					cmd[len] = ft_substr(mini->lst1->content, 0, \
						ft_strlen(mini->lst1->content));
				}
				mini->lst1 = mini->lst1->next;
			}
			break ;
		}
		mini->lst1 = mini->lst1->next;
	}
	mini->lst1 = begin;
	return (cmd);
}

char	**ft_prepare_one_cmd(t_struct *mini)
{
	char	**cmd;
	int		len;

	len = ft_len_cmd(mini);
	cmd = malloc(sizeof(char *) * (len + 1));
	if (!cmd)
		return (NULL);
	cmd[len] = NULL;
	cmd = fill_tab_cmd(mini, cmd);
	return (cmd);
}
