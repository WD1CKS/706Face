#include <sys/select.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#define BUFSZ 256

int descriptor = -1;
unsigned bufpos;
uint8_t buf[BUFSZ];

void
terminate(int code)
{
	if (descriptor != -1)
		close(descriptor);
	// TODO: Cook stdio
	exit(code);
}

void
usage(const char *cmd)
{
	printf("%s [serial_path]\n"
	    "\n"
	    "Does the reverse engineering stuff on [serial_path].\n", cmd);
	terminate(EXIT_FAILURE);
}

void comOpen(const char *path)
{
	struct termios t;

	descriptor = open(path, O_NONBLOCK|O_RDWR);
	if (descriptor == -1) {
		perror("Opening serial port");
		terminate(EXIT_FAILURE);
	}
	if (tcgetattr(descriptor, &t) == -1) {
		perror("Getting serial port attributes");
		close (descriptor);
		descriptor = -1;
		terminate(EXIT_FAILURE);
	}

	t.c_iflag = IGNBRK | IGNPAR;
	t.c_oflag = 0;
	t.c_cflag = CS8 | CREAD | HUPCL | CLOCAL;
	t.c_lflag = 0;
	cfsetispeed(&t, B19200);
	cfsetospeed(&t, B19200);
	if (tcsetattr(descriptor, TCSANOW, &t) == -1) {
		perror("Setting serial port attibutes");
		close(descriptor);
		descriptor = -1;
		terminate(EXIT_FAILURE);
	}
}

bool
calcRemain(struct timespec *now, struct timespec *last, struct timeval *tv)
{
	struct timespec diff;

	diff.tv_nsec = now->tv_nsec - last->tv_nsec;
	diff.tv_sec = now->tv_sec - last->tv_sec;
	last->tv_nsec = now->tv_nsec;
	last->tv_sec = now->tv_sec;

	if (diff.tv_nsec < 0) {
		diff.tv_sec -= 1;
		diff.tv_nsec += 1000000000L;
	}

	// Convert to ms
	tv->tv_sec = diff.tv_sec;
	tv->tv_usec = diff.tv_nsec / 1000L;

	if (tv->tv_sec > 0 || tv->tv_usec > 100000)
		return false;
	return true;
}

bool
waitForData(struct timespec *last)
{
	fd_set rfd;
	struct timespec now;
	struct timeval delay;

	FD_ZERO(&rfd);
	FD_SET(STDIN_FILENO, &rfd);
	FD_SET(descriptor, &rfd);

	clock_gettime(CLOCK_MONOTONIC, &now);
	if (!calcRemain(&now, last, &delay))
		return false;

	switch (select(descriptor + 1, &rfd, NULL, NULL, &delay)) {
		case -1:
			perror("Selecting stdin and serial port");
			terminate(EXIT_FAILURE);
		case 0:
			return false;
	}
	return true;
}

bool
byteAvailable(int h)
{
	struct timeval tv = {0};
	fd_set rfd;

	FD_ZERO(&rfd);
	FD_SET(h, &rfd);
	switch (select(h + 1, &rfd, NULL, NULL, &tv)) {
		case -1:
		case 0:
			return false;
	}
	return true;
}

void
handleCommand(void)
{
	int i;

	if (buf[0] != 0xFE || buf[bufpos] != 0xFD) {
		fputs("Invalid command\n", stderr);
		// TODO: Log bytes and stuff.
		return;
	}

	switch (buf[1]) {
		case 0x60:
			for (i = 1; i < bufpos; i++) {
				if ((i % 16) == 1)
					fprintf(stderr, "%04x: ", i - 1);
				else if ((i % 8) == 1)
					fputs(" ", stderr);
				fprintf(stderr, "%02X ", buf[i]);
				if ((i % 16) == 0)
					fputs("\n", stderr);
			}
			if (i % 16)
				fputs("\n", stderr);
			break;
		case 0xF0:
		case 0xF1:
			write(descriptor, buf, bufpos + 1);
			break;
		default:
			fprintf(stderr, "Unhandled command: 0x%02X\n", buf[1]);
			break;
	}
	bufpos = 0;
}

void
readFromRadio(void)
{
	while (byteAvailable(descriptor)) {
		if (bufpos == BUFSZ) {
			fputs("Buffer overflow from radio\n", stderr);
		}
		else {
			switch (read(descriptor, &buf[bufpos], 1)) {
				case 1:
					if (buf[bufpos] == 0xFD) {
						handleCommand();
					}
					else {
						bufpos++;
					}
					break;
				case 0:
					fputs("Unable to read byte after select() said it was there.\n", stderr);
					terminate(EXIT_FAILURE);
				case -1:
					perror("Reading byte from serial port");
					terminate(EXIT_FAILURE);
			}
		}
	}
}

void
sendKeepAlive(void)
{
	write(descriptor, "\xFE\x0B\x00\xFD", 4);
}

int
main(int argc, char **argv)
{
	struct timespec last = {0};

	fputs("IC-706 Reverse engineering utility\n\n", stderr);

	if (argc != 2)
		usage(argv[0]);

	// TODO: Raw keyboard...
	comOpen(argv[1]);

	/*
	 * Power on needs to be via some other mechanism
	 */
	for (;;) {
		if (!waitForData(&last)) {
			sendKeepAlive();
		}
		else {
			// First, read all data from remote into buffer...
			readFromRadio();
		}
	}

	terminate(EXIT_SUCCESS);
}
