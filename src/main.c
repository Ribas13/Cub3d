/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:01:29 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/10 19:38:49 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* To do:

1. Finish map validation(gnl, etc)
2. Open window and draw map */

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	//valid_map(ac, av);
	if (ft_strchr("10NSWE", 'N') == NULL)
		printf("NULL\n");
	else
		printf("found letter\n");
	printf("Hreeee\n");
}
