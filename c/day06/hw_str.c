#include <stdio.h>

char *mystrcpy(char *dest, const char *src);
char *mystrcat(char *dest, const char *src);
int mystrcmp(const char *s1, const char *s2);
char *mystrchr(const char *s, char ch);
char *mystrstr(const char *s1, const char *s2);
int main(void)
{
	char d[100] = "good";
	char *s = "good";
	char *r;
	int n;

#ifdef COPY
	r = mystrcpy(d, s);
	puts(r);
#endif
	puts(mystrcat(d, s));

	n = mystrcmp(s, d);
	if (n == 0) {
		printf("相等\n");
	} else if (n > 0) {
		printf("%s大于%s\n", s, d);
	} else {
		printf("%s小于%s\n", s, d);
	}

	r = mystrchr(s, 'm');
	if (r == NULL) {
		printf("没有找到相应的字符\n");
	} else {
		printf("%s\n", r);
	}

	// d-->"goodgood"
	r = mystrstr(d, "good");
	if (r == NULL) {
		printf("没找到子串\n");
	} else {
		printf("%s\n", r);
	}

	return 0;
}

/*
 字符串复制
 */
char *mystrcpy(char *dest, const char *src)
{
#if 0
	char *ret = dest;

	while (*src) {
		*dest++ = *src++;
	}
	*dest = '\0';

	return ret;
#endif
	int i;

	for (i = 0; src[i]; i++) {
		dest[i] = src[i];	
	}
	dest[i] = '\0';

	return dest;
}

/*
 字符串拼接
 */
char *mystrcat(char *dest, const char *src)
{
	int i;	

	for (i = 0; dest[i]; i++)
		;
	mystrcpy(dest+i, src);
	return dest;
}

/*
 字符串比较
 */
int mystrcmp(const char *s1, const char *s2)
{
#if 0
	int i = 0;

	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	if (s1[i] != s2[i])
		return s1[i] - s2[i];
	return 0;
#endif
	while (*s1 == *s2 && *s1 != '\0') {
		s1++;
		s2++;
	}
	if (*s1 == '\0')
		return 0;
	return *s1 - *s2;
}

/*
 字符串中找字符
 */
char *mystrchr(const char *s, char ch)
{
	while (*s) {
		if (*s == ch)
			return (char *)s;
		s++;
	}
	return NULL;
}

/*
 字符串中找子串
 */
char *mystrstr(const char *s1, const char *s2)
{
	int i;		
	const char *s1_next;
	const char *s2_next;

	i = 0;
	while (s1[i]) {
		if (s1[i] == s2[0]) {
			s1_next = s1+i+1;	
			s2_next = s2+1;
			while (*s2_next) {
				if (*s2_next == *s1_next) {
					s1_next ++;
					s2_next ++;
				} else {
					break;
				}
			}
			if (*s2_next == '\0') {
				// 是子串
				return (char *)s1+i;
			}
		}
		i ++;
	}
	return NULL;
}









