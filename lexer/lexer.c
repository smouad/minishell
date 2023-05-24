/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:06:07 by msodor            #+#    #+#             */
/*   Updated: 2023/05/24 17:32:27 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\r' || c == '\f')
		return (1);
	return (0);
}

int	special_char(char c)
{
	return (c == '\'' || c == '\"' || c == '<' || c == '>' || c == '|'
		/*|| c == '$'*/ || is_space(c) || c == '\n' || c == '\0');
}

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

void	set_token_var(char *line, t_elems *elem, int *i)
{
	int		j;
	int		start;
	char	*var;

	j = 0;
	start = *i;
	while (!special_char(line[start + j]))
		j++;
	var = ft_substr(line, start, j);
	token_list_add(&elem, token_new(var, j, VAR, DEFAULT));
	free(var);
	*(i) += j;
}

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


// void	quote_state(t_elems **ptr)
// {
// 	ptr->state = IN_QUOTE;
// 	ptr = ptr->next;
// 	while (ptr->type != QUOTE)
// 	{
// 		ptr->state = IN_QUOTE;
// 		ptr = ptr->next;
// 		ptr->state = IN_QUOTE;
// 	}
// }
// void	set_state(t_elems *elems)
// {
// 	t_elems	*ptr;

// 	ptr = elems->next;
// 	while (ptr)
// 	{
// 		if (ptr->type == DQUOTE)
// 		{
// 			ptr->state = IN_DQUOTE;
// 			ptr = ptr->next;
// 			while (ptr->type != DQUOTE)
// 			{
// 				ptr->state = IN_DQUOTE;
// 				ptr = ptr->next;
// 				ptr->state = IN_DQUOTE;
// 			}
// 		}
// 		else if (ptr->type == QUOTE)
// 		{
// 			quote_state(&ptr);
// 		}
// 		ptr = ptr->next;
// 	}
// }



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
	set_state(elems);
	return (elems);
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
