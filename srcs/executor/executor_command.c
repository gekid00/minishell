/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:40:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/17 01:03:16 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_ast(t_ast_node *node, t_env *env)
{
	if (!node)
		return (0);
	env->ast_cleanup = node;
	if (node->type == NODE_COMMAND)
		g_signal_status = execute_command(node, env);
	else if (node->type == NODE_PIPE)
		g_signal_status = execute_pipe(node, env);
	else
		g_signal_status = 1;
	env->ast_cleanup = NULL;
	return (g_signal_status % 256);
}

int	execute_builtin(char **args, t_env *env)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (echo_builtin(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (cd_builtin(args, env));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (pwd_builtin());
	else if (ft_strcmp(args[0], "export") == 0)
		return (export_builtin(args, env));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (unset_builtin(args, env));
	else if (ft_strcmp(args[0], "env") == 0)
		return (env_builtin(env));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (exit_builtin(args, env));
	return (1);
}

int	execute_command_node(t_ast_node *node, t_env *env)
{
	char	**args;
	int		result;

	args = node->args;
	if (!args || !args[0])
		return (0);
	result = handle_dot_command(args);
	if (result != 0)
		return (result);
	if (is_builtin(args[0]))
		return (execute_builtin_safe(args, env));
	else
		execute_external(node, env);
	return (g_signal_status % 256);
}

int	execute_command(t_ast_node *node, t_env *env)
{
	int		result;

	if (!node->redirects)
		return (execute_command_node(node, env));
	if (setup_command_redirections(node, env) != 0)
		return (1);
	result = execute_command_node(node, env);
	update_exit_status(result);
	restore_std_fds(env->saved_stdin, env->saved_stdout);
	return (g_signal_status % 256);
}

int	execute_command_child(t_ast_node *node, t_env *env)
{
	int		result;

	if (setup_redirections(node->redirects, env) != 0)
		return (1);
	result = execute_command_node(node, env);
	update_exit_status(result);
	return (g_signal_status % 256);
}
