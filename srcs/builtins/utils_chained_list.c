/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:41:25 by retcheba          #+#    #+#             */
/*   Updated: 2022/10/28 22:10:53 by subrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../minishell.h"
#include <stdlib.h>

typedef struct s_lst
{
	char			*content;
	struct s_lst	*next;
}				t_lst;

t_lst	*new_link(void *content)
{
	t_lst	*new;

	new = malloc(sizeof(t_lst));
	if (new)
	{
		new->content = content;
		new->next = NULL;
	}
	return (new);
}

t_lst	*ft_lstlast(t_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_lst	*ft_lstadd_back(t_lst *lst, t_lst *new)
{
	t_lst	*tmp;

	if (lst)
	{
		tmp = ft_lstlast(lst);
		tmp->next = new;
	}
	else
		lst = new;
	return (tmp);
}

void	ft_swap_content(t_lst **list)
{
	char	*swap;

	swap = (*list)->content;
	(*list)->content = (*list)->next->content;
	(*list)->next->content = swap;
}

void	ft_free_list(t_lst *lst)
{
	t_lst	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
		tmp = NULL;
	}
}
