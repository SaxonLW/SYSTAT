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

sNode* newSNode (){
	int i;

	sNode * foo = malloc(sizeof(sNode));
	foo->func = NULL;

	for (i = 0; i < 256; i++){
		foo->links[i] = NULL;
	}

}

void traverseTree(sNode * node, unsigned int depth){
	char i;
	unsigned int j;
	for (i = 0; i < 256; i++){
		if (node->links[i] != NULL){
			for(j=0; j<=depth; j++){
				printf("\t");
			}
			printf("%c\n", i);

			traverseTree(node->links[i], depth++);

		}
	}
	return;
}

void addString (stringPack val){
	int i;
	sNode * currentNode = &head;
	//printf("%s\n", val.string);

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
