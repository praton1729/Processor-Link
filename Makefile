OUTPUT = processor_link

INTERNAL = processor_link_internal

INTERNAL_DEPENDENCIES = $(INTERNAL).c $(INTERNAL).h

HARDWARE_DESCRIPTION = hardware_description

OUTPUT_DEPENDENCIES = $(OUTPUT).h $(HARDWARE_DESCRIPTION).h $(INTERNAL) 

default:all

all: Memory_test_app tags

$(INTERNAL):
	gcc -g -c -I ./include src/$@.c -o obj/$@.o

$(OUTPUT): $(INTERNAL)
	gcc -g -c -I ./include src/$@.c -o obj/$@.o

library:
	ar -rcs lib/libaxidriver.a obj/$(OUTPUT).o obj/$(INTERNAL).o

Memory_test_app: $(OUTPUT) library
	gcc -g -I ./include/ build/memory_test_application.c -o bin/memory_test_application -L ./lib/ -laxidriver

tags:
	ctags -R --extra=+f *

clean:
	rm -f logs/* obj/* bin/* lib/* 
