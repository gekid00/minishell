/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:29:21 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/06/19 13:42:03 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/colors.h"

static void	free_prompt_parts(char *user_part, char *dir_part, char *arrow)
{
	if (user_part)
		free(user_part);
	if (dir_part)
		free(dir_part);
	if (arrow)
		free(arrow);
}

static char	*build_final_prompt(char *user_part, char *dir_part, char *arrow)
{
	char	*temp1;
	char	*temp2;
	char	*result;

	temp1 = ft_strjoin(user_part, " ");
	temp2 = ft_strjoin(temp1, dir_part);
	free(temp1);
	temp1 = ft_strjoin(temp2, " ");
	free(temp2);
	result = ft_strjoin(temp1, arrow);
	free(temp1);
	return (result);
}

char	*get_colored_prompt(t_env *env)
{
	char	*user;
	char	*dir;
	char	*parts[3];
	char	*result;

	(void)env;
	user = get_username();
	dir = get_current_dir();
	parts[0] = format_prompt_part(user, BOLD BCYAN);
	parts[1] = format_prompt_part(dir, BOLD BMAGENTA);
	if (get_last_exit_status() == 0)
		parts[2] = format_prompt_part("➜ ", BGREEN);
	else
		parts[2] = format_prompt_part("➜ ", BRED);
	free(dir);
	if (!parts[0] || !parts[1] || !parts[2])
	{
		free_prompt_parts(parts[0], parts[1], parts[2]);
		return (ft_strdup("minishell$ "));
	}
	result = build_final_prompt(parts[0], parts[1], parts[2]);
	free_prompt_parts(parts[0], parts[1], parts[2]);
	return (result);
}
