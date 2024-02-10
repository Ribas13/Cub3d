/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:22:42 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/10 15:16:01 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	map_check(char *mapFile)
{
	(void)mapFile;
	return (false);
}

bool	valid_type(char *file)
{
	int	i;

	i = 0;
	while (file[i] != '\0')
	{
		if (file[i] == '.')
		{
			if (file[i + 1] == 'c' && file[i + 2] == 'u'
				&& file[i + 3] == 'b' && file[i + 4] == '\0')
				return (true);
			else
				return (false);
		}
		i++;
	}
	return (false);
}

void	error(char *error_msg)
{
	printf("%s\n", error_msg);
}

/* Check for invalid number of args
Check for invalid extension */
bool	valid_map(int ac, char **av)
{
	if (ac != 2)
	{
		error("Invalid number of arguments");
		return (false);
	}
	else if (!valid_type(av[1]))
	{
		error("File must be '.cub'");
		return (false);
	}
	/* else if (!map_check(av[1]))
	{
		error("Invalid map format! Map can only contain");
		error("1 - Wall");
		error("0 - Open space");
		error("N, S, E, W - Player spawn and direction");
		return (false);
	} */
	return (true);
}
