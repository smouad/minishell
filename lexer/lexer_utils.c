/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:39:16 by msodor            #+#    #+#             */
/*   Updated: 2023/06/21 17:41:12 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * is_space - function that checks if @c is a white-space character
 * @c: the character to check
 *
 * Return: 1 if @c is a white-space character, otherwise 0
 */
int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\r' || c == '\f')
		return (1);
	return (0);
}

/**
 * special_char - checks if @c is a special character or white-space character
 * @c: the character to check
 *
 * Return: the ASCII value of the character if it is a special
 * or white-space character, otherwise 0
 */
int	special_char(char c)
{
	return (c == '\'' || c == '\"' || c == '<' || c == '>' || c == '|'
		|| c == '$' || is_space(c) || c == '\n' || c == '\0');
}

/**
 * set_token_word - function that extracts a word from the input string
 * and adds it to the token list
 * @line: the input string
 * @elem: a pointer to the token list
 * @i: a pointer to the current index of the input string
 */
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

/**
 * set_token_var - function that extracts a variable from the input string
 * and adds it to the token list
 * @line: the input string
 * @elem: a pointer to the token list
 * @i: a pointer to the current index of the input string
 */
void	set_token_var(char *line, t_elems *elem, int *i)
{
	int		j;
	int		start;
	int		skip;
	char	*var;

	j = 0;
	start = *i;
	skip = start + 1;
	while (ft_isalnum(line[skip + j]) || line[skip + j] == '_' \
	|| line[skip + j] == '?')
		j++;
	var = ft_substr(line, start, j + 1);
	token_list_add(&elem, token_new(var, j + 1, VAR, DEFAULT));
	free(var);
	*(i) += j;
}

/**
 * set_token_redir - function that extracts a redirection symbol
 * from the input string and adds it to the token list
 * @line: the input string
 * @elem: a pointer to the token list
 * @i: a pointer to the current index of the input string
 */
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
