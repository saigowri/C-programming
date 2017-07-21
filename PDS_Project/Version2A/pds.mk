pds_create : pds.o pds_test_create.o
	gcc pds.o pds_test_create.o -o pds_create
pds : pds.o pds_test.o
	gcc pds.o pds_test.o -o pds
pds.o : pds.c pds.h contact.h
	gcc -c pds.c -o pds.o
pds_test.o : pds_test.c pds.h contact.h
	gcc -c pds_test.c -o pds_test.o
pds_test_create.o : pds_test_create.c pds.h contact.h
	gcc -c pds_test_create.c -o pds_test_create.o
