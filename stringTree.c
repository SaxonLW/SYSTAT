#include "SYSTAT.h"
#include "stringTree.h"
#include <stdlib.h>
#include <stdio.h>

sNode head;

sNode * getHead (){
	return &head;
}


void newStringPack (stringPack * stringPack, char * string, void * p, unsigned int length){
	stringPack->string = string;
	stringPack->func = p;
	stringPack->length = length;
}

/*
 * Apparently you cant just zero memory for pointers as NULL does not always point to 0
 */
sNode* newSNode (){
	int i;

	sNode * foo = malloc(sizeof(sNode));
	foo->func = NULL;

	for (i = 0; i < 256; i++){
		foo->links[i] = NULL;
	}
}

void addString (stringPack val){
	int i;
	sNode * currentNode = &head;

	for (i = 0; i < val.length; i++){
		//If the link is already active traverses immediately
		if (currentNode->links[val.string[i]] != NULL){
			currentNode = currentNode->links[val.string[i]];
		}
		else{
			currentNode->links[val.string[i]] = newSNode();
			currentNode = currentNode->links[val.string[i]];
		}
	}
	//printf("\n");
	currentNode->func = val.func;
}
