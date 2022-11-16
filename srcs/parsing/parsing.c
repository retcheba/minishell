/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:11:21 by retcheba          #+#    #+#             */
/*   Updated: 2022/10/26 16:11:25 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free_str(t_struct *mini, char *result, char *begin, char *end)
{
	if (mini->free_list == NULL)
		mini->free_list = new_link(result, 0);
	else
		mini->free_list = add_link_bottom(mini->free_list, new_link(result, 0));
	free(begin);
	begin = NULL;
	free(end);
	end = NULL;
}

static char	*ft_separate_pipe_and_redirections(t_struct *mini, char *str)
{
	char	*result;
	char	*tmp;
	char	*begin;
	char	*end;
	size_t	split;

	split = 0;
	while (str[split])
	{
		if ((str[split] == '|' || str[split] == '>' || str[split] == '<')
			&& str[split + 1] != ' ' && str[split + 1] != '>'
			&& str[split + 1] != '<' && str[split + 1] != '\0')
		{
			split++;
			tmp = ft_substr(str, 0, split);
			begin = ft_strjoin(tmp, " ");
			end = ft_substr(str, split, (ft_strlen(str) - split));
			result = ft_strjoin(begin, end);
			ft_free_str(mini, result, begin, end);
			free(tmp);
			tmp = NULL;
		}
		split++;
	}
	return (result);
}

void	parsing(t_struct *mini)
{
	int		i;

	mini->buff = ft_separate_pipe_and_redirections(mini, mini->buff);
	mini->tab = ft_split_minishell(mini->buff, ' ');
	mini->lst1 = NULL;
	i = 0;
	while (mini->tab[i])
	{
		if (mini->lst1 == NULL)
			mini->lst1 = new_link(mini->tab[i], -1);
		else
			add_link_bottom(mini->lst1, new_link(mini->tab[i], -1));
		i++;
	}
}
