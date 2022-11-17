/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_equivalent.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 00:54:05 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/09 02:55:24 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_getenv(t_struct *mini, char *str, char **envp)
{
	unsigned int	i;
	unsigned int	j;
	char			*result;

	result = NULL;
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (str[j] == envp[i][j] && str[j] && envp[i][j] != '=')
			j++;
		if (str[j] == '\0' && envp[i][j] == '=')
		{
			j++;
			result = ft_substr(envp[i], j, (ft_strlen(envp[i]) - j));
			if (mini->free_list == NULL)
				mini->free_list = new_link(result, 0);
			else
				mini->free_list = add_link_bottom(mini->free_list, \
					new_link(result, 0));
		}
		i++;
	}
	return (result);
}

static char	*ft_lil(t_struct *mini, char *str, char **envp)
{
	char	*equivalent;
	char	*result;
	char	*tmp;
	char	**tab;
	int		i;

	tab = ft_split(str, '$');
	result = malloc(sizeof(char) * 1);
	result[0] = '\0';
	i = 0;
	while (tab[i])
	{
		equivalent = ft_getenv(mini, tab[i], envp);
		if (equivalent != NULL)
		{
			tmp = result;
			result = ft_strjoin(result, equivalent);
			free(tmp);
		}
		i++;
	}
	ft_free_tab(tab);
	return (result);
}

static char	*ft_lol(t_struct *mini, char *str, char **envp)
{
	char	*equivalent;
	char	*result;
	char	*tmp;
	char	**tab;
	int		i;

	tab = ft_split(str, '$');
	result = ft_strdup(tab[0]);
	i = 0;
	while (tab[i])
	{
		equivalent = ft_getenv(mini, tab[i], envp);
		if (equivalent != NULL)
		{
			tmp = result;
			result = ft_strjoin(result, equivalent);
			free(tmp);
		}
		i++;
	}
	ft_free_tab(tab);
	return (result);
}

void	replace_env_equivalent(t_struct *mini, char **envp)
{
	t_list	*begin;
	char	*result;
	char	*tmp;
	int		i;

	result = NULL;
	i = 0;
	begin = mini->lst1;
	while (mini->lst1)
	{
		if (ft_strchr(mini->tab[i], '$'))
		{
			if (mini->tab[i][0] == '$')
				result = ft_lil(mini, mini->tab[i], envp);
			else
				result = ft_lol(mini, mini->tab[i], envp);
			tmp = mini->tab[i];
			mini->tab[i] = result;
			free(tmp);
			mini->lst1->content = mini->tab[i];
		}
		i++;
		mini->lst1 = mini->lst1->next;
	}
	mini->lst1 = begin;
}
