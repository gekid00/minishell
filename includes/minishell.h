/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:04:08 by gekido            #+#    #+#             */
/*   Updated: 2025/06/23 11:00:48 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "executor.h"
# include "expand.h"
# include "lexer.h"
# include "parser.h"
# include "colors.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_env		t_env;
typedef struct s_child_data	t_child_data;
typedef struct s_token		t_token;
typedef struct s_ast_node	t_ast_node;

extern int					g_signal_status;

void			cleanup_on_exit(t_env *env);
void			cleanup_child_process(t_env *env);

char			*read_line_non_interactive(void);
void			sigint_handler_no_print(int sig);
void			printbanner(void);
int				handle_input(char *input, char **envp);
void			restore_std_fds(int saved_stdin, int saved_stdout);
int				should_exit(void);
int				get_exit_code(void);
int				process_input(char *input, t_env *env);
void			handle_command(char *input, t_env *env);
t_token			*get_first_non_empty_token(t_token *tokens);
int				check_unknown_command(t_token *first_non_empty, t_env *env);
void			close_fd(int fd1, int fd2);
void			clean_all(t_env *env, t_token *tokens, t_ast_node *ast);
int				is_unknown_cmd(t_token *tokens, t_env *env);
void			handle_direct_path_error(char *cmd);
char			**expand_env_tab(char **old, char *new_var, int size);
void			print_invalid(char *var);
int				find_and_replace_env_var(t_env *env, char *var, char *new,
					int klen);
int				key_len(const char *s);
int				process_n_option(char **args);
void			print_echo_args(char **args, int start_index);
int				is_numeric(const char *str);
int				is_valid_n_option(char *arg);
void			handle_exit_status(char **result, int *i);
void			handle_digit_variable(int *i);
void			handle_regular_variable(char *str, int *i, char **result,
					t_env *env);
void			update_quote_status(char c, bool *in_single, bool *in_double);
int				execute_ast_child(t_ast_node *node, t_env *env);
int				handle_dot_command(char **args);
int				execute_builtin_safe(char **args, t_env *env);
int				setup_command_redirections(t_ast_node *node, t_env *env);
void			update_exit_status(int result);

void			free_child_data(t_child_data *data);
char			**allocate_and_copy_args(char **node_args);
t_child_data	*init_child_data(void);
void			parent_process(pid_t pid, t_env *env);
void			handle_command_not_found(t_ast_node *node);
void			execute_fork_process(t_child_data *child_data, t_env *env);
void			minimal_child_process(t_child_data *data, t_env *env);
void			free_partial_env(char **dup_env, int count);
char			**allocate_env_array(int count);
void			free_array(char **arr);
char			**convert_env_to_array(t_env *env);

char			**extract_args_safe(t_token **token, int count);
int				is_redirection(t_token_type type);

void			append_quote_to_word(char **word, char quote);
void			append_quoted_content(char *input, int *i, char **word,
					char quote);
void			handle_quotes(char *input, int *i, char **word);

#endif