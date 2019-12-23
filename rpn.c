/* Fill in your Name and GNumber in the following two comment fields
 * Name: VISHWAJEET VIJAY PARADKAR	
 * GNumber: G01222771
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "token.h"
#include "hash.h"

/* Local Function Declarations (that you need to finish implementing) */
static int read_file(char *filename, char *line);
static int parse_token(Symtab *symtab, Stack_head *stack, Token *tok);

/* Pre-Written Local Function Declarations */
static void print_header(char *filename, int step);
static void print_step_header(int step);
static void print_step_footer(Symtab *symtab, Stack_head *stack);
static void print_step_output(int val);
static int answers(int a,int b, int c);

/* Defines the largest line that can be read from a file */
#define MAX_LINE_LEN 255

/* This has been written for you.
 * Main function to run your program (written for you).
 * 1) Opens the file using the passed in filename. (your function)
 * -- If the file is not found (ie. fopen returns NULL), then exit(-1);
 * 2) Reads one line from the file.
 * -- The programs will all only be one line in size.
 * -- That line may be up to MAX_LINE_LEN long.
 * 3) Closes the file.
 * 4) Calls token_read_line(line, strlen(line))
 * -- This parses the line and prepares the tokens to be ready to get.
 * 5) While there are tokens remaining to parse: token_has_next() != 0
 * -- a) Get the next token: token_get_next()
 * 6) Parse the token (your function)
 * 7) Print out all of the relevant information
 */
int rpn(Stack_head *stack, Symtab *symtab, char *filename) {
  int step = 0; /* Used to track the program steps */
  int ret = 0;
  char line[MAX_LINE_LEN];
  Token *tok = NULL;

  /* Complete the read_file function that is defined later in this file. */
  ret = read_file(filename, line);
  if(ret != 0) {
    printf("Error: Cannot Read File %s.  Exiting\n", filename);
    exit(-1);
  }

  /* Pass the line into the tokenizer to initialize that system */
  token_read_line(line, strlen(line));

  /* Prints out the nice program output header */
  print_header(filename, step);

  /* Iterate through all tokens */
  while(token_has_next()) {
    /* Begin the next step of execution and print out the step header */
    step++; /* Begin the next step of execution */
    print_step_header(step);

    /* Get the next token */
    tok = token_get_next();
    /* Complete the implementation of this function later in this file. */
    ret = parse_token(symtab, stack, tok);
    if(ret != 0) {
      printf("Critical Error in Parsing.  Exiting Program!\n");
      exit(-1);
    }

    /* Prints out the end of step information */
    print_step_footer(symtab, stack);
  }

  return 0;
}

 /* Local function to open a file or exit.
 * Follow the Directions in the Project Documentation for this Function
 * Open filename, read its contents (up to MAX_LINE_LEN) into line, then
 *   close the file and return 0.
 * On any file error, return -1.
 */
static int read_file(char *filename, char *line) {
	/*Open the file for reading, read the line into line (up to MAX_LINE_LEN)
	  and then close the file*/
	FILE *fp = NULL;		//Setting the file pointer fp to NULL
	fp = fopen(filename,"r");		//Using fopen to Open the File for reading
	if(fp == NULL) return -1;		//On any memory or file errors, return -1.
	fgets(line,MAX_LINE_LEN,fp);	//Reading from the File
	fclose(fp);						//Closing the File
	return 0;
}

/* (IMPLEMENT THIS FUNCTION)
 * Parses the Token to implement the rpn calculator features
 * Follow the Directions in the Project Documentation for this Function
 * You may implement this how you like, but many small functions would be good!
 * If the token you are passed in is NULL, return -1.
 * If there are any memory errors, return -1.
 */
