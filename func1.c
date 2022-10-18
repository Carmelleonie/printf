#include "main.h"

/** PRINT CHAR **/

/**
*print_char - Prints a char
*@types: list of arguments
*@buffer: Buffer array to handle print
*@flags: calculates active flags
*@width: width
*@precision: precision on specifier
*@size: size specifier
*Return: number of characters printed
*/

int print_char(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision,size));
}

/*********************** PRINT A STRING *************************/
/**
*print_string - Prints a string
*@types: list of arguments
*@buffer: Buffer array to handle print
*@flags: calculates active flags
*@width: width
*@precision: precision on specifier
*@size: size specifier
*Return: number of characters printed
*/

int print_string(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	int lenght = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
		{
			str = "     ";
		}
	}
	while (str[lenght] != '\0')
	{
		lenght++;
	}
	if (precision >= 0 && precision < lenght)
	{
		lenght = precision;
	}
	if (width > lenght)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], lenght);
			for(i = width - lenght; i > 0; i--)
			{
				write(1, " ", 1);
			}
			return (width);
		}
		else
		{
			for (i = width - lenght; i > 0; i--)
			{
				write(1, &str[0], lenght);
			}
			write(1, &str[0], lenght);
			return (width);
		}
	}
	return (write(1, str, lenght));
}

/************** PRINT PERCENT SIGN ******************/
/**
*print_percent - Prints percent sign
*@types: list of arguments
*@buffer: Buffer array to handle print
*@flags: calculates active flags
*@width: width
*@precision: precision on specifier
*@size: size specifier
*Return: number of characters printed
*/
int print_percent(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**************** PRINT INT ******************************/
/**
print_int - print an integer
*@types: list of arguments
*@buffer: Buffer array to handle print
*@flags: calculates active flags
*@width: width
*@precision: precision on specifier
*@size: size specifier
*Return: number of characters printed
*/
int print_int(va_list types, char buffer[], int flags, int width, int precision, int size)
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int k;

	n = convert_size_number(n, size);

	if (n == 0)
	{
		buffer[i--] = '0';
	}
	buffer[BUFF_SIZE - 1] = '\0';
	k = (unsigned long int)n;

	if (n < 0)
	{
		k = (unsigned long int)((-1) * n);
		is_negative = 1;
	}
	while (k > 0)
	{
		buffer[i--] = (k % 10) + '0';
		k /= 10;
	}
	i++;
	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/*************** PRINT BINARY ****************/
/**
*print_binary - prints an unsigned number
*@types: list of arguments
*@buffer: Buffer array to handle print
*@flags: calculates active flags
*@width: width
*@precision: precision on specifier
*@size: size specifier
*Return: number of characters printed
*/
int print_binary(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	unsigned int i, j, k, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	i = va_arg(types, unsigned int);
	j = 2147483648; /* (2 ^ 31) */
	a[0] = i / j;
	for (k = 1; k < 32; k++)
	{
		j /= 2;
		a[k] = (i / j) % 2;
	}
	for (k = 0; sum = 0, count = 0; k < 32; k++)
	{
		sum += a[k];
		if (sum || k == 31)
		{
			char z = '0' + a[k];

			write(1, &z, 1);
		}
	}
	return (count);
}
