/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:44:31 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/26 10:16:41 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	cmd_unset(t_data *data, char **cmds)
{
	int	i;

	i = 1;
	while (cmds[i])
		ms_remove_env(data, cmds[i++]);
	ms_build_array_env(data);
	return (0);
}
