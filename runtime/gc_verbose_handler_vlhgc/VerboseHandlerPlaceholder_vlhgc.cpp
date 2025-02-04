/*******************************************************************************
 * Copyright (c) 1991, 2014 IBM Corp. and others
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at https://www.eclipse.org/legal/epl-2.0/
 * or the Apache License, Version 2.0 which accompanies this distribution and
 * is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following
 * Secondary Licenses when the conditions for such availability set
 * forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
 * General Public License, version 2 with the GNU Classpath
 * Exception [1] and GNU General Public License, version 2 with the
 * OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] https://openjdk.org/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
 *******************************************************************************/

/* Temporary file to make compilers happy */

#include "j9.h"
#include "j9cfg.h"
#include "mmhook.h"


void verboseHandlerCycleStart(J9HookInterface** hook, UDATA eventNum, void* eventData, void* userData)
{
	return ;
}

void verboseHandlerCycleEnd(J9HookInterface** hook, UDATA eventNum, void* eventData, void* userData)
{
	return ;
}


void verboseHandlerExclusiveStart(J9HookInterface** hook, UDATA eventNum, void* eventData, void* userData)
{
	return ;
}

void verboseHandlerExclusiveEnd(J9HookInterface** hook, UDATA eventNum, void* eventData, void* userData)
{
	return ;
}

void verboseHandlerSystemGCStart(J9HookInterface** hook, UDATA eventNum, void* eventData, void* userData)
{
	return ;
}

void verboseHandlerSystemGCEnd(J9HookInterface** hook, UDATA eventNum, void* eventData, void* userData)
{
	return ;
}


void verboseHandlerAllocationFailureStart(J9HookInterface** hook, UDATA eventNum, void* eventData, void* userData)
{
	return ;
}

void verboseHandlerAllocationFailureEnd(J9HookInterface** hook, UDATA eventNum, void* eventData, void* userData)
{
	return ;
}

void verboseHandlerMark(J9HookInterface** hook, UDATA eventNum, void* eventData, void* userData)
{
	return ;
}

void verboseHandlerSweep(J9HookInterface** hook, UDATA eventNum, void* eventData, void* userData)
{
	return ;
}

#if defined(J9VM_GC_MODRON_COMPACTION)
void verboseHandlerCompact(J9HookInterface** hook, UDATA eventNum, void* eventData, void* userData)
{
	return ;
}
#endif /* defined(J9VM_GC_MODRON_COMPACTION) */

#if defined(J9VM_GC_DYNAMIC_CLASS_UNLOADING)
void verboseHandlerClassUnloading(J9HookInterface** hook, UDATA eventNum, void* eventData, void* userData)
{
	return ;
}
#endif /* defined(J9VM_GC_DYNAMIC_CLASS_UNLOADING) */
