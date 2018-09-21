FILENAME = proc_link
HEADER = $(FILENAME).h

default:$(FILENAME)

$(FILENAME): $(FILENAME).c
	
	gcc -g $(FILENAME).c -o $(FILENAME)

clean:

	rm -f $(FILENAME)  	
