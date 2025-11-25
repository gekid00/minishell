/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 23:50:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/20 23:56:19 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
