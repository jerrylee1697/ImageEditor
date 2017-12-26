# Makefile: PhotoLab

#PhotoLab: FileIO.o DIPs.o Advanced.o PhotoLab.o
#	gcc -Wall -ansi -std=c99 FileIO.o DIPs.o Advanced.o PhotoLab.o -o PhotoLab

#FileIO.o: FileIO.c FileIO.h Constants.h
#	gcc -Wall -ansi -std=c99 -c FileIO.c -o FileIO.o

#DIPs.o: DIPs.c DIPs.h Constants.h
#	gcc -Wall -ansi -std=c99 -c DIPs.c -o DIPs.o

#Advanced.o: Advanced.c Advanced.h Constants.h
#	gcc -Wall -ansi -std=c99 -c Advanced.c -o Advanced.o

#PhotoLab.o: PhotoLab.c FileIO.h DIPs.h Advanced.h Constants.h
#	gcc -Wall -ansi -std=c99 -c PhotoLab.c -o PhotoLab.o

#Variable Defintions
CC 		= gcc
DEBUG 	= -g -DDEBUG
CFLAGS 	= -Wall -ansi -std=c99 -c 
LFLAGS 	= -Wall -ansi -std=c99
MAIN	= -DMAIN
#convenience targets
all: PhotoLab PhotoLabTest
	
clean:
		rm -f bw.ppm
		rm -f negative.ppm
		rm -f colorfilter.ppm
		rm -f edge.ppm
		rm -f shuffle.ppm
		rm -f vflip.ppm
		rm -f vmirror.ppm
		rm -f border.ppm
		rm -f noise.ppm
		rm -f sharpen.ppm
		rm -f posterize.ppm
		rm -f blur.ppm
		rm -f smallresize.ppm
		rm -f bigresize.ppm
		rm -f crop.ppm
		rm -f brightnessandcontrast.ppm
		rm -f watermark.ppm
		rm -f *.o
		rm -f PhotoLab
		rm -f PhotoLabTest
test: PhotoLab
		./PhotoLabTest
	
#compilation Rules
#User Interactive without DEBUG
#PhotoLab: FileIO.o DIPs.o Advanced.o PhotoLab.o
#	$(CC) $(LFLAGS) FileIO.o DIPs.o Advanced.o PhotoLab.o -o PhotoLab

PhotoLab: Test.o libfilter.a FileIO.o PhotoLab.o Image.o
	$(CC) $(LFLAGS) $(DEBUG)  Test.o FileIO.o PhotoLab.o Image.o -lfilter -L. -o PhotoLab

FileIO.o: FileIO.c FileIO.h Constants.h
	$(CC) $(CFLAGS)  $(DEBUG) FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h Constants.h
	$(CC) $(CFLAGS)  DIPs.c -o DIPs.o

Advanced.o: Advanced.c Advanced.h Constants.h
	$(CC) $(CFLAGS)  Advanced.c -o Advanced.o

PhotoLab.o: PhotoLab.c FileIO.h DIPs.h Advanced.h Constants.h Image.h Test.h 
	$(CC) $(CFLAGS)  PhotoLab.c -o PhotoLab.o

Image.o: Image.h Image.c Constants.h
	$(CC) $(CFLAGS)  Image.c -o Image.o

libfilter.a: DIPs.o Advanced.o
	ar rc libfilter.a DIPs.o Advanced.o
	ranlib libfilter.a

Test.o: Image.h DIPs.h FileIO.h Test.h Test.c
	$(CC) $(CFLAGS)  Test.c -o Test.o


#DEBUG Mode files
PhotoLabTest: TestAuto.o Image.o FileIO.o DIPs.o Advanced.o PhotoLabTest.o
	$(CC) $(LFLAGS) TestAuto.o FileIO.o DIPs.o Advanced.o PhotoLabTest.o Image.o -o PhotoLabTest

PhotoLabTest.o: PhotoLab.c FileIO.h DIPs.h Advanced.h Constants.h Image.h Test.h
	$(CC) $(CFLAGS) $(DEBUG) PhotoLab.c -o PhotoLabTest.o

TestAuto.o: Image.h DIPs.h FileIO.h Test.h Test.c
	$(CC) $(CFLAGS) $(DEBUG) Test.c -o TestAuto.o
