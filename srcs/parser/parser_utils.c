/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:13:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/20 23:56:19 by gekido           ###   ########.fr       */
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

void	print_syntax_error(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token && token->value)
		ft_putstr_fd(token->value, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putendl_fd("'", 2);
	g_signal_status = 2;
}

int	check_redirection_syntax(t_token *redir_token)
{
	if (!redir_token->next)
	{
		print_syntax_error(NULL);
		return (1);
	}
	if (redir_token->type == TOKEN_HEREDOC
		&& is_redirection(redir_token->next->type))
	{
		print_syntax_error(redir_token->next);
		return (1);
	}
	if (redir_token->next->type != TOKEN_WORD)
	{
		print_syntax_error(redir_token->next);
		return (1);
	}
	return (0);
}
