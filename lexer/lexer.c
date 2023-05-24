/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:06:07 by msodor            #+#    #+#             */
/*   Updated: 2023/05/24 17:42:38 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	return (set_state(elems), elems);
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
        char* type_str;
        char* state_str;

        if (current->type == QUOTE)
            type_str = "QUOTE";
        else if (current->type == DQUOTE)
            type_str = "DQUOTE";
        else if (current->type == _SPACE)
            type_str = "SPACE";
        else if (current->type == VAR)
            type_str = "VAR";
        else if (current->type == PIPE)
            type_str = "PIPE";
        else if (current->type == REDIR_IN)
            type_str = "REDIR_IN";
        else if (current->type == REDIR_OUT)
            type_str = "REDIR_OUT";
        else if (current->type == WORD)
            type_str = "WORD";
        else if (current->type == HERE_DOC)
            type_str = "HERE_DOC";
        else if (current->type == AREDIR_OUT)
            type_str = "AREDIR_OUT";
        else
            type_str = "UNKNOWN";

        if (current->state == IN_DQUOTE)
            state_str = "IN_DQUOTE";
        else if (current->state == IN_QUOTE)
            state_str = "IN_QUOTE";
        else if (current->state == DEFAULT)
            state_str = "DEFAULT";

        const char* content_str = (current->content != NULL) ? current->content : "";

		if(current)
        	printf("%-10s | %-10d | %-10s | %-10s\n", current->content, current->len, type_str, state_str);
        current = current->next;
    }
}

int main()
{
	t_elems *list = lexer("echo \"hello  $USER \" >>> file | grep h | 'cat mousd' << name");
	print_table(list);
}
