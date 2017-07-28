# PDS-Project
Personal Data Store Project - Contact Management System ( Using file I/O operations )

## Header files :
1. pds.h - definition of PDS and Index structure, prototypes of functions, error and status codes
2. contact.h - definition of ContactInfo structure

**NOTE: pds.mk is the makefile created to take care of compiling and simulate a build process**

## VERSIONS:
### Version 1 :
1. *create()* - to create .dat file
2. *open()* - open file
3. *store()* - to store contacts into the file
4. *search_by_key()* - search for record by using contact_id as key value
5. *close()* - close file

### Version 2A :
Extending V1 by adding indexing to make search_by_key() more efficient

### Version 2B
Implementing built-in *qsort()* method to sort the keys in the index file

### Version 3 :
Adding 
1. *delete_by_key()* method which perform soft delete
2. *get_num_recs()* method which returns number of valid records in the data file
