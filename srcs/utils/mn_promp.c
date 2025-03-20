/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mn_promp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:56:55 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/20 15:00:41 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*bt_prompt(t_data *data)
{
	char	*prompt;
	char	*folder;
	char	*rl;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!data->exit_status)
		prompt = "\e[1;32m➜  \e[1;36m";
	else
		prompt = "\e[1;31m➜  \e[1;36m";
	folder = ft_strrchr(pwd, '/') + 1;
	if (!*folder)
		folder = "/";
	prompt = ft_strjoin(prompt, folder);
	prompt = ft_strjoinfree(prompt, "\e[0m ", FREE_S1);
	rl = readline(prompt);
	dh_free(prompt);
	free(pwd);
	return (rl);
}
