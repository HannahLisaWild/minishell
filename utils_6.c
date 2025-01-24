/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:18:18 by kforfoli          #+#    #+#             */
/*   Updated: 2025/01/24 15:23:40 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest2;
	unsigned char	*src3;
	size_t			i;

	if (dest == (void *)0 && src == (void *)0)
		return (dest);
	dest2 = (unsigned char *)dest;
	src3 = (unsigned char *)src;
	i = 0;
	while (n > i)
	{
		dest2[i] = src3[i];
		i++;
	}
	return ((void *)dest);
}

static size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (len < maxlen && s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strndup(const char *src, size_t n)
{
	size_t	len;
	char	*dest;

	len = ft_strnlen(src, n);
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, src, len);
	dest[len] = '\0';
	return (dest);
}
