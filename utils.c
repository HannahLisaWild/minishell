/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:52:33 by hawild            #+#    #+#             */
/*   Updated: 2025/01/23 22:34:24 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s)
{
	char	*d;

	d = malloc(ft_strlen(s) + 1);
	if (d)
		ft_strcpy(d, s);
	return (d);
}

int	is_string(char *str)
{
	char	*cpy;
	int		i;
	int		j;

	cpy = ft_strdup(str);
	i = 0;
	j = 0;
	while (cpy[i])
	{
		if (isalpha(cpy[i]))
			j++;
		i++;
	}
	free(cpy);
	if (j != 0)
		return (j);
	return (0);
}

int	is_valid(char *inp)
{
	char	*cpy;
	int		i;
	int		j;

	cpy = ft_strdup(inp);
	i = 0;
	j = 0;
	while (cpy[j] >= '0' && cpy[j] <= '9')
		j++;
	if (cpy[j] == '\0' || cpy[j] == '=')
		return (0);
	while (cpy[i] != '\0' && cpy[i] != '=')
	{
		if (ft_isalnum(cpy[i]) != 0)
			i++;
		else
			cpy[i] = '\0';
	}
	if (i == (int)ft_strlen(inp) || cpy[i] == '=')
		return (1);
	else
		return (0);
}

int	ft_error(t_command *cmd, const char *str)
{
	perror(str);
	cmd->exit_status = 1;
	return (1);
}

char	*ft_read_input(void)
{
	char	*input;

	input = readline("minishell>");
	if (input && *input)
		add_history(input);
	return (input);
}
