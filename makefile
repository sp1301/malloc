all: libsl.a mymalloc.o test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12 test13 test14 test15 test16 test17 test18 test1.o test2.o test3.o test4.o test5.o test6.o test7.o test8.o test9.o test10.o test11.o test12.o test13.o test14.o test15.o test16.o test17.o test18.o

mymalloc.o: mymalloc.c mymalloc.h
	gcc -Wall -Werror -g -c mymalloc.c
test1.o: test1.c
	gcc -Wall -Werror -g -c test1.c
test2.o: test2.c
	gcc -Wall -Werror -g -c test2.c
test3.o: test3.c
	gcc -Wall -Werror -g -c test3.c
test4.o: test4.c	
	gcc -Wall -Werror -g -c test4.c
test5.o: test5.c
	gcc -Wall -Werror -g -c test5.c
test6.o: test6.c
	gcc -Wall -Werror -g -c test6.c
test7.o: test7.c
	gcc -Wall -Werror -g -c test7.c
test8.o: test8.c	
	gcc -Wall -Werror -g -c test8.c
test9.o: test9.c
	gcc -Wall -Werror -g -c test9.c
test10.o: test10.c
	gcc -Wall -Werror -g -c test10.c
test11.o: test11.c
	gcc -Wall -Werror -g -c test11.c
test12.o: test12.c
	gcc -Wall -Werror -g -c test12.c
test13.o: test13.c
	gcc -Wall -Werror -g -c test13.c
test14.o: test14.c
	gcc -Wall -Werror -g -c test14.c
test15.o: test15.c
	gcc -Wall -Werror -g -c test15.c
test16.o: test16.c
	gcc -Wall -Werror -g -c test16.c
test17.o: test17.c
	gcc -Wall -Werror -g -c test17.c
test18.o: test18.c
	gcc -Wall -Werror -g -c test18.c
test1:
	gcc -Wall -Werror -g -o test1 mymalloc.c test1.c
test2:
	gcc -Wall -Werror -g -o test2 mymalloc.c test2.c
test3:
	gcc -Wall -Werror -g -o test3 mymalloc.c test3.c
test4:
	gcc -Wall -Werror -g -o test4 mymalloc.c test4.c	
test5:
	gcc -Wall -Werror -g -o test5 mymalloc.c test5.c
test6:
	gcc -Wall -Werror -g -o test6 mymalloc.c test6.c	
test7:
	gcc -Wall -Werror -g -o test7 mymalloc.c test7.c
test8:
	gcc -Wall -Werror -g -o test8 mymalloc.c test8.c
test9:
	gcc -Wall -Werror -g -o test9 mymalloc.c test9.c
test10:
	gcc -Wall -Werror -g -o test10 mymalloc.c test10.c
test11:
	gcc -Wall -Werror -g -o test11 mymalloc.c test11.c
test12:
	gcc -Wall -Werror -g -o test12 mymalloc.c test12.c
test13:
	gcc -Wall -Werror -g -o test13 mymalloc.c test13.c
test14:
	gcc -Wall -Werror -g -o test14 mymalloc.c test14.c
test15:
	gcc -Wall -Werror -g -o test15 mymalloc.c test15.c
test16:
	gcc -Wall -Werror -g -o test16 mymalloc.c test16.c
test17:
	gcc -Wall -Werror -g -o test17 mymalloc.c test17.c
test18:
	gcc -Wall -Werror -g -o test18 mymalloc.c test18.c

libsl.a:
	ar r libsl.a mymalloc.o test1.o
	ar r libsl.a mymalloc.o test2.o
	ar r libsl.a mymalloc.o test3.o
	ar r libsl.a mymalloc.o test4.o
	ar r libsl.a mymalloc.o test5.o
	ar r libsl.a mymalloc.o test6.o
	ar r libsl.a mymalloc.o test7.o
	ar r libsl.a mymalloc.o test8.o
	ar r libsl.a mymalloc.o test9.o
	ar r libsl.a mymalloc.o test10.o
	ar r libsl.a mymalloc.o test11.o
	ar r libsl.a mymalloc.o test12.o
	ar r libsl.a mymalloc.o test13.o
	ar r libsl.a mymalloc.o test14.o
	ar r libsl.a mymalloc.o test15.o
	ar r libsl.a mymalloc.o test16.o
	ar r libsl.a mymalloc.o test17.o
	ar r libsl.a mymalloc.o test18.o
clean:
	rm *.o test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12 test13 test14 test15 test16 test17 test18
