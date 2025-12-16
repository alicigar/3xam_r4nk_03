#include <unistd.h> //añade todas las bibliotecas del .h
#include <stdlib.h>

#ifndef BUFFER_SIZE  //añade esto también
# define BUFFER_SIZE 10
#endif

char *ft_strchr(char *s, int c)
{
    int i = 0;
    while (s[i] && s[i] != c) //solo agregar s[i] &&
        i++;
    if (s[i] == c)
        return (s + i);
    else
    	return (NULL);
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i = 0; //agregamos esta variable y la inicializamos
    while (i < n) //el while cambia de (--n > 0) a (i < n)
    {
        ((char *)dest)[i] = ((char *)src)[i]; //sustituye las n por i, y quita los -1
        i++; //agrega esto
    }
    return (dest); //REMINDER: mejor poner todos los valores de return entre paréntesis
}

size_t ft_strlen(char *s)
{
    size_t res = 0;
    while (s && *s) //solo agrega s &&
    {
        s++;
        res++;
    }
    return (res);
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
    size_t size1 = ft_strlen(*s1);
    char *tmp = malloc(size2 + size1 + 1);
    if (!tmp)
        return (0);
    if (*s1) //agrega esta condición y mete la siguiente linea en ella
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
    size_t i; //añade esta nueva variable

    if (dest == src) //la segunda condición va primero
        return (dest);
    if (dest < src) // la primera condición va segunda, solo if, sin else if y la == es <
        return (ft_memcpy(dest, src, n)); //ft_memmove es ft_memcpy
    i = n; //elimina una linea para poner esta
    while (i > 0)
    {
        i--; //ahora el i-- va primero, pero todo sigue igual
        ((char *)dest)[i] = ((char *)src)[i];
    }
    return (dest);
}

char *get_next_line(int fd)
{
    static char b[BUFFER_SIZE + 1] = "";
    char *ret = NULL;
    char *tmp = ft_strchr(b, '\n');
    /*int read_ret;*/

    while (!tmp)
    {
        if (!str_append_str(&ret, b))
            return (NULL);
        int read_ret = read(fd, b, BUFFER_SIZE);
        if (read_ret == -1)
            return (NULL);
        b[read_ret] = '\0'; //en vez de 0, pon '\0'

        if (read_ret == 0) //agregas toda esta nueva condición
        {
            if (ret && *ret)
                return (ret);
            free(ret);
            return (NULL);
        }

        tmp = ft_strchr(b, '\n'); //hasta aquí, además es traerlo de arriba
    }
    if (!str_append_mem(&ret, b, tmp - b + 1))
    {
        free(ret);
        return (NULL);
    }
    ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1); //añade esta nueva linea
    return (ret);
}

#include <stdio.h>
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
}
