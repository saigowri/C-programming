#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "pds.h"
#include "contact.h"
struct PdsInfo pdsInfo;

int pds_create( char *repo_name ) {
	if(pdsInfo.repo_status == PDS_OPEN) { //if another file open
		return PDS_REPO_ALREADYOPEN;
	}
	pdsInfo.repo_fptr = fopen(repo_name,"r"); //file trying to be created already exists
	if(pdsInfo.repo_fptr != NULL){
		fclose(pdsInfo.repo_fptr);
		return PDS_CREATE_ERROR;
	}
	pdsInfo.repo_fptr = fopen(repo_name,"a+"); //creation of file
	if(pdsInfo.repo_fptr == NULL){
		return PDS_CREATE_ERROR;
	}
	strcpy(pdsInfo.repo_name,repo_name);
	fclose(pdsInfo.repo_fptr);
	return PDS_SUCCESS;
}

int pds_open( char *repo_name ) {
	if(pdsInfo.repo_status == PDS_OPEN) {
		return PDS_REPO_ALREADYOPEN;
	}
	pdsInfo.repo_fptr = fopen(repo_name,"a+");
	if(pdsInfo.repo_fptr == NULL){
		return PDS_OPEN_ERROR;
	}
	strcpy(pdsInfo.repo_name,repo_name);
	pdsInfo.repo_status = PDS_OPEN;
	return PDS_SUCCESS;
}

int pds_store( struct Contact *c ) {
	if(pdsInfo.repo_status == PDS_CLOSED) {
		return PDS_REPO_NOTOPEN;
	}
	if( pds_search_by_key(c->contact_id, c) == PDS_SUCCESS ){
		return PDS_DUPLICATE_RECORD;
	}
	fseek(pdsInfo.repo_fptr, 0, SEEK_END);
	if(fwrite(c, 1 , sizeof(struct Contact) , pdsInfo.repo_fptr)){
		return PDS_SUCCESS;
	}
	return PDS_STORE_ERROR;
}

int pds_search_by_key( int key, struct Contact *c ) {
	int i = 0;
	if(pdsInfo.repo_status == PDS_CLOSED) { //check if open
		return PDS_REPO_NOTOPEN;
	}
	fseek(pdsInfo.repo_fptr, 0, SEEK_END);  //move pointer to end to get file size
	long int len = ftell(pdsInfo.repo_fptr);
	fseek(pdsInfo.repo_fptr, 0, SEEK_SET);  //move pointer to beginning
	//struct Contact *buffer = (struct Contact*)malloc(sizeof(struct Contact));
	while(i < len / sizeof(struct Contact)){
		fread(c, sizeof(struct Contact), 1, pdsInfo.repo_fptr);
		if(c->contact_id == key) {
			//*c = *buffer;
			return PDS_SUCCESS;
		}
		i++;
		fseek(pdsInfo.repo_fptr, i*sizeof(struct Contact), SEEK_SET); //move pointer to start of next record
	}
	return PDS_REC_NOT_FOUND;
}

int pds_close() {
	if(pdsInfo.repo_status == PDS_CLOSED) {
		return PDS_REPO_NOTOPEN;
	}
	pdsInfo.repo_status = PDS_CLOSED;
	fclose(pdsInfo.repo_fptr);
	return PDS_SUCCESS;
}
