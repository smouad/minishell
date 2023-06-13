/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 01:42:00 by msodor            #+#    #+#             */
/*   Updated: 2023/06/13 02:14:13 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	array_sise(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**resize_env(char **env)
{
	char	**new_env;
	int		size;
	int		i;

	size = array_sise(env) + 1
	new_env = (char **)malloc(size * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while(env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	return (new_env);
}

void	