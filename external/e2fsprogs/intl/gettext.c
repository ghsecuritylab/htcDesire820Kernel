/* Implementation of gettext(3) function.
   Copyright (C) 1995, 1997, 2000-2003 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU Library General Public License as published
   by the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
   USA.  */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#ifdef _LIBC
# define __need_NULL
# include <stddef.h>
#else
# include <stdlib.h>		
#endif

#include "gettextP.h"
#ifdef _LIBC
# include <libintl.h>
#else
# include "libgnuintl.h"
#endif


#ifdef _LIBC
# define GETTEXT __gettext
# define DCGETTEXT INTUSE(__dcgettext)
#else
# define GETTEXT libintl_gettext
# define DCGETTEXT libintl_dcgettext
#endif

char *
GETTEXT (const char *msgid)
{
  return DCGETTEXT (NULL, msgid, LC_MESSAGES);
}

#ifdef _LIBC
weak_alias (__gettext, gettext);
#endif
