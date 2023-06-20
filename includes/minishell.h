/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:29:40 by msodor            #+#    #+#             */
/*   Updated: 2023/06/20 15:16:42 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "header_utils.h"

/* ******************************************* */
/* ----------------:> LEXER <:---------------- */
/* ******************************************* */

/* -----:> LIST <:-----*/
t_elems		*token_new(char *content, int len, t_token type, t_state state);
void		token_list_add(t_elems **lst, t_elems *new);
void		token_del(t_elems **head, t_elems *node);
void		token_list_free(t_elems *list);

/* -----:> STATE <:-----*/
void		set_state(t_elems *elems);
void		dquote_state(t_elems **ptr);
void		quote_state(t_elems **ptr);

/* -----:> LEXER <:-----*/
int			is_space(char c);
int			special_char(char c);
void		set_token_word(char *line, t_elems *elem, int *i);
void		set_token_redir(char *line, t_elems *elem, int *i);
void		set_token_var(char *line, t_elems *elem, int *i);
t_elems		*lexer(char *line);

/* -----:> ANALYSER <:-----*/
void		join_in_quote(t_elems **elems);
void		rm_quotes(t_elems **elems);
void		join_cmd(t_elems **elems);
void		type_cast(t_elems **elems);
void		rm_spaces(t_elems **elems);
t_elems		*analyser(char *line, t_env *env);

/* -----:> SYNTAX_ERR <:-----*/
int			quotes_syntax(t_elems *elems);
int			redir_syntax(t_elems *elems);
int			pipe_syntax(t_elems *elems);
int			is_redir(t_elems *elems);

/* -----:> PRINT_TABLE <:-----*/
char		*get_type_string(enum e_token type);
char		*get_state_string(enum e_state state);
void		print_table_row(t_elems *elem);
void		print_table(t_elems *lst);

/* ******************************************** */
/* ----------------:> PARSER <:---------------- */
/* ******************************************** */
void		cmd_nbr(t_elems *elems, t_parser *parser);
char		*turn_env(char *var, t_env *env);
t_parser	*init_cmds(t_elems *elems);
void		set_redir(t_parser *parser, t_elems *elems);
void		set_env(t_elems *elems, t_env *env);
void		set_cmd_args(t_parser *parser, t_elems *elems);
t_parser	*init_parser(t_elems *elems);

/* -----:> LIST REDIR <:-----*/
t_redir		*redir_new(char *file, t_token type);
void		redir_add(t_redir **lst, t_redir *new);
void		redir_del(t_redir **head, t_redir *node);
void		redir_list_free(t_redir *head);

/* -----:> LIST CMD <:-----*/
t_cmd		*cmd_new(t_redir *redir, int argc);
void		cmd_list_add(t_cmd **lst, t_cmd *new);
void		cmd_del(t_cmd **head, t_cmd *node);
void		cmd_list_free(t_cmd *head);

/* *********************************************** */
/* ----------------:> EXECUTION <:---------------- */
/* *********************************************** */

/* -----:> ENV <:-----*/
t_env		*env_new(char *line);
void		env_list_add(t_env **env, t_env *new);

/* -----:> BUILTINS <:-----*/
void		builtins(t_cmd *cmds, t_env *env);
int			is_option(char *str);
void		ft_echo(t_cmd *cmds);
t_env		*get_env(char **env);
void		ft_env(t_cmd *cmd, t_env *env);
void		ft_pwd(t_cmd *cmd);
void		ft_cd(t_cmd *cmd);
void		ft_exit(t_cmd *cmd);
/*export*/
void		ft_export(t_cmd *cmd, t_env *env);
void		set_value(char *var, t_env *env);
int			is_correct(char *word);
void		env_del(t_env **head, t_env *node);
void		ft_unset(t_cmd *cmd, t_env **env);
/*exec*/
int			is_path(char *cmd);
char		**get_path(t_env *env);
int			list_size(t_env *env);
char		**list_to_array(t_env *env);
void		exec_cmd(t_cmd *cmd, t_env *env_list);

#endif