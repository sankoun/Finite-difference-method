all : rm_boundary_conditions.o rm_model.o rm_source_terms.o moov

rm_boundary_conditions.o : rm_boundary_conditions.c
	gcc -Wall -o rm_boundary_conditions.o -c rm_boundary_conditions.c

rm_model.o : rm_model.c
	gcc -Wall -o rm_model.o -c rm_model.c

rm_source_terms.o : rm_source_terms.c
	gcc -Wall -o rm_source_terms.o -c  rm_source_terms.c

moov :
	mv *.o ../../obj
