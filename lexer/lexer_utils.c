/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:39:16 by msodor            #+#    #+#             */
/*   Updated: 2023/05/29 12:37:29 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\r' || c == '\f')
		return (1);
	return (0);
}

int	special_char(char c)
{
	return (c == '\'' || c == '\"' || c == '<' || c == '>' || c == '|'
		/*|| c == '$'*/ || is_space(c) || c == '\n' || c == '\0');
}

void	set_token_word(char *line, t_elems *elem, int *i)
{
	int		j;
	int		start;
	char	*word;

	j = 0;
	start = *i;
	while (!special_char(line[start + j]))
		j++;
	word = ft_substr(line, start, j);
	token_list_add(&elem, token_new(word, j, WORD, DEFAULT));
	free(word);
	*(i) += j - 1;
}

void	set_token_var(char *line, t_elems *elem, int *i)
{
	int		j;
	int		start;
	char	*var;

	j = 0;
	start = *i;
	while (!special_char(line[start + j]))
		j++;
	var = ft_substr(line, start, j);
	token_list_add(&elem, token_new(var, j, VAR, DEFAULT));
	free(var);
	*(i) += j - 1;
}

void	set_token_redir(char *line, t_elems *elem, int *i)
{
	int	pos;

	pos = *i;
	if (line[pos] == '<')
	{
		if (line[pos + 1] == '<')
		{
			token_list_add(&elem, token_new("<<", 2, HERE_DOC, DEFAULT));
			*(i) += 1;
		}
		else
			token_list_add(&elem, token_new("<", 1, REDIR_IN, DEFAULT));
	}
	else if (line[pos] == '>')
	{
		if (line[pos + 1] == '>')
		{
			token_list_add(&elem, token_new(">>", 2, AREDIR_OUT, DEFAULT));
			*(i) += 1;
		}
		else
			token_list_add(&elem, token_new(">", 1, REDIR_OUT, DEFAULT));
	}
}
