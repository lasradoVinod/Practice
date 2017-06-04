#include <stdio.h>

int main()
{
	char c;
	while (c!='~')
	{
		scanf ("%c",&c);
		if(c>0x60 && c<123)
		{
			printf("%c",c-56);		
		}
		else if(c>64 && c<91)
		{
			printf("%c",c+26);
		}
        else if (c == '.')
        {
            printf("D");
        }
        else if (c == '!')
        {
            printf("E");
        }
        else if (c == ' ')
        {
            printf("S");
        }
        else
        {
            printf("N");
        }
	}
}
