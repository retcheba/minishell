/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:41:25 by retcheba          #+#    #+#             */
/*   Updated: 2022/10/25 16:20:17 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*new_link(void *content, int tag)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new)
	{
		new->content = content;
		new->tag = tag;
		new->next = NULL;
	}
	return (new);
}

t_list	*add_link_bottom(t_list *lst, t_list *new)
{
	t_list	*begin;

	begin = lst;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
	return (begin);
}

t_list	*add_link_top(t_list *lst, void *content, int tag)
{
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	if (tmp)
	{
		tmp->content = content;
		tmp->tag = tag;
		tmp->next = lst;
	}
	return (tmp);
}

void	ft_free_list(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
		tmp = NULL;
	}
}

t_list	*ft_listlast(t_list *lst, int i)
{
	if (lst)
	{
		while (lst->next && i > 0)
		{
			lst = lst->next;
			i--;
		}
	}
	return (lst);
}
