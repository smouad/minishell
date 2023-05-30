/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:00:00 by msodor            #+#    #+#             */
/*   Updated: 2023/05/30 16:03:14 by msodor           ###   ########.fr       */
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

void	rm_quotes(t_elems **elems)
{
	t_elems	*head;

	head = *elems;
	while (head && head->next)
	{
		if ((head->type == DQUOTE || head->type == QUOTE) \
		&& head->state == DEFAULT)
		{
			printf("here\n");
			token_del(elems, head);
		}
		head = head->next;
	}
}

// void	join_cmd(t_elems **elems)
// {
// 	t_elems	*head;

// 	head = *elems;
// 	rm_quotes(elems);
// 	while (head && head->next)
// 	{
// 		if (head->type == WORD && head->next->type == WORD)
// 		{
// 			head->content = ft_strjoin(head->content, head->next->content);
// 			token_del(elems, head);
// 		}
// 		head = head->next;
// 	}
// }

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

t_elems	*analyser(char *line)
{
	t_elems	*elems;

	elems = lexer(line);
	// join_cmd(&elems);
	rm_quotes(&elems);
	type_cast(&elems);
	return (elems);
}
