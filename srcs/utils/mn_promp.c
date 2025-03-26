/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mn_promp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:56:55 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/25 11:56:16 by edubois-         ###   ########.fr       */
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
	if (!pwd)
		return (readline(data->prompt));
	if (!data->exit_status)
		prompt = "\e[1;32m➜  \e[93m";
	else
		prompt = "\e[1;31m➜  \e[93m";
	folder = ft_strrchr(pwd, '/') + 1;
	if (!*folder)
		folder = "/";
	prompt = ft_strjoin(prompt, folder);
	prompt = ft_strjoinfree(prompt, "\e[0m ", FREE_S1);
	rl = readline(prompt);
	dh_free(data->prompt);
	data->prompt = prompt;
	free(pwd);
	return (rl);
}
