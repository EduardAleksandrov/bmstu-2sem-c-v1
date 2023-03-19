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