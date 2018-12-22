#include "util.h"

//==================================================================================
//				GESTION CHAINES DE CARACTERES
//==================================================================================

//------------------------------------------------------
// CONVERSION ENTIER --> CHAINE DE CARACTERES
//------------------------------------------------------
int int_to_str(int value, char *buf, unsigned int len)
{
	unsigned result = 0;

	if (!buf)
		return -1;


#define ADDCHAR(chr) \
	if (result < len - 1) \
	{ \
		*buf++ = (chr); \
		result++; \
	}

	int j = 0;
	char int_to_str[16];

	if (value < 0)
		ADDCHAR('-');

	char *ptr = int_to_str + sizeof(int_to_str) - 1;
	do
	{
		int modulo = value % 10;
		modulo = (modulo<0)?-modulo:modulo;
		*ptr-- =  modulo + '0';
		value /= 10;
		j++;
	} while (value);

	for (; j > 0; j--)
		ADDCHAR(int_to_str[sizeof(int_to_str) - j]);

	//*buf++ = '\n';//'\0';
	//*buf++ = '\r';//'\0';
	*buf++ = 0;//'\0';
	return 0;
}

//------------------------------------------------------
// EFFACEMENT CHAINE DE CARACTERES
//------------------------------------------------------

void flush_ch(char* ch, int ch_size)
{
	int i=0;
	for (i=0 ; i<ch_size ; i++)
	{
		ch[i]=0;

	}
}

//------------------------------------------------------
// TAILLE CHAINE DE CARACTERES
//------------------------------------------------------

int size_ch(char* ch, int ch_size_max)
{

	int i=0;
	for (i=0 ; i<ch_size_max ; i++)
	{
		if (ch[i]==0)
			break;
	}

	return i;
}
