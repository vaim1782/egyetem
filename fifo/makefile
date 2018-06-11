
all:sz kl

sz: asd_sz.o
	gcc asd_sz.o -o sz

asd_sz.o: asd_sz.c asd.h
	gcc asd_sz.c -c

kl: asd_kl.o
	gcc asd_kl.o -o kl

asd_kl.o: asd_kl.c asd.h
	gcc asd_kl.c -c

.PHONY: clean
	
clean:
	rm -f ./kl asd_kl.o ./sz asd_sz.o 













