/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:28:31 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/06/19 13:41:46 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include "minishell.h"

# define RESET "\033[0m"
# define BOLD "\033[1m"
# define DIM "\033[2m"

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

# define BRED "\033[91m"
# define BGREEN "\033[92m"
# define BYELLOW "\033[93m"
# define BBLUE "\033[94m"
# define BMAGENTA "\033[95m"
# define BCYAN "\033[96m"

char	*get_colored_prompt(t_env *env);
char	*get_username(void);
char	*get_current_dir(void);
int		get_last_exit_status(void);
char	*format_prompt_part(char *content, char *color);

#endif