/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeris <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:28:40 by haeris            #+#    #+#             */
/*   Updated: 2022/04/09 15:35:33 by haeris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 2);
	if (!line)
		return (0);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_get_new_str(char *str)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = ft_strlen(str);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (0);
	}
	new_line = (char *)malloc(sizeof(char) * (j - i) + 1);
	if (!new_line)
		return (0);
	j = 0;
	i++;
	while (str[i] != '\0')
		new_line[j++] = str[i++];
	new_line[j] = '\0';
	free(str);
	return (new_line);
}

char	*ft_get_read(int fd, char *str)
{
	int		count;
	char	*now_str;

	now_str = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!now_str)
		return (0);
	count = 1;
	while (!ft_strchr(str, '\n') && count != 0)
	{
		count = read(fd, now_str, BUFFER_SIZE);
		if (count == -1)
		{
			free (now_str);
			return (0);
		}
		now_str[count] = '\0';
		str = ft_strjoin(str, now_str);
	}
	free(now_str);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 && BUFFER_SIZE <= 0)
		return (0);
	str = ft_get_read(fd, str);
	if (!str)
		return (0);
	line = ft_get_line(str);
	str = ft_get_new_str(str);
	return (line);
}
/*int main()
{
	int a = open("a.txt", O_RDONLY, 0777);
	char	*str = get_next_line(a);
	int count = 1;


	while (*str)
	{

		if ( count == 3)
		{
			printf("%s", str);
			return (0);
		}
	count += 1;
	str = get_next_line(a);
	}
}
*/
/*int main()
{
	int a = open("a.txt", O_RDONLY, 0777);
	char	*str = get_next_line(a);
	char	**new;
	int count = 1;
	size_t	i = 0;

	new = (char **)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!new)
		return (0);
	while (*str)
	{
		new[i++] = str;
		str = get_next_line(a);
		if (str ==  NULL)
		{
			printf("%s", new[i - 1]);
			return (0);
		}
	}
	free(str);

}*/
