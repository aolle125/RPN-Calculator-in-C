/* Fill in your Name and GNumber in the following two comment fields
 * Name: VISHWAJEET VIJAY PARADKAR	
 * GNumber: G01222771
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "hash.h"

/* (IMPLEMENT THIS FUNCTION)
 * In this function, you will create a new Symtab struct.
 * Follow the Directions in the Project Documentation for this Function
 * Return the pointer to the new symtab.
 * On any memory errors, return NULL
 */
Symtab *hash_initialize() {
	/* Creating and Initializing a new Symbol Table */
  Symtab *new = malloc(sizeof(Symtab));
  
	// Checking whether there were any errors
  if(new == NULL) return NULL;
  
	/*Setting the Size and Capacity of the New Symbol Table
    to 0 and HASH_TABLE_INITIAL respectively */
	
    new->size = 0;
  new->capacity = HASH_TABLE_INITIAL;
    int i = 0;
	
	//Allocation of Space for a new table on the Symtab
  Symbol **table = malloc(sizeof(Symbol *) * HASH_TABLE_INITIAL);
  
	//Initializing all the index elements to NULL
   while(i<HASH_TABLE_INITIAL){
	table[i] = NULL;
  i++; }
  new->table = table;
  return new;	//Returning the Symbol Table
}

/* (IMPLEMENT THIS FUNCTION)
 * Destroy your Symbol Table.
 * Follow the Directions in the Project Documentation for this Function
 * Return on any memory errors.
 */
void hash_destroy(Symtab *symtab) {
	// Returning out of the function if any error
	if(symtab == NULL) return;
	int i = 0;
	Symbol *walker = NULL;
	Symbol *reaper = NULL;
	
	/* Going through each Index in the table and freeing Linked List
	   Symbols in there */
	   
	for(i = 0;i<(symtab->capacity);i++){
	  walker = symtab->table[i];		//Setting Walker to the index in the Symbol Table
	  if(walker == NULL) return;		//Return NULL if empty
	  while(walker != NULL){			//Iterating through the linked list symbols
		  reaper = walker;
		  walker = walker->next;
		  symbol_free(reaper);			//Freeing the linked list symbols
		  reaper = NULL;
	  }
	}
	free(walker);
	free(symtab);
}

/*
 * Return the capacity of the table inside of symtab.
 * If symtab is NULL, return -1;
 */
int hash_get_capacity(Symtab *symtab) {
  if(symtab == NULL) return -1;
return symtab->capacity;
}

/* 
 * Return the number of used indexes in the table (size) inside of symtab.
 * If symtab is NULL, return -1;
 */
int hash_get_size(Symtab *symtab) {
if(symtab == NULL) return -1;
return symtab->size;
}


/* Either adding a new variable to the Hash Table
   or Updating an existing one */
   
int hash_put(Symtab *symtab, char *var, int val) {
	if(symtab == NULL) return -1;		// Checking whether there were any errors
	Symbol *walker = NULL, *reaper = NULL, *sym = NULL;		//Initializing pointers of type Symbol to NULL
	
	/* Calculating the index by taking the hash code and taking it modulus the capacity.
	   Also Calculating the Load which is Size/Capacity */
	long ans = hash_code(var);
	int index = ((ans) % (symtab->capacity));
	double load = ((double)symtab->size)/((double)symtab->capacity);
	
	
/*If already have this variable in the hash table
 update its val to the new val */
 
	walker = symtab->table[index];
    while(walker != NULL){
        if(strcmp(var, walker->variable) == 0)		//Comparing the variables using strcmp
        walker->val = val;							//Updating its value if found
	walker = walker->next;
    }
    sym = symbol_create(var,val);					//Creating the symbol to insert at the given index
	if(symtab->table[index] == NULL){				//Checking if the index is NULL and adding the symbol
        symtab->table[index] = sym;
        (symtab->size)++ ;							//Incrementing size of the Symbol Table by 1
    }
    else{
		/* Iterating through the Linked List
		    and inserting the symbol to the end*/
		reaper = symtab->table[index];			
        while(reaper->next != NULL)
        {
           reaper = reaper->next;
        }
        reaper->next = sym;
        (symtab->size)++;							//Incrementing size of the Symbol Table by 1
    }
	
	//Check to see if the load is >= 2.0 then rehash
	if(load >= 2.0) { 
    hash_rehash(symtab, 2*symtab->capacity);
    }
  return 0;
}
	
 
 /* Gets the Symbol for a variable in the Hash Table.
 * Follow the Directions in the Project Documentation for this Function
 * On any NULL symtab or memory errors, return NULL
 */
