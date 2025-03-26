/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_var_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:09:23 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/26 13:37:06 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	is_env_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

char	*build_var_env(char *str, t_data data)
{
	char	*str1;
	char	*str2;

	str1 = replace_var_env(str, data);
	str2 = epurstr(str1);
	dh_free(str1);
	return (str2);
}

char	*get_env(char *str, t_data data)
{
	char	*env;

	if (ft_strcmp(str, "?"))
		env = ft_itoa(data.exit_status);
	else
		env = ms_get_env(data, str);
	dh_free(str);
	if (!env)
		return ("");
	return (env);
}

void	check_quotes(char *str, int i, int *dquote, int *quote)
{
	if (str[i] == '"')
	{
		if (*dquote == -1)
			*dquote = i;
		else
			*dquote = -1;
	}
	else if (str[i] == '\'')
	{
		if (*quote == -1)
			*quote = i;
		else
			*quote = -1;
	}
}
