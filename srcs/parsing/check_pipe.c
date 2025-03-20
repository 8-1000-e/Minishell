/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:59:26 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/18 10:01:52 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_pipe(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (data->cmd_list[i].cmd && ((data->cmd_list[i].cmd[0][0] != '|')
		|| ((data->cmd_list[i].cmd[0][0] == '|')
		&& (data->cmd_list[i + 1].cmd
			&& data->cmd_list[i + 1].cmd[0][0] != '|'))))
		i++;
	if (data->cmd_list[i].cmd && ft_charite(line, '|'))
	{
		ft_printf(2, BOLD RED"/!\\ "
			BOLD BEIGE "Shellokitty: syntax error near \"|\"\n" RESET);
		data->exit_status = 2;
		return (1);
	}
	return (0);
}
