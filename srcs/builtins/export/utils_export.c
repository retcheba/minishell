/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subrandt <subrandt@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:26:34 by subrandt          #+#    #+#             */
/*   Updated: 2022/11/06 04:02:57 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] - s2[i] == 0) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_swap_content(t_list **list)
{
	char	*swap;

	swap = (*list)->content;
	(*list)->content = (*list)->next->content;
	(*list)->next->content = swap;
}

int	is_only_alpha(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=' && !(s[i] == '+' && s[i + 1] == '='))
	{
		if (i == 0
			&& !(s[i] >= 'A' && s[i] <= 'Z') && !(s[i] >= 'a' && s[i] <= 'z'))
			return (1);
		else if (!(s[i] >= 'A' && s[i] <= 'Z') && !(s[i] >= 'a' && s[i] <= 'z')
			&& !(s[i] >= '0' && s[i] <= '9'))
			return (1);
		i++;
	}
	if (i == 0)
		return (1);
	return (0);
}

int	ft_print_error(char *cast)
{
	write(2, "export: \'", 9);
	write(2, cast, ft_strlen(cast));
	write(2, "\' : not a valid identifier\n", 27);
	g_status = 1;
	return (1);
}

void	save_content(t_struct *mini, char *content)
{
	if (mini->free_list == NULL)
		mini->free_list = new_link(content, 0);
	else
		mini->free_list = add_link_bottom(mini->free_list, \
			new_link(content, 0));
}
