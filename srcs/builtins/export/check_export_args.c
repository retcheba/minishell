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

#include "../../minishell.h"

//si export toto - ajout dans export
//si export toto= ou toto=12  ajout dans export et env

static char	*attach_end(t_struct *mini, t_list *envp, char *content, char *cast)
{
	char			*result;
	char			*tmp;
	unsigned int	start;

	start = 0;
	while (cast[start] && cast[start] != '=')
		start++;
	if (!cast[start])
	{
		start++;
		tmp = ft_strjoin(envp->content, "=");
		mini->free_list = add_link_bottom(mini->free_list, new_link(tmp, 0));
		envp->content = tmp;
	}
	start = 0;
	while (content[start] != '=' && content[start])
		start++;
	tmp = ft_substr(content, (start + 1), ft_strlen(content) - (start + 1));
	mini->free_list = add_link_bottom(mini->free_list, new_link(tmp, 0));
	result = ft_strjoin(envp->content, tmp);
	mini->free_list = add_link_bottom(mini->free_list, new_link(result, 0));
	return (result);
}

static char	*new_content_attach(t_struct *mini, char *content)
{
	char	*result;
	char	*begin;
	char	*end;
	size_t	split;

	split = 0;
	while (content[split] != '+' && content[split])
		split++;
	begin = ft_substr(content, 0, split);
	end = ft_substr(content, (split + 1), (ft_strlen(content) - (split + 1)));
	result = ft_strjoin(begin, end);
	mini->free_list = add_link_bottom(mini->free_list, new_link(result, 0));
	free(begin);
	begin = NULL;
	free(end);
	end = NULL;
	return (result);
}

static int	search_in_envp(t_struct *mini, t_list *envp, char *content)
{
	int		i;
	char	*cast;

	while (envp)
	{
		cast = (char *)envp->content;
		i = 0;
		while (content[i] && content[i] != '=' && content[i] != '+'
			&& cast[i] && cast[i] != '=' && content[i] == cast[i])
			i++;
		if ((content[i] == '=' && cast[i] == '\0')
			|| (content[i] == '=' && cast[i] == '=')
			|| (content[i] == '+' && cast[i] == '\0')
			|| (content[i] == '+' && cast[i] == '=')
			|| (content[i] == '\0' && cast[i] == '='))
		{
			if (content[i] == '+')
				envp->content = attach_end(mini, envp, content, cast);
			else if (content[i] != '\0')
				envp->content = content;
			return (0);
		}
		envp = envp->next;
	}
	return (1);
}

static void	put_in_envp(t_struct *mini, char *content)
{
	if (ft_strnstr(content, "+=", ft_strlen(content)))
	{
		if (search_in_envp(mini, mini->export, content))
			mini->export = add_link_bottom(mini->export, \
				new_link(new_content_attach(mini, content), 0));
		if (search_in_envp(mini, mini->env, content))
			mini->env = add_link_bottom(mini->env, \
				new_link(new_content_attach(mini, content), 0));
	}
	else if (ft_strchr(content, '=') != NULL)
	{
		if (search_in_envp(mini, mini->export, content))
			mini->export = add_link_bottom(mini->export, new_link(content, 0));
		if (search_in_envp(mini, mini->env, content))
			mini->env = add_link_bottom(mini->env, new_link(content, 0));
	}
	else
	{
		if (search_in_envp(mini, mini->export, content))
			mini->export = add_link_bottom(mini->export, new_link(content, 0));
	}
	g_status = 0;
}

void	check_export_args(t_struct *mini, char **cmd)
{
	char	*content;
	int		i;

	if (cmd[1] == NULL)
		print_export(mini->export);
	i = 1;
	while (cmd[i])
	{
		if (!(cmd[i][0] == '_' && cmd[i][1] == '='))
		{
			if (is_only_alpha(cmd[i]))
				ft_print_error(cmd[i]);
			else
			{
				content = ft_strdup(cmd[i]);
				if (mini->free_list == NULL)
					mini->free_list = new_link(content, 0);
				else
					mini->free_list = add_link_bottom(mini->free_list, \
						new_link(content, 0));
				put_in_envp(mini, content);
			}
		}
		i++;
	}
}
