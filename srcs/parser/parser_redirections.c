/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:55:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/25 00:02:18 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIR_OUT || type == TOKEN_REDIR_IN
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

int	has_redirection_tokens(t_token *token)
{
	while (token && token->type != TOKEN_PIPE)
	{
		if (is_redirection(token->type))
			return (1);
		token = token->next;
	}
	return (0);
}

t_redir	*create_and_append_redirection(t_redir *redirections, t_token *token)
{
	t_redir	*new_redir;

	new_redir = create_redirection(token->type, token->next->value);
	if (!new_redir)
		return (NULL);
	return (append_redirections(redirections, new_redir));
}

t_redir	*parse_redirections(t_token **token)
{
	t_redir	*redirections;

	redirections = NULL;
	while (*token && (*token)->type != TOKEN_PIPE)
	{
		if (is_redirection((*token)->type))
		{
			if (check_redirection_syntax(*token))
				return (free_redirections(redirections), NULL);
			redirections = create_and_append_redirection(redirections, *token);
			if (!redirections)
				return (free_redirections(redirections), NULL);
			*token = (*token)->next->next;
		}
		else
			*token = (*token)->next;
	}
	return (redirections);
}
