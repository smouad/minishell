/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:00:00 by msodor            #+#    #+#             */
/*   Updated: 2023/05/31 10:27:10 by msodor           ###   ########.fr       */
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
	t_elems	*current;
	t_elems	*temp;

	current = *elems;
	temp = NULL;
	while (current != NULL)
	{
		if ((current->type == DQUOTE || current->type == QUOTE) \
		&& current->state == DEFAULT)
		{
			temp = current->next;
			token_del(elems, current);
			current = temp;
		}
		else
			current = current->next;
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
void	join_cmd(t_elems **elems)
{
	t_elems	*current;
	t_elems	*temp;
	char	*new_content;

	current = *elems;
	temp = NULL;
	rm_quotes(elems);
	while (current != NULL && current->next != NULL)
	{
		if (current->type == WORD && current->next->type == WORD)
		{
			new_content = ft_strjoin(current->content, current->next->content);
			free(current->content);
			current->content = new_content;
			// Delete the next node using the token_del function
			temp = current->next;
			current->next = current->next->next;
			if (current->next != NULL)
				current->next->prev = current;
			free(temp);
		}
		else
			current = current->next;
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

t_elems	*analyser(char *line)
{
	t_elems	*elems;

	elems = lexer(line);
	// rm_quotes(&elems);
	join_cmd(&elems);
	type_cast(&elems);
	return (elems);
}
