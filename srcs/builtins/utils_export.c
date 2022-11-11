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
