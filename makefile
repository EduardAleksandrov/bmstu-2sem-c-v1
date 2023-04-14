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

run5.restrict:
	gcc -std=c17 ./5.restrict.c  -o build/5.restrict -g && ./build/5.restrict 

run6.maxmin:
	gcc -std=c17 ./6.maxmin.c  -o build/6.maxmin -g && ./build/6.maxmin 
