/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:11:21 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/17 01:56:10 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_check_squotes(const char *s, size_t i)
{
	size_t	j;

	if (s[i] == '\'')
	{
		j = 1;
		while (s[i + j] != '\'' && s[i + j])
			j++;
		if (s[i + j] == '\'')
			i += j;
	}
	return (i);
}

static char	*ft_separate_str(t_struct *mini, char *str, size_t split)
{
	char	*result;
	char	*tmp;
	char	*begin;
	char	*end;

	tmp = ft_substr(str, 0, split);
	begin = ft_strjoin(tmp, " ");
	end = ft_substr(str, split, (ft_strlen(str) - split));
	result = ft_strjoin(begin, end);
	if (mini->free_list == NULL)
		mini->free_list = new_link(result, 0);
	else
		mini->free_list = add_link_bottom(mini->free_list, \
			new_link(result, 0));
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
	size_t	split;

	split = 0;
	while (str[split])
	{
		split = ft_check_quotes(str, split);
		if (str[split] != ' ' && str[split] != '>' && str[split] != '<'
			&& (str[split + 1] == '|' || str[split + 1] == '>'
				|| str[split + 1] == '<'))
		{
			split++;
			str = ft_separate_str(mini, str, split);
		}
		else if ((str[split] == '|' || str[split] == '>' || str[split] == '<')
			&& str[split + 1] != ' ' && str[split + 1] != '>'
			&& str[split + 1] != '<' && str[split + 1] != '\0')
		{
			split++;
			str = ft_separate_str(mini, str, (split));
		}
		split++;
	}
	return (str);
}

void	parsing(t_struct *mini, char **envp)
{
	int		i;

	mini->buff = ft_separate_pipe_and_redirections(mini, mini->buff);
	mini->buff = replace_env_equivalent(mini, mini->buff, envp);
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
