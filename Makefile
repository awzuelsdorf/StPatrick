CC = g++
EXE = irish
CFLAGS = -lX11 -L/usr/X11/lib -pthread -Wfatal-errors
RM = /bin/rm -f

compile:
	$(CC) $(EXE).cc $(CFLAGS) -o $(EXE)

clean:
	$(RM) $(EXE)
