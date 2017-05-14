/* file: sumfunction.i */
%module sumfunction
%{
/* Everything in the %{ }% block will be copied in the wrapper file.
   Here, we include C header files necessary to compile the interface
*/
#include "sumfunction.h"
%}

%include "typemaps.i"

/* list functions to be interfaced: */
void sum1(double r1, double r2, double *OUTPUT); /* OUTPUT indicates an return variable */

/* Alternative: */
/* %apply double *OUTPUT { double* s }  */ /* apply rule that defines the argument *s as an output variable */
/* void sum1(double r1, double r2, double *s); */

void sum2(double r1, double r2);
