/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc_pre.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:16:04 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/06/21 00:57:12 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*generate_temp_filename(void)
{
	static int	counter = 0;
	char		*filename;
	char		*num_str;

	num_str = ft_itoa(counter++);
	if (!num_str)
		return (NULL);
	filename = ft_strjoin("/tmp/minishell_heredoc_", num_str);
	free(num_str);
	return (filename);
}

void	heredoc_signal_handler(int sig)
{
	(void)sig;
	g_signal_status = 130;
	printf("\r> ^C\n");
	close(STDIN_FILENO);
}

static int	setup_heredoc_files(char **temp_file, int *fd, int *original_stdin)
{
	*temp_file = generate_temp_filename();
	if (!*temp_file)
		return (1);
	*fd = open(*temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (*fd == -1)
	{
		free(*temp_file);
		return (1);
	}
	*original_stdin = dup(STDIN_FILENO);
	if (*original_stdin == -1)
	{
		close(*fd);
		free(*temp_file);
		return (1);
	}
	return (0);
}

static int	process_single_heredoc(t_redir *redir)
{
	char	*temp_file;
	int		fd;
	int		original_stdin;
	int		result;

	if (setup_heredoc_files(&temp_file, &fd, &original_stdin) != 0)
		return (1);
	result = handle_heredoc_input(redir, fd, original_stdin);
	close(original_stdin);
	close(fd);
	setup_signals();
	if (result == 1)
	{
		unlink(temp_file);
		free(temp_file);
		return (1);
	}
	free(redir->file);
	redir->file = temp_file;
	redir->type = TOKEN_REDIR_IN;
	return (0);
}

int	preprocess_heredocs_in_node(t_ast_node *node)
{
	t_redir	*redir;

	if (!node)
		return (0);
	if (node->type == NODE_COMMAND && node->redirects)
	{
		redir = node->redirects;
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC)
			{
				if (process_single_heredoc(redir) != 0)
					return (1);
			}
			redir = redir->next;
		}
	}
	if (node->left && preprocess_heredocs_in_node(node->left) != 0)
		return (1);
	if (node->right && preprocess_heredocs_in_node(node->right) != 0)
		return (1);
	return (0);
}
