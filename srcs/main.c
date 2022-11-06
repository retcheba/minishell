/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:15:05 by retcheba          #+#    #+#             */
/*   Updated: 2022/10/25 16:38:50 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_init_minishell(char *username)
{
	printf("\033[H\033[2J");
	printf("\e[2J\e[H\e[1;96m-----------------------------------------");
	printf("\e[1;96m--------------------------\e[0m\n");
	printf("\e[91m███╗   ███╗██╗███╗   ██╗██╗");
	printf("███████╗██╗  ██╗███████╗██╗     ██╗     \n");
	printf("████╗ ████║██║████╗  ██║██║██╔════╝");
	printf("██║  ██║██╔════╝██║     ██║     \n");
	printf("██╔████╔██║██║██╔██╗ ██║██║███████╗");
	printf("███████║█████╗  ██║     ██║     \n");
	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║");
	printf("██╔══██║██╔══╝  ██║     ██║     \n");
	printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║");
	printf("██║  ██║███████╗███████╗███████╗\n");
	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝");
	printf("╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\e[0m\n");
	printf("\e[1;96mMade by: subrandt & retcheba\e[0m\n");
	printf("\e[1;96m-----------------------------------------");
	printf("\e[1;96m--------------------------\e[0m\n");
	printf("\nWelcome %s\n", username);
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	mini;
	char	*username;

	username = getenv("USER");
	(void)argc;
	(void)argv;
	ft_init_minishell(username);
	while (1 == 1)
	{
		mini.buff = NULL;
		mini.buff = readline("\e[1;91mminishell\e[0m  ");
		add_history(mini.buff);
		if (mini.buff[0] != 0)
		{
			parsing(&mini);
			ft_tag_word(&mini);
			what_to_execute(&mini, envp);
			if (mini.lst1->tag == EXIT)
			{
				printf ("exit\n");
				free(mini.buff);
				ft_free_tab(mini.tab);
				ft_free_list(mini.lst1);
				exit(0);
			}
			ft_free_tab(mini.tab);
			ft_free_list(mini.lst1);
		}
	}
	return (0);
}
