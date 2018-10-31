OUTPUT = processor_link

INTERNAL = processor_link_internal

INTERNAL_DEPENDENCIES = $(INTERNAL).c $(INTERNAL).h

HARDWARE_DESCRIPTION = hardware_description

OUTPUT_DEPENDENCIES = $(OUTPUT).h $(HARDWARE_DESCRIPTION).h $(INTERNAL) 

default:$(OUTPUT)

$(INTERNAL):
	
	gcc -c -I ./include src/$@.c -o obj/$@.o

$(OUTPUT): $(INTERNAL)
	gcc -c -I ./include src/$@.c -o obj/$@.o

library:
	ar -cvq lib/libaxidriver.a obj/$(OUTPUT).o obj/$(INTERNAL).o

clean:
	rm -f obj/*	bin/* lib/*
