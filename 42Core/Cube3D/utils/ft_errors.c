/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:27:50 by jsarda            #+#    #+#             */
/*   Updated: 2024/08/21 12:33:19 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_errors(t_sys *sys, char *message, int error_status)
{
	free_all(sys);
	printf("%s\n", message);
	exit(error_status);
}
