// Library "intal" - Integer of arbitray length
// intal is a nonnegative integer of arbitrary length.
// The way the integer is stored is specific to the 
//  implementation as long as the interface is intact.

// DO NOT modify this header file.
// As usual, an implementation file implements all the functionalities decalred here
//  and a client file uses the functionalities declared here.

//String (array of chars with a null termination) of decimal digits converted to intal type.
//Input str has most significant digit at the head of the string.
//"void *" hides the format of intal.
//The returned pointer points to the intal "object. Client need not know the format of the intal.
//Even if the format of an intal is "char*" just like the input string, it's expected to a create
//a new copy because the intal object should be modifyable, but the input could be a constant literal.
void* intal_create(char* str);

//Destroy the created "object"
void intal_destroy(void* intal);

//Converts intal to a string of decimal digits for mostly display purpose.
//Returned string has most significant non-zero digit at the head of the string.
char* intal2str(void* intal);

//Increments the integer by one.
void intal_increment(void* intal);

//Decrements the integer by one.
//No change if the intal is zero because it is nonnegative integer.
void intal_decrement(void* intal);

//Adds two intals and returns their sum.
void* intal_add(void* intal1, void* intal2);

//Returns the difference (obviously, nonnegative) of two intals.
void* intal_diff(void* intal1, void* intal2);

//Multiplies two intals and returns the product.
void* intal_multiply(void* intal1, void* intal2);

//Integer division
//Retuns the integer part of the quotient of intal1/intal2.
void* intal_divide(void* intal1, void* intal2);

//Returns -1, 0, +1
int intal_compare(void* intal1, void* intal2);

//Returns intal1^intal2.
void* intal_pow(void* intal1, void* intal2);
