/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_env_to_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:41:00 by hawild            #+#    #+#             */
/*   Updated: 2025/01/23 21:53:31 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env_vars(t_envvar **env_list)
{
	int			env_count;
	t_envvar	*current;

	env_count = 0;
	current = *env_list;
	while (current != NULL)
	{
		env_count++;
		current = current->next;
	}
	return (env_count);
}

char	**allocate_env_array(int env_count)
{
	char	**envp;

	envp = malloc((env_count + 1) * sizeof(char *));
	if (!envp)
	{
		printf("malloc");
		return (NULL);
	}
	return (envp);
}

int	populate_env_array(char **envp, t_envvar **env_list)
{
	t_envvar	*current;
	int			i;
	size_t		len;

	i = 0;
	current = *env_list;
	while (current != NULL)
	{
		len = ft_strlen(current->key) + ft_strlen(current->value) + 2;
		envp[i] = malloc(len);
		if (!envp[i])
		{
			perror("malloc");
			envp[i] = NULL;
			return (-1);
		}
		ft_strcpy(envp[i], current->key);
		ft_strcat(envp[i], "=");
		ft_strcat(envp[i], current->value);
		i++;
		current = current->next;
	}
	return (0);
}

char	**convert_env_list_to_array(t_envvar **env_list)
{
	int		env_count;
	char	**envp;

	env_count = count_env_vars(env_list);
	envp = allocate_env_array(env_count);
	if (!envp)
		return (NULL);
	if (populate_env_array(envp, env_list) == -1)
	{
		free(envp);
		return (NULL);
	}
	envp[env_count] = NULL;
	return (envp);
}

char	**get_envp(t_envvar **env_list)
{
	char	**envp;

	envp = convert_env_list_to_array(env_list);
	if (!envp)
		return (NULL);
	return (envp);
}
