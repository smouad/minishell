/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:06:07 by msodor            #+#    #+#             */
/*   Updated: 2023/05/23 23:56:30 by msodor           ###   ########.fr       */
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
		|| c == '$' || is_space(c) || c == '\n' || c == '\0');
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
	word = ft_substr(line, start, (start + j) + 1);
	printf("%s\n", word);
	token_list_add(&elem, token_new(word, j, WORD, UNOWN));
	free(word);
	*(i) += j;
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
	var = ft_substr(line, start, (start + j) + 1);
	token_list_add(&elem, token_new(var, j, VAR, UNOWN));
	free(var);
	*(i) += j;
}

void	*set_token_redir(char *line, t_elems *elem, int *i)
{
	int	pos;

	pos = *i;
	if (line[pos] == '<')
	{
		if (line[pos + 1] == '<')
			token_list_add(&elem, token_new("<<", 2, HERE_DOC, UNOWN));
		else
			token_list_add(&elem, token_new("<", 1, REDIR_IN, UNOWN));
		*(i) += 1;
	}
	if (line[pos] == '>')
	{
		if (line[pos + 1] == '>')
			token_list_add(&elem, token_new(">>", 2, HERE_DOC, UNOWN));
		else
			token_list_add(&elem, token_new(">", 1, REDIR_OUT, UNOWN));
		*(i) += 1;
	}
}
t_elems *lexer(char *line)
{
    int i = 0;
    t_elems *elems = malloc(sizeof(t_elems));

    while (line[i])
    {
        if (line[i] == '$')
            set_token_var(line, elems, &i);
        else if (!special_char(line[i]))
            set_token_word(line, elems, &i);
        else if (line[i] == '>' || line[i] == '<')
            set_token_redir(line, elems, &i);
        else if (line[i] == '\'')
            token_list_add(&elems, token_new("\'", 1, QUOTE, UNOWN));
        else if (line[i] == '\"')
            token_list_add(&elems, token_new("\"", 1, DQUOTE, UNOWN));
        else if (is_space(line[i]))
            token_list_add(&elems, token_new(" ", 1, SPACE, UNOWN));
        else if (line[i] == '|')
            token_list_add(&elems, token_new("|", 1, PIPE, UNOWN));

        i++;
    }
    return elems;
}

// t_elems	*lexer(char *line)
// {
// 	int		i;
// 	t_token	token;
// 	t_state	state;
// 	t_elems *elems;

// 	i = 0;
// 	elems = malloc(sizeof(t_elems));
// 	while (line[i])
// 	{
// 		if (line[i] == '$')
// 			set_token_var(line)
// 		else if (!special_char(line[i]))
// 			set_token_word(line, &i);
// 		else if (line[i] == '>' || line[i] '<')
// 			set_token_redir(line, &i);
// 		else if (line[i] == '\'')
// 			token_list_add(&elems, token_new("\'", 1, QUOTE, UNOWN));
// 		else if (line[i] == '\'')
// 			token_list_add(&elems, token_new("\"", 1, DQUOTE, UNOWN));
// 		else if (is_space(line[i]))
// 			token_list_add(&elems, token_new(" ", 1, SPACE, UNOWN));
// 		else if (line[i] == '|')
// 			token_list_add(&elems, token_new("|", 1, PIPE, UNOWN));
// 	}
// 	return (elems);
// }
// void print_token_table(t_elems *lst)
// {
//     printf("%-10s | %-10s | %-10s | %-10s\n", "Content", "Len", "Type", "State");
//     printf("----------------------------------------\n");
    
//     t_elems *current = lst;
    
//     while (current != NULL)
//     {
//         printf("%-10s | %-10c | %-10c | %-10c\n",
//                current->content, current->len, current->type, current->state);
        
//         current = current->next;
//     }
// }
void print_table(t_elems *lst) {
    printf("%-10s | %-10s | %-10s | %-10s\n", "Content", "Len", "Type", "State");
    printf("----------------------------------------\n");
    
    t_elems *current = lst;
    
    while (current != NULL) {
        char type_str[10];
        char state_str[10];
        
        switch (current->type) {
            case QUOTE:
                snprintf(type_str, sizeof(type_str), "QUOTE");
                break;
            case DQUOTE:
                snprintf(type_str, sizeof(type_str), "DQUOTE");
                break;
            case _SPACE:
                snprintf(type_str, sizeof(type_str), "SPACE");
                break;
            case VAR:
                snprintf(type_str, sizeof(type_str), "VAR");
                break;
            case PIPE:
                snprintf(type_str, sizeof(type_str), "PIPE");
                break;
            case REDIR_IN:
                snprintf(type_str, sizeof(type_str), "REDIR_IN");
                break;
            case REDIR_OUT:
                snprintf(type_str, sizeof(type_str), "REDIR_OUT");
                break;
            case WORD:
                snprintf(type_str, sizeof(type_str), "WORD");
                break;
            case HERE_DOC:
                snprintf(type_str, sizeof(type_str), "HERE_DOC");
                break;
            case AREDIR_OUT:
                snprintf(type_str, sizeof(type_str), "AREDIR_OUT");
                break;
            default:
                snprintf(type_str, sizeof(type_str), "UNKNOWN");
                break;
        }
        
        switch (current->state) {
            case IN_DQUOTE:
                snprintf(state_str, sizeof(state_str), "IN_DQUOTE");
                break;
            case IN_QUOTE:
                snprintf(state_str, sizeof(state_str), "IN_QUOTE");
                break;
            case DEFAULT:
                snprintf(state_str, sizeof(state_str), "DEFAULT");
                break;
            case UNOWN:
                snprintf(state_str, sizeof(state_str), "UNOWN");
                break;
            default:
                snprintf(state_str, sizeof(state_str), "UNKNOWN");
                break;
        }
        
        printf("%-10s | %-10d | %-10s | %-10s\n",
               current->content, current->len, type_str, state_str);
        
        current = current->next;
    }
}
int main()
{
	t_elems *list = lexer("echo \"hello\" >> > <<< | $MOUAD");
	print_table(list);
}
