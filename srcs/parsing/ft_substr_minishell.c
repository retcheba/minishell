/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:06:39 by retcheba          #+#    #+#             */
/*   Updated: 2022/04/11 18:38:16 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_d_quotes(char const *s, size_t *tmp1, size_t start)
{
	size_t	j;

	if (*tmp1 != 0)
		*tmp1 = 0;
	else
	{
		j = 1;
		while (s[start + j] != '\"' && s[start + j])
			j++;
		if (s[start + j] == '\"')
			*tmp1 = j;
		else
			return (1);
	}
	return (0);
}

static int	check_s_quotes(char const *s, size_t *tmp2, size_t start)
{
	size_t	j;

	if (*tmp2 != 0)
		*tmp2 = 0;
	else
	{
		j = 1;
		while (s[start + j] != '\'' && s[start + j])
			j++;
		if (s[start + j] == '\'')
			*tmp2 = j;
		else
			return (1);
	}
	return (0);
}

static char	*ft_fill_str(char *str, char const *s, size_t start, size_t len)
{
	size_t	i;
	size_t	tmp[2];

	i = 0;
	tmp[0] = 0;
	tmp[1] = 0;
	while (len-- > 0 && s[start])
	{
		if (s[start] == '\"')
		{
			if (check_d_quotes(s, &tmp[0], start))
				str[i++] = s[start];
		}
		else if (s[start] == '\'')
		{
			if (check_s_quotes(s, &tmp[1], start))
				str[i++] = s[start];
		}
		else
			str[i++] = s[start];
		start++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr_minishell(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		str = malloc(sizeof(char) * 1);
		*str = '\0';
		return (str);
	}
	if (len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str = ft_fill_str(str, s, start, len);
	return (str);
}
