/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subrandt <subrandt@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:40:11 by subrandt          #+#    #+#             */
/*   Updated: 2022/11/03 17:00:58 by subrandt         ###   ########.fr       */
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
void	ft_free_list(t_lst *lst);

//prints env 
static void	print_env(t_lst *env)
{
	t_lst	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

//creates the env-list
void	ft_env(char **envp, t_lst *env)
{
	int		i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		if (env == NULL)
			env = new_link(envp[i]);
		else
			ft_lstadd_back(env, new_link(envp[i]));
		i++;
	}
	print_env(env);
	ft_free_list(env);
}

int	main(int argc, char **argv, char **envp)
{
	t_lst	env;

	(void)argc;
	(void)argv;
	ft_env(envp, &env);
	return (0);
}
