#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int val;
    struct node *next;
} node_t;


node_t *head = NULL;
node_t *rear = NULL;



void enqueue(int val) {
    node_t *new_node = (node*)malloc(sizeof(node_t));
    if (!new_node) return;
	
	if(head==NULL){
		head=new_node;
		rear=new_node;
	}
    new_node->val = val;
    rear->next=new_node;
    rear=new_node;
    new_node->next=NULL;
        
}

int dequeue(){
	if(head==NULL)return -1;
	else{
		int a=head->val;
		node_t *current=head;
		head=head->next;
		free(current);
		if(head==NULL)rear=NULL;
		return a;
	
	}
		
}


void print_Q() {
    node_t *current = head;

    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}


int main() {
    
    int ret;

    enqueue( 11);
    enqueue( 22);
    enqueue( 33);
    enqueue( 44);

    print_Q();
    
    while (head!=NULL) {
    	ret=dequeue();
        printf("dequeued %d\n", ret);
    }
    printf("done. head=%p\n", head);

    return 0;
}
