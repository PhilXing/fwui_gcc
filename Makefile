LIBS= -L/usr/lib/x86_64-linux-gnu -lefivar -I/usr/include/efivar

all : fwui

install :

clean :
	@rm -rfv fwui *.o *.E *.S

test : fwui
	./fwui

fwui :: fwui.o
	cc -o $@ $^ $(LIBS) -ldl

.PHONY: all clean install test
