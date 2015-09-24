
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define False  0
#define True   1
typedef int    Bool;

char* all_archs[] = {
   "x86",
   "amd64",
   "ppc32",
   "ppc64",
   "arm",
   "s390x",
   NULL
};

static Bool go(char* arch)
{ 
#if defined(VGP_x86_linux) || defined(VGP_x86_darwin)
   if ( 0 == strcmp( arch, "x86"   ) ) return True;

#elif defined(VGP_amd64_linux) || defined(VGP_amd64_darwin)
   if ( 0 == strcmp( arch, "x86"   ) ) return True;
   if ( 0 == strcmp( arch, "amd64" ) ) return True;

#elif defined(VGP_ppc32_linux)
   if ( 0 == strcmp( arch, "ppc32" ) ) return True;

#elif defined(VGP_ppc64_linux)
   if ( 0 == strcmp( arch, "ppc64" ) ) return True;
   if ( 0 == strcmp( arch, "ppc32" ) ) return True;

#elif defined(VGP_s390x_linux)
   if ( 0 == strcmp( arch, "s390x" ) ) return True;

#elif defined(VGP_arm_linux)
   if ( 0 == strcmp( arch, "arm" ) ) return True;

#else
#  error Unknown platform
#endif   

   return False;
}

int main(int argc, char **argv)
{
   int i;
   if ( argc != 2 ) {
      fprintf( stderr, "usage: arch_test <arch-type>\n" );
      exit(3);             
   }
   if (go( argv[1] )) {
      return 0;            
   }
   for (i = 0; NULL != all_archs[i]; i++) {
      if ( 0 == strcmp( argv[1], all_archs[i] ) )
         return 1;         
   }
   return 2;               
}
