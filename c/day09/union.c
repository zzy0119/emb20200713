#include <stdio.h>

// 共用体 联合体
union test_un{
	int a;
	char b;	
};

// 大端存储:低字节存高地址，高字节存低地址 小端存储:低字节存在低地址，高字节存高地址

int main(void)
{
	union test_un n;
	
	n.a = 0x12345678;
	if (n.b == 0x78) {
		printf("小端\n");
	} else if (n.b == 0x12) {
		printf("大端\n");
	}

	printf("%ld\n", sizeof(union test_un));

	return 0;
}

