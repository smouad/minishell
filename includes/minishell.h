/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:29:40 by msodor            #+#    #+#             */
/*   Updated: 2023/05/23 23:24:04 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "header_utils.h"

/* ******************************************* */
/* ----------------:> LEXER <:---------------- */
/* ******************************************* */

/* -----:> LIST <:-----*/

t_elems	*token_new(char *content, int len, t_token type, t_state state);
void	token_list_add(t_elems **lst, t_elems *new);
void	token_list_free(t_elems *list);

/* -----:> LEXER <:-----*/

int		is_space(char c);
void	set_token_word(char *line, t_elems *elem, int *i);
void	*set_token_redir(char *line, t_elems *elem, int *i);
t_elems	*lexer(char *line);


#endif