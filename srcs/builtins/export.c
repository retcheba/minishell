/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subrandt <subrandt@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:31:54 by subrandt          #+#    #+#             */
/*   Updated: 2022/11/10 17:22:47 by subrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//sorts the list  according to ascii-order
static void	ft_sort_ascii_export(t_list *export)
{
	t_list	*tmp;

	tmp = export;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->content, tmp->next->content) > 0)
		{
			ft_swap_content(&tmp);
			ft_sort_ascii_export(export);
		}
		tmp = tmp->next;
	}
	export = tmp;
}

//doesn't print if there's "_="
static int	check_not_to_print(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '_')
		i++;
	if (s[i] == '_' && s[i + 1] == '=')
		return (1);
	return (0);
}

static void	print_my_export(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		printf("declare -x ");
		i = 0;
		while (s[i] && s[i] != '=')
		{
			printf("%c", s[i]);
			i++;
		}
		printf("=\"");
		i++;
		while (s[i])
		{
			printf("%c", s[i]);
			i++;
		}
		printf("\"\n");
	}
}

//prints export
void	print_export(t_list *export)
{
	t_list	*tmp;

	tmp = export;
	while (tmp)
	{
		if (check_not_to_print(tmp->content) == 0)
			print_my_export(tmp->content);
		tmp = tmp->next;
	}
}

//creates list export, sorted by ascii-order
void	ft_init_export(t_struct *mini, char **envp)
{
	int		i;

	i = 0;
	mini->export = NULL;
	while (envp[i])
	{
		if (mini->export == NULL)
			mini->export = new_link(envp[i], 0);
		else
			add_link_bottom(mini->export, new_link(envp[i], 0));
		i++;
	}
	ft_sort_ascii_export(mini->export);
}
