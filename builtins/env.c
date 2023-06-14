/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:30:40 by msodor            #+#    #+#             */
/*   Updated: 2023/06/14 20:34:33 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*get_env(char **env)
{
	int		i;
	int		end;
	t_env	*lst = NULL;
	t_env	*new_env;
	char	*value;

	// lst = malloc(sizeof(t_env));
	// new_env = malloc(sizeof(t_env));
	i = 0;
	end = 0;
	while (env[i])
	{
		end = ft_strchr(env[i], '=');
		if (end == -1)
			value = NULL;
		else
			value = ft_substr(env[i], end + 1, ft_strlen(env[i]) - end);
		new_env = env_new(ft_substr(env[i], 0, end), value);
			printf("TTTT -1 %s\n", new_env->value);
		if (!lst)
		{
			lst = malloc(sizeof(t_env));
			lst->value = new_env->value;
			lst->key = new_env->key;
			lst->next = NULL;
			// lst = new_env;
		}
		else
		{
			t_env *tmp = lst;
			while (tmp->next)
				tmp = tmp->next;
			t_env *added = malloc(sizeof(t_env));
			added->value = new_env->value;
			added->key = new_env->key;
			added->next = NULL;
			tmp = added;
		}
		// t_env *gza = lst;
		// while (gza)
		// {
		// 	printf("TTTT -1 %s\n", gza->value);
		// 	gza = gza->next;
		// }
		// env_list_add(&lst, new_env);
		i++;
	}
		// 	t_env *gza = lst;
		// while (gza)
		// {
		// 	gza = gza->next;
		// }
	return (lst);
}
// int main(int ac, char **av, char **env)
// {
// 	t_env *env_list = get_env(env);
// 	while (env_list && env_list->next)
// 	{
// 		env_list = env_list->next;
// 		printf("%s=%s\n", env_list->key, env_list->value);
// 	}
// }
void	ft_env(t_cmd *cmd, t_env *env)
{
	if (!cmd->args[0])
	{
		while (env && env->next)
		{
			env = env->next;
			printf("%s=%s\n", env->key, env->value);
		}
	}
	else
		printf("env: incorrect number of argumments");
}
