/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subrandt <subrandt@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:26:34 by subrandt          #+#    #+#             */
/*   Updated: 2022/11/02 16:36:54 by subrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../minishell.h"

typedef struct s_lst
{
	char			*content;
	struct s_lst	*next;
}				t_lst;

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] - s2[i] == 0) && s1[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
