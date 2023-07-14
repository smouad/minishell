/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:29:33 by msodor            #+#    #+#             */
/*   Updated: 2023/07/04 14:31:52 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	count_words(const char *str, char *c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_strchr(c, str[i]) >= 0)
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] && ft_strchr(c, str[i]) == -1)
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char *c)
{
	char	**split;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s)
		return (NULL);
	split = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	start = 0;
	end = 0;
	i = -1;
	while (++i < count_words(s, c))
	{
		while (ft_strchr(c, s[start]) >= 0)
			start++;
		end = start;
		while (ft_strchr(c, s[end]) == -1 && s[end])
			end++;
		split[i] = ft_substr(s, start, (end - start));
		start = end;
	}
	split[i] = 0;
	return (split);
}