static int parse_token(Symtab *symtab, Stack_head *stack, Token *tok) {
  if(stack == NULL) return -1;		//Returning -1 on memory errors
  if(tok == NULL) return -1;		//Returning -1 on memory errors
  
 /* Initializing variables to use */
  int c = 0 , d = 0;
  int a = 0, b = 0;
  d = tok->type;		//Setting 'd' to the type of token
  
   /* Initializing Pointers to use */
  Token *reaper = NULL, *reaper1 = NULL, *answer = NULL;
  Symbol *sym = NULL, *sym1 = NULL;
  char *var = NULL;
  
  //Using Switch Case to check type of Token
  switch(d){
	  case TYPE_VALUE:
	  /* Push the token on to the stack and return it */
	  c = stack_push(stack,tok);		//Pushing it on to the stack
	  return c;
	  break;
	  
	  case TYPE_OPERATOR:
	  /* 1. Pop two tokens off the stack,
		 2. Perform the operation on them, 
		 3. Push the result */
		 
	//Pop two tokens off the stack and saving their values in a and b
	  reaper = stack_pop(stack);	
	  a = reaper->value;
	  reaper1 = stack_pop(stack);
	  b = reaper1->value;
	  c = tok->oper;
	  /* When there are no variables popped from the stack 
		 We can directly perform operations on the variables 
		 and Push the results onto the stack*/
	  if(reaper1->type != TYPE_VARIABLE && reaper->type != TYPE_VARIABLE){
		  //Performing addition and pushing on the stack
		d = answers(a,b,c);
		answer = token_create_value(d);	//Creating the token using token_create_value()
		stack_push(stack, answer);		//Pushing it on to the stack
	  return 0;
	  }
	  
	  /* When there are variables popped from the stack 
		 we will need to pass it’s variable field into the 
		 hash_get function to get its current value from the 
		 symbol table. 
		 In this specific case, we’ll get back a Symbol struct with the current
		 variable and val information */
	 if((reaper->type) == TYPE_VARIABLE && (reaper1->type) == TYPE_VARIABLE){
		  sym = hash_get(symtab,reaper->variable);		//Getting the values from the symbol Table
		  sym1 = hash_get(symtab,reaper1->variable);	//Getting the values from the symbol Table
	  a = sym->val;
	  b = sym1->val;
		d = answers(a,b,c);
		answer = token_create_value(d);	//Creating the token using token_create_value()
		stack_push(stack, answer);		//Pushing it on to the stack
	  return 0;
	 }
	  
	  	 /* When only the first token popped from the stack 
		  is a variable we will need to pass it’s variable field into the 
		 hash_get function to get its current value from the 
		 symbol table. 
		 In this specific case, we’ll get back a Symbol struct with the current
		 variable and val information */
	  
	  if((reaper->type) == TYPE_VARIABLE && (reaper1->type) != TYPE_VARIABLE){
		  sym = hash_get(symtab,reaper->variable);		//Getting the values from the symbol Table
	  a = sym->val;
		d = answers(a,b,c);
		answer = token_create_value(d);	//Creating the token using token_create_value()
		stack_push(stack, answer);		//Pushing it on to the stack
	  return 0;
	  }
	  
	  
	   /* When only the second token popped from the stack 
		  is a variable we will need to pass it’s variable field into the 
		 hash_get function to get its current value from the 
		 symbol table. 
		 In this specific case, we’ll get back a Symbol struct with the current
		 variable and val information */
	  if((reaper->type) != TYPE_VARIABLE && (reaper1->type) == TYPE_VARIABLE){
		  sym = hash_get(symtab,reaper1->variable);		//Getting the values from the symbol Table
		  b = sym->val;
		d = answers(a,b,c);
		answer = token_create_value(d);	//Creating the token using token_create_value()
		stack_push(stack, answer);		//Pushing it on to the stack
	  return 0;
	  }
		  
		  
	 return -1;
	 break;
	 
	 /* Token (tok) you are passed in has type == TYPE_VARIABLE, 
		then you will need to push it on to the stack*/
	 case TYPE_VARIABLE:
	 c = stack_push(stack,tok);
	  return c;
	  break;
	  
	 /*Pop two tokens off the stack (value and variable)
	   Put it in the symbol table. */ 
	case TYPE_ASSIGNMENT:
	 reaper = stack_pop(stack);		//Popping token from the stack
	 a = reaper->value;
	  reaper1 = stack_pop(stack);	//Popping token from the stack
	  var = reaper1->variable;
	  c = hash_put(symtab,var,a);	//Putting it in the symbol table
	  return c;
	  break;
	
	/* Pop one token off the stack and print it to the screen as output */
	case TYPE_PRINT:
	reaper = stack_pop(stack);		//Popping token from the stack
	
	//If token is of type variable, then we need to get the value
	//Of the Token and thing printing the output
	if(reaper->type == TYPE_VARIABLE){
		sym = hash_get(symtab,reaper->variable);
		a = sym->val;
		print_step_output(a);
		return 0;
	}
	else {
		print_step_output(reaper->value);
	return 0; }
	break;
	
}
return -1;
}


/* Creating a Basic Funtion that will perform the operation
    And send the results back to the parse_token function*/
static int answers(int a,int b, int c){
	int ans = 0;
	switch(c){
		case OPERATOR_PLUS:
		ans = a + b;
		return ans;
		break;
		
		case OPERATOR_MINUS:
		ans = b - a;
		return ans;
		break;

		case OPERATOR_MULT:
		ans = a * b;
		return ans;
		break;
		
		case OPERATOR_DIV:
		ans = b / a;
		return ans;
		break;
	}
return -1;
		
}
/* This has been written for you.
 * Prints out the main output header
 */
static void print_header(char *filename, int step) {
  printf("######### Beginning Program (%s) ###########\n", filename);
  printf("\n.-------------------\n");
  printf("| Program Step = %2d\n", step);
  token_print_remaining();
  printf("o-------------------\n");
}

/* This has been written for you.
 * Prints out the information at the top of each step
 */
static void print_step_header(int step) {
  printf("\n.-------------------\n");
  printf("| Program Step = %2d\n", step++);
}

/* This has been written for you.
 * Prints out the output value (print token) nicely
 */
static void print_step_output(int val) {
  printf("|-----Program Output\n");
  printf("| %d\n", val);
}

/* This has been written for you.
 * Prints out the information at the bottom of each step
 */
static void print_step_footer(Symtab *symtab, Stack_head *stack) {
  hash_print_symtab(symtab);
  stack_print(stack);
  token_print_remaining();
  printf("o-------------------\n");
}
