/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 23:04:19 by kforfoli          #+#    #+#             */
/*   Updated: 2025/01/23 23:04:21 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		if (g_execute_external_running == 1)
		{
			printf("\n");
			clear_buffer();
		}
		else
		{
			printf("\n");
			rl_on_new_line();
			clear_buffer();
		}
		g_execute_external_running = 130;
	}
	handle_sigquit(sig);
}

void	handle_sigquit(int sign)
{
	if (sign == SIGQUIT)
	{
		if (g_execute_external_running == 1)
		{
			printf("QUIT\n");
			clear_buffer();
			g_execute_external_running = 131;
		}
		else
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
}
