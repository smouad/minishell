/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:10:15 by msodor            #+#    #+#             */
/*   Updated: 2023/05/24 16:28:32 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_UTILS_H
# define HEADER_UTILS_H

# include "../libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_elems t_elems;

typedef enum e_token
{
	QUOTE = '\'',
	DQUOTE = '\"',
	_SPACE = ' ',
	VAR = '$',
	PIPE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	WORD,
	HERE_DOC,
	AREDIR_OUT,
}	t_token;
	// NEW_LINE = '\n',
	// _NULL = '0',
	// ESCAPE = '\\',

typedef enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	DEFAULT,
}	t_state;

typedef struct s_elems
{
	t_elems			*prev;
	char			*content;
	int				len;
	enum e_token	type;
	enum e_state	state;
	t_elems			*next;
}	t_elems;

#endif
