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

static size_t	ft_check_quotes(const char *s, size_t i)
{
	size_t	j;

	if (s[i] == '\"')
	{
		j = 1;
		while (s[i + j] != '\"' && s[i + j])
			j++;
		if (s[i + j] == '\"')
			i += j;
	}
	if (s[i] == '\'')
	{
		j = 1;
		while (s[i + j] != '\'' && s[i + j])
			j++;
		if (s[i + j] == '\'')
			i += j;
	}
	return (i);
}

static size_t	cmpt_words(const char *s, char c)
{
	size_t	i;
	size_t	cmpt;

	i = 0;
	if (s[i] == c || s[i] == 0)
		cmpt = 0;
	else
		cmpt = 1;
	while (s[i])
	{
		i = ft_check_quotes(s, i);
		if (s[i] == c && s[i + 1] != c && s[i + 1] != 0)
			cmpt++;
		i++;
	}
	return (cmpt + 1);
}

static size_t	ft_len_word(const char *s, char c, size_t i, size_t len)
{
	size_t	j;

	j = 0;
	while (s[i + len] != c && s[i + len])
	{
		if (s[i + len] == '\"')
		{
			j = 1;
			while (s[i + len + j] != '\"' && s[i + len + j])
				j++;
			if (s[i + len + j] == '\"')
				len += j;
		}
		if (s[i + len] == '\'')
		{
			j = 1;
			while (s[i + len + j] != '\'' && s[i + len + j])
				j++;
			if (s[i + len + j] == '\'')
				len += j;
		}
		len++;
	}
	return (len);
}

static char	**fill_tab(const char *s, char c, char **str)
{
	size_t	i;
	size_t	len;
	size_t	cmp;

	i = 0;
	len = 0;
	cmp = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		len = ft_len_word(s, c, i, len);
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
