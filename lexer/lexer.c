/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:06:07 by msodor            #+#    #+#             */
/*   Updated: 2023/07/07 13:22:44 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * lexer - a function that tokenizes a given input string and builds a token list
 * @line: a pointer to the input string to be tokenized
 *
 * This function processes the input string and identifies tokens such as
 * variables, words, redirections, pipe symbols, and quotes.
 * It also handles special characters and creates a token list
 * that represents the structure of the input string.
 *
 * The function returns a token list, which can be further processed
 * by other functions in the lexer or parser.
 */
t_elems	*lexer(char *line)
{
	int		i;
	t_elems	*elems;

	i = 0;
	elems = token_new("", 0, _SPACE, DEFAULT);
	while (line[i])
	{
		if (line[i] == '$')
			set_token_var(line, elems, &i);
		else if (!special_char(line[i]))
			set_token_word(line, elems, &i);
		else if (line[i] == '>' || line[i] == '<')
			set_token_redir(line, elems, &i);
		else if (line[i] == '\'')
			token_list_add(&elems, token_new("\'", 1, QUOTE, DEFAULT));
		else if (line[i] == '\"')
			token_list_add(&elems, token_new("\"", 1, DQUOTE, DEFAULT));
		else if (is_space(line[i]))
			token_list_add(&elems, token_new(" ", 1, _SPACE, DEFAULT));
		else if (line[i] == '|')
			token_list_add(&elems, token_new("|", 1, PIPE, DEFAULT));
		i++;
	}
	return (set_state(elems), join_in_quote(&elems), elems);
}
