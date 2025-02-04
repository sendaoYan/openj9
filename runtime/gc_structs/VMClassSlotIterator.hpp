
/*******************************************************************************
 * Copyright (c) 1991, 2021 IBM Corp. and others
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

/**
 * @file
 * @ingroup GC_Structs
 */

#if !defined(VMCLASSSLOTITERATOR_HPP_)
#define VMCLASSSLOTITERATOR_HPP_

#include "j9.h"
#include "j9cfg.h"
#include "modron.h"

/**
 * Iterate over all slots in VM known classes that contain object references.
 * @ingroup GC_Structs
 */
class GC_VMClassSlotIterator
{
	J9Class **_scanPtr;
	J9Class **_endPtr;

public:
	GC_VMClassSlotIterator(J9JavaVM *javaVM) :
		_scanPtr( &javaVM->voidReflectClass ),
		_endPtr( &javaVM->longArrayClass + 1 )
	{};

	J9Class *nextSlot();

};

#endif /* VMCLASSSLOTITERATOR_HPP_ */

