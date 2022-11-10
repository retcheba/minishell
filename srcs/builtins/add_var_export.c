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

void	ft_free_list_export(t_struct *mini, t_list *export)
{
	t_list	*begin;

	begin = export;
	while (mini->malloc_export > 0)
	{
		export = ft_listlast(export, ft_lstsize(export) - mini->malloc_export);
		printf("last=%s\n", (char *)export->content);
		free(export->content);
		export = begin;
		mini->malloc_export--;
	}
	ft_free_list(export);
}

void	check_export_args(t_struct *mini, t_list *n)
{
	char	*content;

	if (n == NULL)
		print_export(mini->export);
	else
	{
		content = ft_strdup(n->content);
		mini->malloc_export++;
		mini->export = add_link_bottom(mini->export, new_link(content, 0));
	}
}
