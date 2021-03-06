#CC=gcc
#CFLAGS+=-Wall -O0 -g -ggdb
#CFLAGS+=-Wall -O3 -ffast-math
#CFLAGS+=-Wall -O3 
#LDFLAGS+=-lm -lrt -lfftw

#profiling: -pg, run normally, use gprof later

#CC=icc
#CFLAGS+=-Wall -O3 -fast -opt-jump-tables=large
#LDFLAGS+=-lm -lrt -lfftw

CC=pgcc
#CFLAGS+=-Minform=warn -fastsse -Mipa=fast,inline -Msafeptr=all -O4 
CFLAGS+=-Minform=warn -fast -Msafeptr=all -O4 
LDFLAGS+=-lm -lrt -lfftw  

all: test_fft test_swifft
#wavelet

clean:
	rm -f *.o test_fft test_wavelets

test_fft: fft.o test_fft.o utils.o
	$(CC) $(CFLAGS) -o test_fft test_fft.o fft.o utils.o $(LDFLAGS)

test_fft.o: test_fft.c
	$(CC) $(CFLAGS) -c test_fft.c

fft.o: fft.c
	$(CC) $(CFLAGS) -c fft.c

utils.o: utils.c
	$(CC) $(CFLAGS) -c utils.c

test_swifft: test_swifft.o swifft.o utils.o fft.o
	$(CC) $(CFLAGS) -o test_swifft test_swifft.o swifft.o utils.o fft.o $(LDFLAGS)

test_swifft.o: test_swifft.c
	$(CC) $(CFLAGS) -c test_swifft.c 

swifft.o: swifft.c
	$(CC) $(CFLAGS) -c swifft.c

