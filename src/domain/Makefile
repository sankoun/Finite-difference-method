all: rm_mesh_1D.o rm_domain_1D.o moov

rm_mesh_1D.o : rm_mesh_1D.c
	gcc -Wall -o rm_mesh_1D.o -c rm_mesh_1D.c

rm_domain_1D.o : rm_domain_1D.c
	gcc -Wall -o rm_domain_1D.o -c rm_domain_1D.c

moov:
	mv *.o ../../obj/
