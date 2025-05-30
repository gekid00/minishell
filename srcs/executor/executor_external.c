/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_external.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourkai <rbourkai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:55:00 by gekido            #+#    #+#             */
/*   Updated: 2025/05/28 18:01:38 by rbourkai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_external_direct(t_ast_node *node, t_env *env)
{
	char	*path;
	char	**envp;

	path = find_path(node->args[0], env->vars);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(node->args[0], 2);
		g_signal_status = 127;
		exit(127);
	}
	envp = convert_env_to_array(env);
	if (execve(path, node->args, envp) == -1)
	{
		ft_putstr_fd("minishell: error executing: ", 2);
		ft_putendl_fd(node->args[0], 2);
		free(path);
		exit(126);
	}
	free(path);
}

void	execute_external(t_ast_node *node, t_env *env)
{
	pid_t	pid;

	signal(SIGINT, sigint_handler_no_print);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		child_process(node, env);
	else
		parent_process(pid, env);
	setup_signals();
}
