/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_words_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:00:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/17 01:03:16 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	append_quote_to_word(char **word, char quote)
{
	char	*tmp;
	char	quote_str[2];

	quote_str[0] = quote;
	quote_str[1] = '\0';
	if (!*word)
	{
		*word = ft_strdup(quote_str);
		return ;
	}
	tmp = *word;
	*word = ft_strjoin(*word, quote_str);
	free(tmp);
}

void	append_quoted_content(char *input, int *i, char **word, char quote)
{
	char	*tmp;
	char	*content;
	int		start;
	int		len;

	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	len = *i - start;
	if (len > 0)
	{
		content = malloc(len + 1);
		if (!content)
			return ;
		ft_strlcpy(content, input + start, len + 1);
		if (!*word)
			*word = content;
		else
		{
			tmp = *word;
			*word = ft_strjoin(*word, content);
			free(tmp);
			free(content);
		}
	}
}

void	handle_quotes(char *input, int *i, char **word)
{
	char	quote;

	quote = input[*i];
	append_quote_to_word(word, quote);
	(*i)++;
	append_quoted_content(input, i, word, quote);
	if (input[*i] == quote)
	{
		append_quote_to_word(word, quote);
		(*i)++;
	}
}
