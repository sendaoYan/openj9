
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

#ifndef UNFINALIZEDOBJECTBUFFERVLHGC_HPP_
#define UNFINALIZEDOBJECTBUFFERVLHGC_HPP_

#include "j9.h"
#include "j9cfg.h"

#include "UnfinalizedObjectBuffer.hpp"

class MM_HeapRegionDescriptorVLHGC;
/**
 * A per-thread buffer of recently allocated unfinalized objects.
 * The buffer is periodically flushed to the global list. 
 */
class MM_UnfinalizedObjectBufferVLHGC : public MM_UnfinalizedObjectBuffer
{
private:
protected:
public:
	
private:
protected:

	virtual bool initialize(MM_EnvironmentBase *env);
	virtual void tearDown(MM_EnvironmentBase *env);

	/**
	 * Flush the contents of the buffer to the appropriate global buffers.
	 * Subclasses must override.
	 * @param env[in] the current thread
	 */
	virtual void flushImpl(MM_EnvironmentBase* env);
	
public:
	static MM_UnfinalizedObjectBufferVLHGC *newInstance(MM_EnvironmentBase *env);
	/**
	 * Construct a new buffer.
	 * @param extensions[in] the GC extensions
	 * @param maxObjectCount the maximum number of objects permitted before a forced flush 
	 */
	MM_UnfinalizedObjectBufferVLHGC(MM_GCExtensions *extensions, UDATA maxObjectCount);

	/**
	 * Returns this buffer's _region which is declared in the parent class.
	 * @return @ref _region
	 */
	MM_HeapRegionDescriptorVLHGC *getRegion();
};

#endif /* UNFINALIZEDOBJECTBUFFERVLHGC_HPP_ */
