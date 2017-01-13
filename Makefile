# my first Makefile

CC = gcc
#CC = arm-none-linux-gnueabi-gcc
CFLAGS = -Wall -g -std=gnu99 -DDEBUG -DMY_ALGO
STDLIBS= -lrt -lm 

all: audio_encoder.c
	rm -rf *.o 
	rm -rf ./audio_encoder
	clear
	$(CC) $(CFLAGS) audio_encoder.c $(STDLIBS)  -o audio_encoder
	
clean:
	rm -rf *.o 
	rm -rf ./audio_encoder

