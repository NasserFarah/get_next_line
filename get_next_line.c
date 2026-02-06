#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;
	size_t	i;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	*readfd(int fd, char *line)
{
	char		*save;
	ssize_t		countread;

	save = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!save)
		return (free(line), NULL);
	countread = 1;
	while (countread > 0 && !ft_strchr(line, '\n'))
	{
		countread = read(fd, save, BUFFER_SIZE);
		if (countread > 0)
		{
			save[countread] = '\0';
			line = ft_strjoin(line, save);
			if (!line)
				return (free(save), free(line), NULL);
		}
	}
	if (countread == 0 && (!line || !*line))
		return (free(save), free(line), NULL);
	if (countread < 0)
		return (free(line), free(save), NULL);
	return (free(save), line);
}

static char	*init(int fd, char **line)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!*line)
		*line = ft_strdup("");
	if (!*line)
		return (NULL);
	*line = readfd(fd, *line);
	if (!*line)
		return (NULL);
	return (*line);
}

char	*get_next_line(int f)
{
	static char	*line[1024];
	char		*nextline;
	char		*current;

	line[f] = init(f, &line[f]);
	if (!line[f])
		return (NULL);
	if (ft_strchr(line[f], '\n'))
	{
		current = ft_substr(line[f], 0, ft_strchr(line[f], 10) - line[f] + 1);
		nextline = ft_strdup(ft_strchr(line[f], '\n') + 1);
		if (!nextline || !current)
			return (free(line[f]), free(current), free(nextline), NULL);
		free(line[f]);
		line[f] = nextline;
	}
	else
	{
		current = ft_strdup(line[f]);
		if (!current)
			return (free(line[f]), line[f] = NULL, NULL);
		free(line[f]);
		line[f] = NULL;
	}
	return (current);
}
// #include <stdio.h>
// #include <fcntl.h>

// int  main(int ac, char **av)
// {
//     if (ac < 0 || !av)
//         return (0);
//     printf("%s", get_next_line(1));
//     int fdd = open("test.txt", O_RDONLY);
//     int fd = open("file.txt", O_RDONLY);
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fdd));
//     printf("%s", get_next_line(fd));
//     close(fd);
//     close(fdd);
//     return (0);
// }
/*
#include <stdio.h>
#include <fcntl.h>

int main(int ac, char **av)
{
    char *result;
    
    if (ac < 2 || !av)  // Changed: ac should be >= 2 if you expect arguments
        return (0);
    
    // Test reading from stdin (fd 1 is stdout, fd 0 is stdin)
    printf("Reading from stdin: ");
    result = get_next_line(0);  // Changed: 0 for stdin, not 1
    if (result)
    {
        printf("%s", result);
        free(result);
    }
    
    // Open files
    int fdd = open("test.txt", O_RDONLY);
    int fd = open("file.txt", O_RDONLY);
    
    if (fd < 0 || fdd < 0)  // Added: check if files opened successfully
    {
        printf("Error opening files\n");
        if (fd >= 0) close(fd);
        if (fdd >= 0) close(fdd);
        return (1);
    }
    
    // Read and free each line
    printf("Reading from file.txt: ");
    result = get_next_line(fd);
    if (result)
    {
        printf("%s", result);
        free(result);
    }
    
    printf("Reading from test.txt: ");
    result = get_next_line(fdd);
    if (result)
    {
        printf("%s", result);
        free(result);
    }
    
    printf("Reading from file.txt again: ");
    result = get_next_line(fd);
    if (result)
    {
        printf("%s", result);
        free(result);
    }
    
    close(fd);
    close(fdd);
    return (0);
}*/
