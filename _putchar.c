#include <unistd.h>

/**
 * _putchar - write character c to the stdout
 * @c: the character
 * Return: 1 on success and -1 otherwise
 */

int _putchar(char character)
{
	return (write(1, &character, 1));
}
