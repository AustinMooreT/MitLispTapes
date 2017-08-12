/*
 * convert from tpc "ascii" header format to simh format
 */

#include <stdio.h>
#include <fcntl.h>

unsigned char buf[64*1024];

//#define FIX_TAPE2
#ifdef FIX_TAPE2
unsigned char b2[] = {
	0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x04, 0x61, 0x45, 0x50, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00
};
#endif

main(int argc, char *argv[])
{
	int ret, fd, fdout, n;
	char b[13];
	unsigned long l;
	int eof;
	int block;

	fd = open(argv[1], O_RDONLY);
	fdout = open(argv[2], O_RDWR);
	eof = 0;
	block = 0;
	while (1) {
		memset(b, 0, 12);
		ret = read(fd, b, 12);
		if (ret != 12)
			break;
		b[12] = 0;
		printf("%s\n", b);
		n = atoi(b);

		if (n == 0) {
			eof++;
			if (eof == 2)
				break;
			l = 0;
			write(fdout, &l, 4);
			continue;
		}

		eof = 0;
		ret = read(fd, buf, n);
		printf("ret %d\n", ret);
		if (ret != n) {
			printf("short read\n");
			exit(1);
		}

#if FIX_TAPE2
		if (block == 0) {

			l = n + 20;
			write(fdout, &l, 4);
			if (n & 1) n++;
			write(fdout, b2, 20);
			write(fdout, buf, n);
			write(fdout, &l, 4);
			block++;
			continue;
		}
#endif

		l = n;
		write(fdout, &l, 4);
//		if (n & 1) n++;
		write(fdout, buf, n);
		write(fdout, &l, 4);
		block++;
	}

	l = 0xffffffff;
	l = 0;
	write(fdout, &l, 4);

	exit(0);
}