Symbol *hash_get(Symtab *symtab, char *var) {
	Symbol *sym = malloc(sizeof(Symbol));	//Declaring a Symbol pointer sym to use for symbol_copy
	Symbol *walker = NULL;					//Initializing Symbol pointer walker to NULL
	if(symtab == NULL) return NULL;			//Checking whether there were any errors
	/* Calculating the index by taking the hash code and taking it modulus the capacity */
	long ans = hash_code(var);
	int index = (ans) % (symtab->capacity);
	walker = symtab->table[index];			//Initializing Walker to the table at the calculated index
	//Check the linked list at the index for a Symbol with a matching var.
	while(walker!=NULL){
		if(strcmp(var, walker->variable) == 0){
			////Use the symbol_copy function to copy and return a pointer to the copy.
			sym = symbol_copy(walker);	
			return sym;		//Returning a pointer to the copy
		}
		walker = walker->next;
	}
		return NULL;		//Returning NULL pointer
	}
	
 /* Doubles the size of the Array in symtab and rehashes.
 * Follow the Directions in the Project Documentation for this Function
 * If there were any memory errors, set symtab->array to NULL
 * If symtab is NULL, return immediately.
 */

void hash_rehash(Symtab *symtab, int new_capacity) {
	if (symtab == NULL) return;		//Checking whether there were any errors
  Symbol **table = malloc(sizeof(Symbol *) * new_capacity);		//Allocation of Space for a new table on the Symtab
	//Initializing variables to be used
  int i=0;
  long ans = 0;
  int index = 0; 
  //Initializing all the index elements to NULL
  while(i<new_capacity){
	table[i] = NULL;
  i++; }
  Symbol *walker = NULL, *reaper = NULL;		//Initializing Symbol pointer variables to be used
  
  /*Walk through the old table and put each Symbol’s data into the new table. */
  
   for(i = 0; i<(symtab->capacity); i++)
  {
    walker = symtab->table[i];		//Initializing walker to the index in the Symbol Table
    while (walker != NULL)
    {
		/* Calculating the index by taking the hash code and taking it modulus the capacity */
		ans = hash_code(walker->variable);
		index = ((ans) % (new_capacity));
		
		//If Index is empty, putting the symbol data at that index of new table
      if(table[index] == NULL) 
		  table[index] = symbol_copy(walker);
      else
      {
		  /* Iterating through the new table
		    and inserting the symbol to the end*/
		  reaper = table[index];
        while (reaper->next != NULL)
        {
          reaper = reaper->next;
        }
        reaper->next = symbol_copy(walker);
      }
      walker = walker->next;
    }
  }
  
//Free all of the old Symbols and the old Table
  for(i = 0;i<(symtab->capacity);i++){
	  walker = symtab->table[i];		
	  if(walker == NULL) return;
	  while(walker != NULL){
		  reaper = walker;
		  walker = walker->next;
		  symbol_free(reaper);		//Freeing Reaper which is of Symbol type
		  reaper = NULL;
	  }
}

//Update the symtab’s table to point to the new table having the new capacity
symtab->capacity = new_capacity;
symtab->table = table;
}
 

/* Implemented for you.
 * Provided function to print the symbol table */
void hash_print_symtab(Symtab *symtab) {
  if(symtab == NULL) {
    return;
  }
  printf("|-----Symbol Table [%d size/%d cap]\n", symtab->size, symtab->capacity);

  int i = 0;
  Symbol *walker = NULL;

  /* Iterate every index, looking for symbols to print */
  for(i = 0; i < symtab->capacity; i++) {
    walker = symtab->table[i];
    /* For each found linked list, print every symbol therein */
    while(walker != NULL) {
      printf("| %10s: %d \n", walker->variable, walker->val);
      walker = walker->next;
    }
  }
  return;
}

/* This function is written for you.
 * This comreaperes the hash function for a String
 */
long hash_code(char *var) {
  long code = 0;
  int i;
  int size = strlen(var);

  for(i = 0; i < size; i++) {
    code = (code + var[i]);
    if(size == 1 || i < (size - 1)) {
      code *= 128;
    }
  }

  return code;
}
