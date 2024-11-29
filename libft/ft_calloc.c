/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:31:35 by dzinchen          #+#    #+#             */
/*   Updated: 2023/10/07 17:22:43 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;
	size_t	memory;

	memory = nmemb * size;
	mem = malloc(memory);
	if (mem == 0)
		return (0);
	ft_bzero(mem, memory);
	return (mem);
}
