/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:13:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/17 01:03:16 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_word_tokens(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_WORD && token->value
			&& ft_strlen(token->value) > 0)
			count++;
		else if (is_redirection(token->type))
		{
			token = token->next;
			if (token && token->type == TOKEN_WORD)
				token = token->next;
			continue ;
		}
		token = token->next;
	}
	return (count);
}

char	**extract_args(t_token **token, int count)
{
	return (extract_args_safe(token, count));
}

t_redir	*append_redirections(t_redir *list, t_redir *new)
{
	t_redir	*current;

	if (!list)
		return (new);
	if (!new)
		return (list);
	current = list;
	while (current->next)
		current = current->next;
	current->next = new;
	return (list);
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
			if (!(*token)->next || (*token)->next->type != TOKEN_WORD)
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
