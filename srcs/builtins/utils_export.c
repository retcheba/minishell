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

#include "../minishell.h"

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
	while (s[i] && s[i] != '=' && (s[i] != '+' && s[i + 1] != '='))
	{
		if (!(s[i] >= 'A' && s[i] <= 'Z') && !(s[i] >= 'a' && s[i] <= 'z'))
			return (1);
		i++;
	}
	if (i == 0)
		return (1);
	return (0);
}

void	ft_print_error(char *cast)
{
	write(2, "export: \'", 9);
	write(2, cast, ft_strlen(cast));
	write(2, "\' : not a valid identifier\n", 27);
}
