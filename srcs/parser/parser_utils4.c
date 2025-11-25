/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 01:00:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/21 00:57:12 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node	*handle_pipe_parsing(t_ast_node *left, t_token **tokens)
{
	t_ast_node	*right;

	skip_to_next_token(tokens, 1);
	if (!*tokens)
	{
		print_syntax_error(NULL);
		free_ast(left);
		return (NULL);
	}
	right = parser(*tokens);
	if (!right)
	{
		print_syntax_error(NULL);
		free_ast(left);
		return (NULL);
	}
	return (create_pipe_node(left, right));
}
