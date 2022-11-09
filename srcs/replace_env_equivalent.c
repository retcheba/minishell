/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_equivalent.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 00:54:05 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/09 00:54:28 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *ft_lil(char *str)
{
    char    *equivalent;
    char    *result;
    char    *tmp;
    char    **tab;
    int i;

    tab = ft_split(str, '$');
    result = malloc(sizeof(char) * 1);
    result[0] = '\0';
    i = 0;
    while (tab[i])
    {
        equivalent = getenv(tab[i]);
        if (equivalent != NULL)
        {
            tmp = result;
            result = ft_strjoin(result, equivalent);
            free(tmp);
        }
        i++;
    }
    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
    return(result);
}

static char *ft_lol(char *str)
{
    char    *equivalent;
    char    *result;
    char    *tmp;
    char    **tab;
    int i;

    tab = ft_split(str, '$');
    result = ft_strdup(tab[0]);
    i = 0;
    while (tab[i])
    {
        equivalent = getenv(tab[i]);
        if (equivalent != NULL)
        {
            tmp = result;
            result = ft_strjoin(result, equivalent);
            free(tmp);
        }
        i++;
    }
    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
    return(result);
}

void    replace_env_equivalent(t_struct *mini)
{
    t_list  *begin;
    char    *result;
    char    *tmp;
    int     i;

    result = NULL;
    i = 0;
    begin = mini->lst1;
    while (mini->lst1)
    {
		if (ft_strchr(mini->tab[i], '$'))
		{
            if (mini->tab[i][0] == '$')
                result = ft_lil(mini->tab[i]);
            else
                result = ft_lol(mini->tab[i]);
            tmp = mini->tab[i];
            mini->tab[i] = result;
            free(tmp);
            tmp = NULL;
            mini->lst1->content = mini->tab[i];
        }
        i++;
        mini->lst1 = mini->lst1->next;
    }
    mini->lst1 = begin;
}