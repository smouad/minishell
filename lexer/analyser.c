/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:16:17 by msodor            #+#    #+#             */
/*   Updated: 2023/07/06 18:27:28 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * join_cmd - function that concatenates adjacent elements
 * in the token list that are of type WORD
 * @elems: a pointer to a pointer to the head element of the token list
 */
void	join_cmd(t_elems **elems)
{
	t_elems	*current;
	char	*new_content;

	current = *elems;
	type_cast(elems);
	rm_quotes(elems);
	current = current->next;
	while (current && current->next)
	{
		if ((current->type == WORD || current->type == VAR) && \
		(current->next->type == WORD || current->next->type == VAR))
		{
			new_content = ft_strjoin(current->content, current->next->content);
			free(current->content);
			current->content = new_content;
			current->len = ft_strlen(new_content);
			token_del(elems, current->next);
		}
		else
			current = current->next;
	}
}

/**
 * analyser - processes a given input string and returns a token list
 * @line: a pointer to the input string to be processed
 *
 * This function uses the `lexer` function to tokenize the input string
 * and then applies various syntax checks and modifications to the token list.
 * These include checking for quotes syntax, joining commands, removing spaces,
 * checking for redirection syntax, and checking for pipe syntax.
 * Return: returns a token list that represents the modified input string.
 */
t_elems	*analyser(char *line, t_parser *parser)
{
	t_elems	*elems;

	elems = lexer(line);
	if (quotes_syntax(elems, parser))
	{
		token_list_free(elems);
		return (NULL);
	}
	set_env(elems, parser);
	join_cmd(&elems);
	rm_spaces(&elems);
	if ((elems->content[0] == '\0' && !elems->next) \
	|| pipe_syntax(elems, parser))
	{
		token_list_free(elems);
		return (NULL);
	}
	if (redir_syntax(elems, parser))
	{
		token_list_free(elems);
		return (NULL);
	}
	return (elems);
}
