/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:12:59 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/24 19:52:12 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

/* @brief Checks if a character is alphabetical
	@param c The character to be checked
	@return 1 if the character is Capital letter
	@return 2 if the character is lowercase
	, 0 if not
 */
int	ft_isalpha(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return (1);
	}
	else if (c >= 'a' && c <= 'z')
	{
		return (2);
	}
	else
	{
		return (0);
	}
}
/*
int main(void)
{
    int a;

    a = '0';
    printf("is alpha?: %i", isalpha(a));
}*/
