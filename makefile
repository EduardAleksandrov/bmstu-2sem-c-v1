run1.algoritm:
	gcc -std=c17 -o build/1.algoritm 1.algoritm.c -lm && ./build/1.algoritm
# -lm : l - linker option, m - math.h
run2.address:
	gcc -std=c17 -o build/2.address 2.address.c && ./build/2.address
run2.maxElement:
	gcc -std=c17 -o build/2.maxElement 2.maxElement.c && ./build/2.maxElement
run2.massiveDu:
	gcc -std=c17 -o build/2.massiveDu 2.massiveDu.c && ./build/2.massiveDu	