/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:14:38 by msodor            #+#    #+#             */
/*   Updated: 2023/05/23 15:17:07 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*token_new(char *content, int len, t_token type, t_state state)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->prev = NULL;
	token->content = content;
	token->len = len;
	token->type = type;
	token->state = state;
	token->next = NULL;
	return (t_token);
}

void	token_list_add(t_token **lst, t_token *new)
{
	t_token	*ptr;


	if (!lst || !new)
		return ;
	if (*lst)
	{
		ptr = *lst;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
		new->prev = ptr;
	}
	else
		*lst = new;
}


void	token_list_free(t_token *list)
{
	t_token	*tmp;

	tmp = list->head;
	while (tmp)
	{
		free(tmp->content);
		free(tmp);
		tmp = tmp->next;
	}
	free(list);
}
