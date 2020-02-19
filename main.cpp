#include <cstdio>

unsigned char blob1[(1 << 10)*4];
unsigned char blob0[(1 << 10)*4] = {};
FILE* f;
long long unsigned int size;
int left;

void initBlob() {
	int i = sizeof(blob1);
	while (i) blob1[--i] = 255;
}

void burn0() {
	fseek(f, 0, SEEK_SET);
	left = size;
	for (;;) {
		if (left > sizeof(blob0)) {
			fwrite(blob0, sizeof(blob0), 1, f);
			left -= sizeof(blob0);
		} else {
			fwrite(blob0, left, 1, f);
			break;
		}
	}
}

void burn1() {
	fseek(f, 0, SEEK_SET);
	left = size;
	for (;;) {
		if (left > sizeof(blob1)) {
			fwrite(blob1, sizeof(blob1), 1, f);
			left -= sizeof(blob1);
		} else {
			fwrite(blob1, left, 1, f);
			break;
		}
	}
}

int main(int argc, char const *argv[]) {
	initBlob();
	for (int i=1; i<argc; ++i) {
		printf("%s: ", argv[i]);
		f = fopen(argv[i], "r+b");
		if (!f) puts("failed!");
		fseek(f, 0, SEEK_END);
		size = ftell(f);
		burn0();
		fflush(f);
		burn1();
		fclose(f);
		puts("Ok");
	}
	puts("Press enter to exit");
	getchar();
	return 0;
}