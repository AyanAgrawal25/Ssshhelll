CFLAGS = -g -Wall

ashell:main.o utils.o prompt.o tokenize.o echo.o cd.o ls.o pwd.o pinfo.o repeat.o history.o redirection.o jobs.o fg.o bg.o sig.o replay.o pipe.o
	gcc $(CFLAGS) -o ashell main.o utils.o prompt.o tokenize.o echo.o cd.o ls.o pwd.o pinfo.o repeat.o history.o redirection.o jobs.o fg.o bg.o sig.o replay.o pipe.o

clean:
	rm -f *.o ashell

main.o:main.c header.h
	gcc $(CFLAGS) -c main.c 
utils.o:utils.c utils.h
	gcc $(CFLAGS) -c utils.c
prompt.o:prompt.c prompt.h
	gcc $(CFLAGS) -c prompt.c
tokenize.o:tokenize.c tokenize.h
	gcc $(CFLAGS) -c tokenize.c
echo.o:echo.c echo.h
	gcc $(CFLAGS) -c echo.c
cd.o:cd.c cd.h
	gcc $(CFLAGS) -c cd.c
ls.o:ls.c ls.h
	gcc $(CFLAGS) -c ls.c
pwd.o:pwd.c pwd.h
	gcc $(CFLAGS) -c pwd.c
pinfo.o:pinfo.c pinfo.h
	gcc $(CFLAGS) -c pinfo.c
repeat.o:repeat.c repeat.h
	gcc $(CFLAGS) -c repeat.c
history.o:history.c history.h
	gcc $(CFLAGS) -c history.c
redirection.o:redirection.c redirection.h
	gcc $(CFLAGS) -c redirection.c
jobs.o:jobs.c jobs.h
	gcc $(CFLAGS) -c jobs.c
fg.o:fg.c fg.h
	gcc $(CFLAGS) -c fg.c
bg.o:bg.c bg.h
	gcc $(CFLAGS) -c bg.c
sig.o:sig.c sig.h
	gcc $(CFLAGS) -c sig.c
replay.o:replay.c replay.h
	gcc $(CFLAGS) -c replay.c
pipe.o:pipe.c pipe.h
	gcc $(CFLAGS) -c pipe.c