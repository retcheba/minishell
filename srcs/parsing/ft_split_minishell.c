/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:35:38 by retcheba          #+#    #+#             */
/*   Updated: 2022/10/25 15:52:52 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	cmpt_words(const char *s, char c)
{
	size_t	i;
	size_t	l;
	size_t	cmpt;

	i = 0;
	if (s[i] == c || s[i] == 0)
		cmpt = 0;
	else
		cmpt = 1;
	while (s[i])
	{
		if (s[i] == '\"')
		{
			l = 1;
			while (s[i + l] != '\"' && s[i + l])
				l++;
			if (s[i + l] == '\"')
				i += l;
		}
		if (s[i] == '\'')
		{
			l = 1;
			while (s[i + l] != '\'' && s[i + l])
				l++;
			if (s[i + l] == '\'')
				i += l;
		}
		if (s[i] == c && s[i + 1] != c && s[i + 1] != 0)
			cmpt++;
		i++;
	}
	return (cmpt + 1);
}

static char	**fill_tab(const char *s, char c, char **str)
{
	unsigned int	i;
	size_t			len;
	size_t			l;
	size_t			cmp;

	i = 0;
	len = 0;
	cmp = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i + len] != c && s[i + len])
		{
			if (s[i + len] == '\"')
			{
				l = 1;
				while (s[i + len + l] != '\"' && s[i + len + l])
					l++;
				if (s[i + len + l] == '\"')
					len += l;
			}
			if (s[i + len] == '\'')
			{
				l = 1;
				while (s[i + len + l] != '\'' && s[i + len + l])
					l++;
				if (s[i + len + l] == '\'')
					len += l;
			}
			len++;
		}
		if (len > 0)
		{
			str[cmp] = ft_substr(s, i, len);
			cmp++;
		}
		i += len;
		while (s[i] == c && s[i])
			i++;
		len = 0;
	}
	str[cmp] = NULL;
	return (str);
}

char	**ft_split_minishell(char const *s, char c)
{
	char			**str;

	if (!s)
		return (NULL);
	str = malloc(sizeof(char *) * (cmpt_words(s, c)));
	if (!str)
		return (NULL);
	str = fill_tab(s, c, str);
	return (str);
}
