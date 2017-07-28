#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "pds.h"
struct PdsInfo pdsInfo;

int pds_create_index( char *repo_name, char *ndx_name ) {
	if(pdsInfo.repo_status == PDS_OPEN) { //if another file open
		return PDS_REPO_ALREADYOPEN;
	}
	pdsInfo.repo_fptr = fopen(repo_name,"r"); //data file trying to be created already exists
	if(pdsInfo.repo_fptr != NULL){
		fclose(pdsInfo.repo_fptr);
		return PDS_CREATE_ERROR;
	}
	pdsInfo.repo_fptr = fopen(repo_name,"a+"); //creation of data file
	if(pdsInfo.repo_fptr == NULL){
		return PDS_CREATE_ERROR;
	}
/*	pdsInfo.ndx_fptr = fopen(ndx_name,"r"); //index file trying to be created already exists
	if(pdsInfo.ndx_fptr != NULL){
		fclose(pdsInfo.ndx_fptr);
		return PDS_CREATE_ERROR;
	} */
	pdsInfo.ndx_fptr = fopen(ndx_name,"a+"); //creation of index file
	if(pdsInfo.ndx_fptr == NULL){
		return PDS_CREATE_ERROR;
	}
	strcpy(pdsInfo.repo_name,repo_name);
	pdsInfo.num_recs = 0;
	fwrite(&pdsInfo.num_recs, 1, sizeof(int), pdsInfo.ndx_fptr);
	fclose(pdsInfo.repo_fptr);
	fclose(pdsInfo.ndx_fptr);
	return PDS_SUCCESS;
}

int comprecs(const void* a, const void* b){
	struct PdsNdxInfo l = *(struct PdsNdxInfo *)a;
	struct PdsNdxInfo r = *(struct PdsNdxInfo *)b;
	if(l.key == r.key){
		return 0;
	}
	else if(l.key > r.key){
		return 1;
	}
	else
		return -1;
}

int pds_open( char *repo_name, char *ndx_name ) {
	if(pdsInfo.repo_status == PDS_OPEN) { //if file already open
		return PDS_REPO_ALREADYOPEN;
	}
	pdsInfo.repo_fptr = fopen(repo_name,"a+"); //opening file in append mode
	if(pdsInfo.repo_fptr == NULL){
		return PDS_OPEN_ERROR;
	}
	pdsInfo.ndx_fptr = fopen(ndx_name, "r"); //opening index file to read
	if(pdsInfo.ndx_fptr == NULL){
		return PDS_OPEN_ERROR;
	}
	fread(&pdsInfo.num_recs,sizeof(int),1,pdsInfo.ndx_fptr);
	//put content of index file into array
	fread(pdsInfo.ndxEntries, sizeof(struct PdsNdxInfo), pdsInfo.num_recs, pdsInfo.ndx_fptr);
	qsort((void*)pdsInfo.ndxEntries, pdsInfo.num_recs, sizeof(struct PdsNdxInfo), comprecs);
	for(int i=0;i<pdsInfo.num_recs;i++)
		printf("%d %d\n",pdsInfo.ndxEntries[i].key,pdsInfo.ndxEntries[i].offset);
	strcpy(pdsInfo.repo_name,repo_name);
	pdsInfo.repo_status = PDS_OPEN;
	fclose(pdsInfo.ndx_fptr);
	pdsInfo.ndx_fptr = fopen(ndx_name, "w"); //opening index file to write
	if(pdsInfo.ndx_fptr == NULL){
		return PDS_OPEN_ERROR;
	}
	return PDS_SUCCESS;
}

int pds_store( struct Contact *c ) {
	if(pdsInfo.repo_status == PDS_CLOSED) { //check if open
		return PDS_REPO_NOTOPEN;
	}
	//check if duplicate record being entered
	if( pds_search_by_key(c->contact_id, c) == PDS_SUCCESS ){
		return PDS_DUPLICATE_RECORD;
	}
	if(pdsInfo.num_recs+1 >=MAX_RECS)
		return PDS_REPOSITORY_FULL;
	fseek(pdsInfo.repo_fptr, 0, SEEK_END); //pointer goes to end of file
	long int offset = ftell(pdsInfo.repo_fptr); //get initial point of record in index file
	if(fwrite(c, 1 , sizeof(struct Contact) , pdsInfo.repo_fptr)){
		pdsInfo.ndxEntries[pdsInfo.num_recs].key = c->contact_id;
		pdsInfo.ndxEntries[pdsInfo.num_recs].offset = (int)offset;
		pdsInfo.num_recs++;
		return PDS_SUCCESS;
	}
	return PDS_STORE_ERROR;
}

int pds_search_by_key( int key, struct Contact *c ) {
	if(pdsInfo.repo_status == PDS_CLOSED) {
		return PDS_REPO_NOTOPEN;
	}
	for(int i=0; i<pdsInfo.num_recs;i++){
		if(pdsInfo.ndxEntries[i].key == key){
			fseek(pdsInfo.repo_fptr, pdsInfo.ndxEntries[i].offset, SEEK_SET);
			fread(c, sizeof(struct Contact), 1, pdsInfo.repo_fptr);
			return PDS_SUCCESS;
		}
	}
	return PDS_REC_NOT_FOUND;
}

int pds_close() {
	if(pdsInfo.repo_status == PDS_CLOSED) {
		return PDS_REPO_NOTOPEN;
	}
	pdsInfo.repo_status = PDS_CLOSED;
	fseek(pdsInfo.ndx_fptr, 0, SEEK_SET);
	fwrite(&pdsInfo.num_recs, 1, sizeof(int), pdsInfo.ndx_fptr);
	fwrite(pdsInfo.ndxEntries, pdsInfo.num_recs, sizeof(struct PdsNdxInfo), pdsInfo.ndx_fptr);	
	fclose(pdsInfo.repo_fptr);
	fclose(pdsInfo.ndx_fptr);
	return PDS_SUCCESS;
}
