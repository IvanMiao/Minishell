/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:35:53 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/16 03:12:01 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// --- define a state machine ---
# define ST_GENERAL	1
# define ST_IN_SQ	2
# define ST_IN_DQ	3

//
# define EXPAND_DOLLAR		4
# define EXPAND_IN_GENARAL	5
# define UPDATE_WORD		6
#endif