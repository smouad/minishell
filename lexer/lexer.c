/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:06:07 by msodor            #+#    #+#             */
/*   Updated: 2023/05/30 00:01:15 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	join_in_quote(t_elems **elems)
{
	t_elems	*head;

	head = *elems;
	while (head && head->next)
	{
		if (head->state == IN_DQUOTE && head->next->state == IN_DQUOTE \
		&& head->next->type != VAR && head->type != VAR)
		{
			head->content = ft_strjoin(head->content, head->next->content);
			head->len += head->next->len;
			head->type = WORD;
			token_del(elems, head->next);
			join_in_quote(&head);
		}
		else if (head->state == IN_QUOTE && head->next->state == IN_QUOTE)
		{
			head->content = ft_strjoin(head->content, head->next->content);
			head->len += head->next->len;
			head->type = WORD;
			token_del(elems, head->next);
			join_in_quote(&head);
		}
		head = head->next;
	}
}

void	type_cast(t_elems **elems)
{
	t_elems	*head;

	head = *elems;
	while (head)
	{
		if ((head->state == IN_DQUOTE && head->type != VAR) \
		|| head->state == IN_QUOTE)
			head->type = WORD;
		head = head->next;
	}
}

t_elems	*lexer(char *line)
{
	int		i;
	t_elems	*elems;

	i = 0;
	elems = malloc(sizeof(t_elems));
	elems->next = NULL;
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
