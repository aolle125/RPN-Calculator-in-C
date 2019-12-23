/* Fill in your Name and GNumber in the following two comment fields
 * Name: VISHWAJEET VIJAY PARADKAR	
 * GNumber: G01222771
 */
 
#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "stack.h"

/* Create a new Stack_head struct on the Heap and return a pointer to it.
 * Follow the Directions in the Project Documentation for this Function
 * On any malloc errors, return NULL
 */
Stack_head *stack_initialize() {
	/* Malloc a new Stack_head and initialize it */
Stack_head *new = malloc(sizeof(Stack_head));
if(new == NULL) return NULL;	//Return NULL on any memory errors
else{
	//Set its count to 0 and next pointer to NULL
	new->count = 0;
	new->top = NULL;
	return new;
}
}

/* Destroy a stack.
 * Follow the Directions in the Project Documentation for this Function
 * If head is NULL, you can just return.
 */
void stack_destroy(Stack_head *head) {
	/* Initializing pointers of type Node and Token to NULL */
   Node *walker = NULL;
  Node *reaper = NULL;
  Token *tok = NULL;

  if(head == NULL) return;		//Return NULL on any memory errors
  else {
	  /* Free an entire Stack (nodes and head) */
    walker = head->top;
	//Iterating through the Stack
    while(walker != NULL) {
      reaper = walker;
      walker = walker->next;
	  tok = reaper->tok;
      token_free(tok);		//Freeing the token
	  free(reaper);			//Freeing the Node
      reaper = NULL;
    }
	free(walker);
    free(head);				//Finally,freeing the stack and setting to NULL
    head = NULL;
  }
  return;
}
 

/* Push a new Token on to the Stack.
 * Follow the Directions in the Project Documentation for this Function
 * On any malloc errors, return -1.
 * If there are no errors, return 0.
 */
int stack_push(Stack_head *stack, Token *tok) {
	/*Create a new Node using node_create
	  Passing in tok to it */
	Node *new = NULL;
 new = node_create(tok);
  if(new == NULL) return -1;		//Return -1 on any memory errors
  if(stack == NULL) return -1;		//Return -1 on any memory errors
  
  //Checking if Stack is empty and inserting token on top of stack
  if(stack_is_empty(stack)){
	  stack->top = new;		//Pushing on the top of the stack
	  stack->count = 1;		//Setting the count to 1
  return 0; }		
  else{
  new->next = stack->top;
      stack->top = new;		//Pushing on the top of the stack
      stack->count++;		//Incrementing the count of the stack
      return 0;
    }
	free(new);
	return -1;
  }

/* Pop a Token off of the Stack.
 * Follow the Directions in the Project Documentation for this Function
 * If the stack was empty, return NULL.
 */
Token *stack_pop(Stack_head *stack) {
	/* Initializing pointers of type Node and Token to NULL */
  Token *tok = NULL;
  Node *reaper = NULL;
  
  //If stack is empty, return NULL as no token is present
  if(stack == NULL || stack_is_empty(stack)) {
    return NULL;
  }
  else {
	  /*Remove the top Node from the stack
	    Return a pointer to the Token */
    tok = stack->top->tok;
    reaper = stack->top;
    stack->top = stack->top->next;
    node_free(reaper);		//Freeing the node reaper
    stack->count--;			//Decrementing the count of the stack
    return tok;				//Returning the Token
  }
  return NULL;
}

/* Return the token in the stack node on the top of the stack
 * Follow the Directions in the Project Documentation for this Function
 * If the stack is NULL, return NULL.
 * If the stack is empty, return NULL.
 */
Token *stack_peek(Stack_head *stack) {
	//If stack is empty, return NULL as no token is present
  if(stack == NULL || stack_is_empty(stack)) {
    return NULL;
  }
  else {  
    return stack->top->tok;	//Return the token in the stack node on the top of the stack
  }
   return NULL;
}
 

/* Return the number of nodes in the stack.
 * Follow the Directions in the Project Documentation for this Function
 * If stack is NULL, return -1.
 * Return 1 if the stack is empty or 0 otherwise.
 */
int stack_is_empty(Stack_head *stack) {
  if(stack == NULL) return -1;	//If stack is NULL, return -1
  if(stack->top == NULL) return 1;		//Return 1 when stack is empty
  else return 0;				//Return 0 if element present on the stack

}

/* These two functions are written for you.
 * It recurses the stack and prints out the tokens in reverse order
 * eg. top->2->4->1->8 will print at Stack: 8 1 4 2
 * eg. stack_push(5) will then print Stack: 8 1 4 2 5
 */

/* This is implemented for you.
 * Recursive print. (Local function)
 * Base Case: node == NULL, return
 * Recursive Case: call print_node(node->next, print_data), then print node.
 */
static void print_node(Node *node) {
  if(node == NULL) {
    return;
  }
  token_print(node->tok);
  print_node(node->next);
  return;
}

/* This is implemented for you.
 * Setup function for the recursive calls.  Starts printing with stack->top
 */
void stack_print(Stack_head *stack) {
  if(stack == NULL) {
    return;
  }
  printf("|-----Program Stack\n");
  printf("| ");
  print_node(stack->top);
  printf("\n");
  return;
}
