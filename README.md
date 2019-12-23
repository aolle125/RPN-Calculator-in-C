For this assignment, I am going to use C and the Stack and Hash Table data structures to implement
a Postfix-notation (RPN) Calculator. This calculator will read in a one-line program from a file. This
line read from the file will then be passed into a pre-written tokenizer, which will take every individual
piece of the program and turn them into tokens. In every step of the calculator, the calculator will get
the next token and I will process it by either pushing it into a stack, or by executing the operation
the token represents. This calculator will work with both number values and variables, which will be
stored as Symbols with a variable name and a value in a symbol table (hash table).
