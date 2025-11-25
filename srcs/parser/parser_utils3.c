/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 23:45:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/20 23:56:19 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_redir	*create_and_append_redirection(t_redir *redirects, t_token *token)
{
	t_redir	*new_redir;

	new_redir = create_redirection(token->type, token->next->value);
	if (!new_redir)
		return (NULL);
	return (append_redirections(redirects, new_redir));
}

t_redir	*parse_redirections(t_token **token)
{
	t_redir	*redirects;

	redirects = NULL;
	while (*token && (*token)->type != TOKEN_PIPE)
	{
		if (is_redirection((*token)->type))
		{
			if (check_redirection_syntax(*token))
				return (free_redirections(redirects), NULL);
			redirects = create_and_append_redirection(redirects, *token);
			if (!redirects)
				return (free_redirections(redirects), NULL);
			*token = (*token)->next->next;
		}
		else
			*token = (*token)->next;
	}
	return (redirects);
}
