run1.algoritm:
	gcc -std=c17 -o build/1.algoritm 1.algoritm.c -lm && ./build/1.algoritm
# -lm : l - linker option, m - math.h
run2.address:
	gcc -std=c17 -o build/2.address 2.address.c && ./build/2.address
run2.maxElement:
	gcc -std=c17 -o build/2.maxElement 2.maxElement.c && ./build/2.maxElement
run2.massiveDu:
	gcc -std=c17 -o build/2.massiveDu 2.massiveDu.c && ./build/2.massiveDu
run2.maxElSer:
	gcc -std=c17 -o build/2.maxElSer 2.maxElSer.c && ./build/2.maxElSer
run3.struct:
	gcc -std=c17 -o build/3.struct 3.struct.c && ./build/3.struct
run3.pthread:
	gcc -std=c17 -o build/3.pthread 3.pthread.c -lpthread && ./build/3.pthread

run3.io-operations:
	gcc -std=c17 -o build/3.io-operations 3.io-operations.c && ./build/3.io-operations

run4.fileinput:
	gcc -std=c17 -o build/4.fileinput 4.fileinput.c && ./build/4.fileinput ./4.data.txt

run.bmstu0301.1:
	gcc -std=c17 ./b0301/1.jsontest.c -ljson-c -o build/1.jsontest  && ./build/1.jsontest 




run0.factorial:
	gcc -std=c17 ./0.std.c ./0.factorial.c -o build/0.factorial  && ./build/0.factorial 
# Промежуточная компиляция через объектные файлы
run0.factorial.one:
	gcc -std=c17 -c ./0.std.c -o ./build/0.std.o
run0.factorial.two:
	gcc -std=c17 -c ./0.factorial.c -o ./build/0.factorial.o
run0.factorial.three:
	gcc ./build/0.std.o ./build/0.factorial.o -o ./build/0.factor



run5.restrict:
	gcc -std=c17 ./5.restrict.c  -o build/5.restrict -g && ./build/5.restrict 
# -g подключаем gdb
# препроцессор
run5.restrict.one:
	gcc -E ./5.restrict.c -o ./build/5.restrictone.i
# компилятор - в ассемблер
run5.restrict.two:
	gcc -std=c17 -S ./build/5.restrictone.i -o ./build/5.restricttwo.s
# файл.с в объектный код
run5.restrict.three:
	gcc -c ./5.restrict.c -o ./build/5.restrictthree.o
# объектный код в исполняемый
run5.restrict.four:
	gcc ./build/5.restrictthree.o -o ./build/5.restrict


run5.restrict.six:
# verbose - расписывает этапы компиляции, + file no-pie executable file
	gcc -std=c17 ./5.restrict.c -no-pie -v -o ./build/5.restrict 

run5.restrict.seven:
# запуск
	./build/5.restrict 




run6.maxmin:
	gcc -std=c17 \
		./6.maxmin.c \
		-o build/6.maxmin \
		-g \
		&& ./build/6.maxmin 

run6.sort:
	gcc -std=c17 ./6.sort.c -o build/6.sort -g && ./build/6.sort 

run6.infincycle:
	gcc -std=c17 ./6.infincycle.c -o build/6.infincycle -g && ./build/6.infincycle 

run7.stack:
	gcc -std=c17 ./7.stack.c -o build/7.stack -g && ./build/7.stack 

run7.stackv2:
	gcc -std=c17 ./7.stackv2.c -o build/7.stackv2 -g && ./build/7.stackv2 


run8.callback:
	gcc -std=c17 ./8.callbackfunc.c -o build/8.callbackfunc -g && ./build/8.callbackfunc 

run9.wfile:
	gcc -std=c17 ./9.wfile.c -o build/9.wfile -g && ./build/9.wfile 

run10.generator:
	gcc -std=c17 ./10.generator.c -o build/10.generator -g && ./build/10.generator 

run11.getchar:
	gcc -std=c17 ./11.getchar.c -o build/11.getchar -g && ./build/11.getchar 

run12.enum:
	gcc -std=c17 ./12.enum.c -o build/12.enum -g && ./build/12.enum 

run13.wchar:
	gcc -std=c17 ./13.wchar.c -o build/13.wchar -g && ./build/13.wchar 

run13.uchar:
	gcc -std=c17 ./13.uchar.c -o build/13.uchar -g && ./build/13.uchar 

run14.serg:
	gcc -std=c17 ./14.serg-func.c -o build/14.serg-func -g && ./build/14.serg-func 