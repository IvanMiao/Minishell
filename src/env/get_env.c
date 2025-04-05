/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:21:43 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/04 16:24:47 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

char	*ft_get_env(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strlen(env->name) == ft_strlen(name))
		{
			if (ft_strncmp(env->name, name, ft_strlen(name)) == 0)
				return (env->word);
		}
		env = env->next;
	}
	return (NULL);
}
