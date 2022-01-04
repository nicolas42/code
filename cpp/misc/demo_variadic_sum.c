// https://www.tutorialspoint.com/c_standard_library/c_macro_va_start.htm

int variadic_sum(int num_args, ...) {
   int val = 0;
   va_list ap;
   int i;

   va_start(ap, num_args);
   for(i = 0; i < num_args; i++) {
      val += va_arg(ap, int);
   }
   va_end(ap);
 
   return val;
}

int demo_variadic_sum(void) {
   printf("Sum of 10, 20 and 30 = %d\n",  variadic_sum(3, 10, 20, 30) );
   printf("Sum of 4, 20, 25 and 30 = %d\n",  variadic_sum(4, 4, 20, 25, 30) );

   return 0;
}

int main()
{
    demo_variadic_sum();
    return 0;
}