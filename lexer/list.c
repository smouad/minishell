/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:14:38 by msodor            #+#    #+#             */
/*   Updated: 2023/05/28 23:45:42 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_elems	*token_new(char *content, int len, t_token type, t_state state)
{
	t_elems	*elems;

	elems = malloc(sizeof(t_elems));
	if (!elems)
		return (NULL);
	elems->prev = NULL;
	elems->content = ft_strdup(content);
	elems->len = len;
	elems->type = type;
	elems->state = state;
	elems->next = NULL;
	return (elems);
}

void	token_list_add(t_elems **lst, t_elems *new)
{
	t_elems	*ptr;

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

void token_del(t_elems **head, t_elems *node) {
    if (*head == NULL || node == NULL) {
        return;
    }
    if (*head == node) {
        *head = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    else {
        // node is the head of the list
        *head = node->next;
    }
    free(node->content);
    free(node);
}



// void	token_list_free(t_elems *list)
// {
// 	t_elems	*tmp;

// 	tmp = list->head;
// 	while (tmp)
// 	{
// 		free(tmp->content);
// 		free(tmp);
// 		tmp = tmp->next;
// 	}
// 	free(list);
// }
