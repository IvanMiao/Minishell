/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:13:33 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/29 04:25:43 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

void	env_free(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		mem_manager(FREE, 0, env->name);
		mem_manager(FREE, 0, env->word);
		mem_manager(FREE, 0, env->content);
		mem_manager(FREE, 0, env);
		env = tmp;
	}
}
