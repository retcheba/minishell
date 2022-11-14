/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subrandt <subrandt@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 08:58:47 by subrandt          #+#    #+#             */
/*   Updated: 2022/11/10 17:26:03 by subrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//si export toto - ajout dans export
//si export toto= ou toto=12  ajout dans export et env

static int	is_only_alpha(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (!(s[i] >= 'A' && s[i] <= 'Z') && !(s[i] >= 'a' && s[i] <= 'z'))
			return (1);
		i++;
	}
	return (0);
}

void	ft_free_list_export(t_struct *mini)
{
	t_list	*begin;

	begin = mini->free_list;
	while (mini->free_list)
	{
		free(mini->free_list->content);
		mini->free_list = mini->free_list->next;
	}
	mini->free_list = begin;
	ft_free_list(mini->free_list);
	ft_free_list(mini->export);
}

static int	search_in_envp(t_list *envp, char *content)
{
	int		i;
	char	*cast;

	while (envp)
	{
		cast = (char *)envp->content;
		i = 0;
		while (content[i] && content[i] != '='
			&& cast[i] && cast[i] != '=' && content[i] == cast[i])
			i++;
		if ((content[i] == '=' && cast[i] == '\0')
			|| (content[i] == '=' && cast[i] == '='))
		{
			envp->content = content;
			return (0);
		}
		else if (cast[i] == '=' && content[i] == '\0')
			return (0);
		envp = envp->next;
	}
	return (1);
}

static void	put_in_envp(t_struct *mini, char *cast, char *content)
{
	content = ft_strdup(cast);
	if (mini->free_list == NULL)
		mini->free_list = new_link(content, 0);
	else
		mini->free_list = add_link_bottom(mini->free_list, \
			new_link(content, 0));
	if (ft_strchr(content, '=') != NULL)
	{
		if (search_in_envp(mini->export, content))
			mini->export = add_link_bottom(mini->export, new_link(content, 0));
		if (search_in_envp(mini->env, content))
			mini->env = add_link_bottom(mini->env, new_link(content, 0));
	}
	else
	{
		if (search_in_envp(mini->export, content))
			mini->export = add_link_bottom(mini->export, new_link(content, 0));
	}
}

void	check_export_args(t_struct *mini, t_list *n)
{
	char	*content;
	char	*cast;

	content = NULL;
	cast = NULL;
	if (n == NULL)
		print_export(mini->export);
	while (n != NULL)
	{
		cast = (char *)n->content;
		if (!(cast[0] == '_' && cast[1] == '='))
		{
			if (cast[0] == '=' || is_only_alpha(cast))
			{
				write(2, "export: \'", 9);
				write(2, cast, ft_strlen(cast));
				write(2, "\' : not a valid identifier\n", 27);
			}
			else
				put_in_envp(mini, cast, content);
		}
		n = n->next;
	}
}
