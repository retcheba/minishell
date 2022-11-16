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

static char	*ft_separate_str(char *str, size_t split)
{
	char	*result;
	char	*tmp;
	char	*begin;
	char	*end;

	tmp = ft_substr(str, 0, split);
	begin = ft_strjoin(tmp, " ");
	end = ft_substr(str, split, (ft_strlen(str) - split));
	result = ft_strjoin(begin, end);
	free(tmp);
	tmp = NULL;
	free(begin);
	begin = NULL;
	free(end);
	end = NULL;
	return (result);
}

static char	*ft_separate_pipe_and_redirections(t_struct *mini, char *str)
{
	char	*result;
	size_t	split;

	split = 0;
	result = NULL;
	while (str[split])
	{
		if ((str[split] == '|' || str[split] == '>' || str[split] == '<')
			&& str[split + 1] != ' ' && str[split + 1] != '>'
			&& str[split + 1] != '<' && str[split + 1] != '\0')
		{
			split++;
			result = ft_separate_str(str, split);
			if (mini->free_list == NULL)
				mini->free_list = new_link(result, 0);
			else
				mini->free_list = add_link_bottom(mini->free_list, \
					new_link(result, 0));
		}
		split++;
	}
	if (result != NULL)
		return (result);
	return (mini->buff);
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
