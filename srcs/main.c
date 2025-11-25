/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:08:55 by gekido            #+#    #+#             */
/*   Updated: 2025/06/23 11:01:09 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_signal_status = 0;

void	clean_all(t_env *env, t_token *tokens, t_ast_node *ast)
{
	if (ast)
		free_ast(ast);
	if (tokens)
		free_tokens(tokens);
	if (env)
		free_env(env);
	rl_clear_history();
}

void	handle_command(char *input, t_env *env)
{
	t_token		*tokens;
	t_token		*first_non_empty;
	t_ast_node	*ast;

	add_history(input);
	tokens = lexer(input);
	if (!tokens)
		return ;
	expand_token_variables(tokens, env);
	first_non_empty = get_first_non_empty_token(tokens);
	if (check_unknown_command(first_non_empty, env))
	{
		free_tokens(tokens);
		return ;
	}
	ast = parser(tokens);
	free_tokens(tokens);
	if (ast)
		execute_ast(ast, env);
	free_ast(ast);
}

int	run_minishell_loop(t_env *env)
{
	char	*input;
	char	*prompt;

	printbanner();
	while (1)
	{
		prompt = get_colored_prompt(env);
		if (!prompt)
			prompt = ft_strdup("minishell$ ");
		input = readline(prompt);
		free(prompt);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (!process_input(input, env))
			break ;
		if (should_exit())
			break ;
	}
	return (get_exit_code());
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	int		exit_code;

	(void)argc;
	(void)argv;
	if (isatty(0) == 0 || isatty(1) != 1 || isatty(2) != 1)
	{
		printf("Erreur.\n");
		return (EXIT_FAILURE);
	}
	env = init_env(envp);
	if (!env)
		return (1);
	setup_signals();
	exit_code = run_minishell_loop(env);
	free_env(env);
	rl_clear_history();
	return (exit_code);
}
