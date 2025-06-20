/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_external.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:55:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/20 16:06:56 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**duplicate_env_vars(char **env_vars)
{
	char	**dup_env;
	int		count;
	int		i;

	if (!env_vars)
		return (NULL);
	count = 0;
	while (env_vars[count])
		count++;
	dup_env = allocate_env_array(count);
	if (!dup_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		dup_env[i] = ft_strdup(env_vars[i]);
		if (!dup_env[i])
			return (free_partial_env(dup_env, i), NULL);
		i++;
	}
	dup_env[count] = NULL;
	return (dup_env);
}

t_child_data	*prepare_child_data(t_ast_node *node, t_env *env)
{
	t_child_data	*data;

	data = init_child_data();
	if (!data)
		return (NULL);
	data->path = find_path(node->args[0], env->vars);
	if (!data->path)
		return (free_child_data(data), NULL);
	data->args = allocate_and_copy_args(node->args);
	if (!data->args)
		return (free_child_data(data), NULL);
	data->env_vars = duplicate_env_vars(env->vars);
	if (!data->env_vars)
		return (free_child_data(data), NULL);
	return (data);
}

void	minimal_child_process(t_child_data *data, t_env *env)
{
	if (env->ast_cleanup)
	{
		free_ast(env->ast_cleanup);
		env->ast_cleanup = NULL;
	}
	if (env->env_cleanup)
	{
		free_env(env->env_cleanup);
		env->env_cleanup = NULL;
	}
	free_env(env);
	rl_clear_history();
	if (execve(data->path, data->args, data->env_vars) == -1)
	{
		ft_putstr_fd("minishell: error executing: ", 2);
		ft_putendl_fd(data->args[0], 2);
		free_child_data(data);
		exit(126);
	}
}

void	execute_external(t_ast_node *node, t_env *env)
{
	t_child_data	*child_data;

	signal(SIGINT, sigint_handler_no_print);
	child_data = prepare_child_data(node, env);
	if (!child_data)
	{
		handle_command_not_found(node);
		return ;
	}
	execute_fork_process(child_data, env);
	setup_signals();
}
