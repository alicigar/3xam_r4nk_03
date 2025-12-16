#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

char *ft_strchr(char *s, int c)
{
    int i = 0;
    while (s[i] && s[i] != c)
        i++;
    if (s[i] == c)
        return (s + i);
    return (NULL);
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i = 0;
    while (i < n)
    {
        ((char *)dest)[i] = ((char *)src)[i];
        i++;
    }
    return (dest);
}

size_t ft_strlen(char *s)
{
    size_t res = 0;
    while (s && *s)
    {
        s++;
        res++;
    }
    return (res);
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
    size_t size1 = ft_strlen(*s1);
    char *tmp = malloc(size1 + size2 + 1);
    if (!tmp)
        return (0);

    if (*s1)
        ft_memcpy(tmp, *s1, size1);

    ft_memcpy(tmp + size1, s2, size2);
    tmp[size1 + size2] = '\0';

    free(*s1);
    *s1 = tmp;
    return (1);
}

int str_append_str(char **s1, char *s2)
{
    return (str_append_mem(s1, s2, ft_strlen(s2)));
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
    size_t i;

    if (dest == src)
        return (dest);

    if (dest < src)
        return (ft_memcpy(dest, src, n));

    i = n;
    while (i > 0)
    {
        i--;
        ((char *)dest)[i] = ((char *)src)[i];
    }
    return (dest);
}

char *get_next_line(int fd)
{
    static char b[BUFFER_SIZE + 1] = "";
    char *ret = NULL;
    char *tmp = ft_strchr(b, '\n');
    int read_ret;

    while (!tmp)
    {
        if (!str_append_str(&ret, b))
            return (NULL);

        read_ret = read(fd, b, BUFFER_SIZE);
        if (read_ret == -1)
            return (NULL);

        b[read_ret] = '\0';

        if (read_ret == 0)
        {
            if (ret && *ret)
                return (ret);
            free(ret);
            return (NULL);
        }

        tmp = ft_strchr(b, '\n');
    }

    if (!str_append_mem(&ret, b, tmp - b + 1))
    {
        free(ret);
        return (NULL);
    }

    ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);

    return (ret);
}

/*#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

char *get_next_line(int fd);

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    if (fd < 0)
        return 1;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
}*/
