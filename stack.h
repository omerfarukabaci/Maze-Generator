#define MAZESIZE 9

struct cell {
	bool left, right, up, down; 
	char val; 
	bool visited;
};

typedef struct store{
	int x;
	int y;
}DataType;


struct Node{
	DataType data;
	Node *next;
};

struct Stack{
	Node *head;
	void create();
	void push(DataType*);
	DataType pop();
	bool isempty();
	void close();
	int counter = 1;
};
