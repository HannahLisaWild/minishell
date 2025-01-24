/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:55:27 by hawild            #+#    #+#             */
/*   Updated: 2025/01/23 21:49:46 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

void	free_commands(t_command *commands)
{
	t_command	*current;
	t_command	*next;
	int			i;

	current = commands;
	while (current)
	{
		next = current->next;
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				free(current->args[i]);
				current->args[i] = NULL;
				i++;
			}
			free(current->args);
		}
		free_file(current);
		free(current);
		current = next;
	}
}

void	ft_free(t_envvar **env_list)
{
	t_envvar	*current;
	t_envvar	*next_node;

	current = *env_list;
	while (current)
	{
		next_node = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next_node;
	}
}

void	cleanup_iteration(char **input, t_token *tokens, t_command *commands)
{
	free_tokens(tokens);
	tokens = NULL;
	free_commands(commands);
	commands = NULL;
	free(*input);
	*input = NULL;
}

void	cleanup_shell(t_envvar **env_list, t_builtin_cmd *builtins)
{
	int	i;

	ft_free(env_list);
	i = 0;
	while (i < NUM_BUILTINS)
	{
		free(builtins[i].name);
		i++;
	}
}
