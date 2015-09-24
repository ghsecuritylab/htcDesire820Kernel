/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

#if defined(LIBM_SCCS) && !defined(lint)
static char rcsid[] = "$NetBSD: e_log.c,v 1.8 1995/05/10 20:45:49 jtc Exp $";
#endif


#include "math_private.h"

#ifdef __STDC__
static const double
#else
static double
#endif
ln2_hi  =  6.93147180369123816490e-01,	
ln2_lo  =  1.90821492927058770002e-10,	
Lg1 = 6.666666666666735130e-01,  
Lg2 = 3.999999999940941908e-01,  
Lg3 = 2.857142874366239149e-01,  
Lg4 = 2.222219843214978396e-01,  
Lg5 = 1.818357216161805012e-01,  
Lg6 = 1.531383769920937332e-01,  
Lg7 = 1.479819860511658591e-01;  

#ifdef __STDC__
	double __ieee754_log(double x)
#else
	double __ieee754_log(x)
	double x;
#endif
{
	double hfsq,f,s,z,R,w,t1,t2,dk;
	int32_t k,hx,i,j;
	u_int32_t lx;

	EXTRACT_WORDS(hx,lx,x);

	k=0;
	if (hx < 0x00100000) {			
	    if (((hx&0x7fffffff)|lx)==0)
		return -two54/zero;		
	    if (hx<0) return (x-x)/zero;	
	    k -= 54; x *= two54; 
	    GET_HIGH_WORD(hx,x);
	}
	if (hx >= 0x7ff00000) return x+x;
	k += (hx>>20)-1023;
	hx &= 0x000fffff;
	i = (hx+0x95f64)&0x100000;
	SET_HIGH_WORD(x,hx|(i^0x3ff00000));	
	k += (i>>20);
	f = x-1.0;
	if((0x000fffff&(2+hx))<3) {	
	    if(f==zero) {if(k==0) return zero;  else {dk=(double)k;
				 return dk*ln2_hi+dk*ln2_lo;}
	    }
	    R = f*f*(0.5-0.33333333333333333*f);
	    if(k==0) return f-R; else {dk=(double)k;
	    	     return dk*ln2_hi-((R-dk*ln2_lo)-f);}
	}
 	s = f/(2.0+f);
	dk = (double)k;
	z = s*s;
	i = hx-0x6147a;
	w = z*z;
	j = 0x6b851-hx;
	t1= w*(Lg2+w*(Lg4+w*Lg6));
	t2= z*(Lg1+w*(Lg3+w*(Lg5+w*Lg7)));
	i |= j;
	R = t2+t1;
	if(i>0) {
	    hfsq=0.5*f*f;
	    if(k==0) return f-(hfsq-s*(hfsq+R)); else
		     return dk*ln2_hi-((hfsq-(s*(hfsq+R)+dk*ln2_lo))-f);
	} else {
	    if(k==0) return f-s*(f-R); else
		     return dk*ln2_hi-((s*(f-R)-dk*ln2_lo)-f);
	}
}