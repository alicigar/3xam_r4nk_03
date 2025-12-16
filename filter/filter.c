#include <unistd.h> //read
#include <string.h> //strlen
#include <stdio.h> //perror
#include <stdlib.h> //malloc

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i = 0;

	while (i < n)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1); //devuelve 1 si hay coincidencias, si no 0
}

int	main(int argc, char **argv)
{
	char	*buffer; //contenedor grande que almacena todo lo leído
	char	c; // variable temporal que almacena el carácter leído por read
	char	r; // resultado de read: 1(ok), 0(EOF), -1(ERROR)
	int		i; // variable para leer y luego para escribir
	int		len; // longitud del argumento (patrón a buscar)

	if (argc != 2 || argv[1][0] == '\0')
		return (1);
	len = strlen(argv[1]);
	buffer = malloc(1000000);
	if (!buffer)
	{
		perror("Error");
		return (1);
	}
	i = 0;
	while (1)
	{
		r = read(0, &c, 1);
		if (r == -1) //si falla
		{
			perror("Error");
			free(buffer);
			return (1);
		}
		if (r == 0) //si llega al EOF
			break ;
		buffer[i++] = c;
	}
	buffer[i] = '\0';
	i = 0;
	while (buffer[i])
	{
		if (ft_strncmp(&buffer[i], argv[1], len))
		{
			while (y < len)
			{
				write(1, "*", 1);
				y++;
			}
			i = i + len;
		}
		else
			write(1, &buffer[i++], 1);
	}
	free(buffer);
	return (0);
}

// steps:
// hay 5 variables (buffer, c, r, i, len) + 1 variable (y)
// 1)if (argumentos inválidos)
// asignaciones de len y de buffer
// 2)if (si falla buffer)
// inicialización de i
// 1)while (1): LECTURA
// asignación de r
// primer if: si falla r (IMPORTANTE: free(buffer);
// segundo if: si llega al EOF
// si no es nada de eso, buffer[i++] = c
// antes del segundo bucle: asegurar que el buffer llega al nulo y reinicializar i 
// 2)while (buffer[i]) ESCRITURA
// if ft_strncmp de buffer[i], argv[1] y len: para ver que coincide el argumento con el string
// si coincide, escribe len veces el * y salta len posiciones, 
// si no coincide, escribe buffer[i] y avanza 1
// liberamos el buffer
