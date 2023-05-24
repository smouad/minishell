/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 20:39:28 by msodor            #+#    #+#             */
/*   Updated: 2023/05/24 22:14:48 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char* get_type_string(enum e_token type) {
	switch (type) {
		case QUOTE:
			return "QUOTE";
		case DQUOTE:
			return "DQUOTE";
		case _SPACE:
			return "SPACE";
		case VAR:
			return "VAR";
		case PIPE:
			return "PIPE";
		case REDIR_IN:
			return "REDIR_IN";
		case REDIR_OUT:
			return "REDIR_OUT";
		case WORD:
			return "WORD";
		case HERE_DOC:
			return "HERE_DOC";
		case AREDIR_OUT:
			return "AREDIR_OUT";
		default:
			return "UNKNOWN";
	}
}

char* get_state_string(enum e_state state) {
	switch (state) {
		case IN_DQUOTE:
			return "IN_DQUOTE";
		case IN_QUOTE:
			return "IN_QUOTE";
		case DEFAULT:
			return "DEFAULT";
		default:
			return "";
	}
}

void print_table_row(t_elems *elem) {
	char* type_str = get_type_string(elem->type);
	char* state_str = get_state_string(elem->state);
	const char* content_str = (elem->content != NULL) ? elem->content : "";

	printf("%-10s | %-10d | %-10s | %-10s\n", content_str, elem->len, type_str, state_str);
}

void print_table(t_elems *lst) {
	printf("%-10s | %-10s | %-10s | %-10s\n", "Content", "Len", "Type", "State");
	printf("----------------------------------------\n");

	if (lst == NULL) {
		printf("Token table is empty.\n");
		return;
	}

	t_elems *current = lst->next;  // Start from the second node

	while (current != NULL) {
		print_table_row(current);
		current = current->next;
	}
}

