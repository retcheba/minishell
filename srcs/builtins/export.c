/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subrandt <subrandt@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:31:54 by subrandt          #+#    #+#             */
/*   Updated: 2022/11/03 11:21:34 by subrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../minishell.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct s_lst
{
	char			*content;
	struct s_lst	*next;
}				t_lst;

t_lst	*new_link(void *content);
t_lst	*ft_lstlast(t_lst *lst);
t_lst	*ft_lstadd_back(t_lst *lst, t_lst *new);
void	ft_export(char **envp, t_lst *export);
int		ft_strcmp(char *s1, char *s2);
void	ft_swap_content(t_lst **list);
void	ft_free_list(t_lst *lst);

//sorts the list  according to ascii-order
static void	ft_sort_ascii_export(t_lst *export)
{
	t_lst	*tmp;

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
		while (s[i] != '=')
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
void	check_print_export(t_lst *export)
{
	t_lst	*tmp;

	tmp = export;
	while (tmp)
	{
		if (check_not_to_print(tmp->content) == 0)
			print_my_export(tmp->content);
		tmp = tmp->next;
	}
}

//creates list export, sorted by ascii-order
void	ft_export(char **envp, t_lst *export)
{
	int		i;

	i = 0;
	export = NULL;
	while (envp[i])
	{
		if (export == NULL)
			export = new_link(envp[i]);
		else
			ft_lstadd_back(export, new_link(envp[i]));
		i++;
	}
	ft_sort_ascii_export(export);
	check_print_export(export);
	ft_free_list(export);
}

int	main(int argc, char **argv, char **envp)
{
	t_lst	export;

	(void)argc;
	(void)argv;
	ft_export(envp, &export);
	return (0);
}
