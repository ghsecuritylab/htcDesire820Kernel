/* 
 * The contents of this file are subject to the Mozilla Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/MPL/
 * 
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 * 
 * The Original Code is the Netscape Portable Runtime (NSPR).
 * 
 * The Initial Developer of the Original Code is Netscape
 * Communications Corporation.  Portions created by Netscape are 
 * Copyright (C) 1998-2000 Netscape Communications Corporation.  All
 * Rights Reserved.
 * 
 * Contributor(s):
 * 
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU General Public License Version 2 or later (the
 * "GPL"), in which case the provisions of the GPL are applicable 
 * instead of those above.  If you wish to allow use of your 
 * version of this file only under the terms of the GPL and not to
 * allow others to use your version of this file under the MPL,
 * indicate your decision by deleting the provisions above and
 * replace them with the notice and other provisions required by
 * the GPL.  If you do not delete the provisions above, a recipient
 * may use your version of this file under either the MPL or the
 * GPL.
 */


#ifndef prrwlock_h___
#define prrwlock_h___

#include "prtypes.h"

PR_BEGIN_EXTERN_C



typedef struct PRRWLock PRRWLock;

#define	PR_RWLOCK_RANK_NONE	0


NSPR_API(PRRWLock*) PR_NewRWLock(PRUint32 lock_rank, const char *lock_name);

NSPR_API(void) PR_DestroyRWLock(PRRWLock *lock);

NSPR_API(void) PR_RWLock_Rlock(PRRWLock *lock);

NSPR_API(void) PR_RWLock_Wlock(PRRWLock *lock);

NSPR_API(void) PR_RWLock_Unlock(PRRWLock *lock);

PR_END_EXTERN_C

#endif 
