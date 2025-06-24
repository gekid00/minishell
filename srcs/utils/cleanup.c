/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:01:31 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/06/25 00:05:22 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cleanup_child_process(t_env *env)
{
	if (!env)
		return ;
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
}

void	cleanup_on_exit(t_env *env)
{
	if (!env)
		return ;
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
}

void	cleanup_temp_files(t_ast_node *node)
{
	t_redir	*redir;

	if (!node)
		return ;
	if (node->type == NODE_COMMAND && node->redirects)
	{
		redir = node->redirects;
		while (redir)
		{
			if (redir->file && ft_strncmp(redir->file,
					"/tmp/minishell_heredoc_", 23) == 0)
				unlink(redir->file);
			redir = redir->next;
		}
	}
	if (node->left)
		cleanup_temp_files(node->left);
	if (node->right)
		cleanup_temp_files(node->right);
}
