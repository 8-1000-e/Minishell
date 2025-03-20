/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:10:52 by edubois-          #+#    #+#             */
/*   Updated: 2025/02/06 16:29:07 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	has_flag(char *str, int index_flag, int index)
{
	if (*str != '-' || (index != 1 && index_flag != index - 1))
		return (0);
	str++;
	while (*str && *str == 'n')
		str++;
	return (!*str);
}

void	echo(char **cmds)
{
	int		index_flag;
	char	**save_cmds;

	save_cmds = cmds;
	index_flag = 0;
	if (!ft_strcmp(*cmds, "echo"))
		return ;
	while (*++cmds)
	{
		if (has_flag(*cmds, index_flag, cmds - save_cmds))
		{
			index_flag = cmds - save_cmds;
			continue ;
		}
		write(1, *cmds, ft_strlen(*cmds));
		if (*(cmds + 1))
			write(1, " ", 1);
	}
	if (!index_flag)
		write(1, "\n", 1);
}

// int	main(int c, char **v)
// {
// 	char	**cmd;
// 	cmd = NULL;
// 	int i = 1;
// 	while(i < c)
// 		ft_strapp(&cmd,ft_strdup(v[i++]));
// 	echo(cmd);
// 	ft_free_tab(cmd);
// }