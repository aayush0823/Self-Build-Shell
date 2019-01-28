shell: overkill.o fg.o bg.o kjob.o pipe.o redirect.o shell.o ls.o echo.o cd.o prompt.o pinfo.o remind.o pwd.o bgreturn.o unsetenv.o setenv.o job.o
	gcc  overkill.o fg.o bg.o kjob.o pipe.o redirect.o shell.o ls.o echo.o cd.o prompt.o pinfo.o remind.o pwd.o bgreturn.o unsetenv.o setenv.o job.o

overkill.o: overkill.c
	gcc -c overkill.c

bg.o: bg.c
	gcc -c bg.c

fg.o: fg.c
	gcc -c fg.c

kjob.o: kjob.c
	gcc -c kjob.c

job.o: job.c
	gcc -c job.c

bgreturn.o: bgreturn.c
	gcc -c bgreturn.c

shell.o: shell.c
	gcc -c shell.c

pwd.o: pwd.c
	gcc -c pwd.c

remind.o: remind.c
	gcc -c remind.c

redirect.o: redirect.c
	gcc -c redirect.c

ls.o:ls.c
	gcc -c ls.c

echo.o:echo.c
	gcc -c echo.c

cd.o:cd.c
	gcc -c cd.c

prompt.o:prompt.c
	gcc -c prompt.c

pinfo.o:pinfo.c
	gcc -c pinfo.c

pipe.o:pipe.c
	gcc -c pipe.c

setenv.o:setenv.c
	gcc -c setenv.c

unsetenv.o:unsetenv.c
	gcc -c unsetenv.c

clean: overkill.o fg.o bg.o kjob.o job.o pipe.o redirect.o pinfo.o ls.o echo.o echo.o prompt.o remind.o pwd.o bgreturn.o setenv.o unsetenv.o
	rm *.o