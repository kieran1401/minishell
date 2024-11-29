/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:44:29 by dzinchen          #+#    #+#             */
/*   Updated: 2023/10/18 17:10:29 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char c)
{
	size_t	i;
	size_t	count;
	size_t	reading;

	i = 0;
	count = 0;
	reading = 0;
	while (str[i] != '\0')
	{
		if (!reading && str[i] != c)
		{
			count++;
			reading = 1;
		}
		else if (reading && str[i] == c)
		{
			reading = 0;
		}
		i++;
	}
	return (count);
}

static int	word_len(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

static char	**free_array(char **arr, size_t word)
{
	size_t	i;

	i = 0;
	while (i < word)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}

static char	**copy_word(char const *str, char c, size_t words, char **arr)
{
	size_t	i;
	size_t	j;
	size_t	word;

	i = 0;
	word = 0;
	while (word < words)
	{
		j = 0;
		while (str[i] != '\0' && str[i] == c)
			i++;
		arr[word] = malloc(word_len(&str[i], c) + 1);
		if (!arr[word])
			return (free_array(arr, word));
		while (str[i] != '\0' && str[i] != c)
		{
			arr[word][j] = str[i];
			j++;
			i++;
		}
		arr[word][j] = '\0';
		word++;
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	words;

	words = count_words(s, c);
	arr = malloc((words + 1) * sizeof(char *));
	if (!arr)
		return (0);
	arr[words] = 0;
	if (words > 0)
		arr = copy_word(s, c, words, arr);
	return (arr);
}
