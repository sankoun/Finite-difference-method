all : rm_matrix_1D.o rm_operation.o rm_gradient.o moov

rm_matrix_1D.o : rm_matrix_1D.c
	gcc -Wall -o rm_matrix_1D.o -c rm_matrix_1D.c

rm_operation.o : rm_operation.c
	gcc -Wall  -o rm_operation.o -c rm_operation.c -lm

rm_gradient.o : rm_gradient.c
	gcc -Wall  -o rm_gradient.o -c rm_gradient.c
moov :
	mv *.o ../../obj
