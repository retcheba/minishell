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

#include "../minishell.h"

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

static char	*ft_get_status(t_struct *mini, char *str)
{
	char	*result;
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_itoa(g_status);
	if (str[1] != '\0')
	{
		tmp2 = ft_substr(str, 1, (ft_strlen(str) - 1));
		result = ft_strjoin(tmp1, tmp2);
		free(tmp1);
		free(tmp2);
	}
	else
		result = tmp1;
	if (mini->free_list == NULL)
		mini->free_list = new_link(result, 0);
	else
		mini->free_list = add_link_bottom(mini->free_list, \
			new_link(result, 0));
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
	result = ft_calloc(sizeof(char), 1);
	i = -1;
	while (tab[++i])
	{
		if (tab[i][0] == '?')
			equivalent = ft_get_status(mini, tab[i]);
		else
			equivalent = ft_getenv(mini, tab[i], envp);
		if (equivalent != NULL)
		{
			tmp = result;
			result = ft_strjoin(result, equivalent);
			free(tmp);
		}
	}
	ft_free_tab(tab);
	result = check_empty_dollar(result, str);
	return (result);
}

static char	*ft_replace(t_struct *mini, char *str, char *middle, size_t *i)
{
	char	*result;
	char	*tmp;
	char	*begin;
	char	*end;
	int		j;

	j = *i + *(i + 1);
	begin = ft_substr(str, 0, *i);
	end = ft_substr(str, j, (ft_strlen(str) - j));
	tmp = ft_strjoin(begin, middle);
	*i = ft_strlen(tmp) - 1;
	result = ft_strjoin(tmp, end);
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

char	*replace_env_equivalent(t_struct *mini, char *str, char **envp)
{
	size_t	i[2];
	char	*tmp;
	char	*result;

	i[0] = 0;
	while (str[i[0]])
	{
		i[0] = ft_check_squotes(str, i[0]);
		if (str[i[0]] == '$')
		{
			i[1] = 0;
			while (str[i[0] + i[1]] != ' ' && str[i[0] + i[1]] != '	'
				&& str[i[0] + i[1]] != '\"' && str[i[0] + i[1]])
				i[1]++;
			tmp = ft_substr(str, i[0], i[1]);
			result = ft_lil(mini, tmp, envp);
			free(tmp);
			str = ft_replace(mini, str, result, &i[0]);
			free(result);
		}
		i[0]++;
	}
	return (str);
}
