all : domesh_1D.o time.o rm_math.o rm_model.o rm_alger.o main.o main moov  

# appliquer les Makefiles d'autres répertoires
domesh_1D.o :
	make -C src/domain/
time.o :
	make -C src/time/
rm_math.o :
	make -C src/base/
rm_model.o :
	make -C src/model/
rm_alger.o :
	make -C src/alger

# déclarations de variable

TIME.O=obj/rm_time.o
MESH.O=obj/rm_mesh_1D.o
DOMAIN.O=obj/rm_domain_1D.o
MATH.O=obj/rm_math.o
BC.O=obj/rm_boundary_conditions.o
MODEL.O=obj/rm_model.o
STM.O=obj/rm_source_terms.o
BORD.O=obj/rm_boundary_conditions.o
ALG.O=obj/rm_matrix_1D.o
OPER.O=obj/rm_operation.o
GRAD.O=obj/rm_gradient.o
main.o : main.c
	gcc -Wall -o main.o -c main.c 

main :
	gcc -o  main -lm $(TIME.O) $(MESH.O) $(DOMAIN.O) $(MATH.O) $(BC.O) $(MODEL.O) $(STM.O) $(ALG.O) $(OPER.O) $(GRAD.O) main.o     

moov :
	mv main.o obj/ && mv main bin/
