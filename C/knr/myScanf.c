/* Minimal Re-implementation of scanf */

#include <stdarg.h>
#include <stdio.h>

short unsigned myscanf(char *format, ...);

short unsigned
myscanf(char *format, ...)
{
	short unsigned n = 0;
	char *p;
	va_list ap;
	
	va_start(ap, format);
	
	for (p = format;*p != '\0';p++) {
		if (*p != '%')
			continue;
		
		switch (*++p) {
		case 'd':
		case 'i':
			n += scanf("%d", va_arg(ap, int *));
			break;
		case 'f':
			n += scanf("%f", va_arg(ap, float *));
			break;
		case 's':
			n += scanf("%s", va_arg(ap, char *));
			break;
		}	
	}

	va_end(ap);

	return n;
}

int
main()
{
	char str[10];
	float f;
	int d;
	
	myscanf("%d", &d);
	myscanf("%f", &f);
	myscanf("%s", str);
	
	printf("%d\n%f\n%s\n", d, f, str);
	
	return 0;
}
