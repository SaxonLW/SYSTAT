typedef struct stringPack{
	void * func;
	char * string;
	unsigned int length;
}stringPack;

typedef struct stringNode {
	void * func;
	struct stringNode * links [256];
}sNode;

extern void traverseTree(sNode * node, unsigned int depth);

extern void addString (stringPack val);

extern void newStringPack (stringPack * stringPack, char * string, void * p, unsigned int length);

extern sNode * getHead ();
