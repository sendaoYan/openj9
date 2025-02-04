/*******************************************************************************
 * Copyright (c) 2001, 2014 IBM Corp. and others
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
package com.ibm.j9ddr.vm29.tools.ddrinteractive.gccheck;

import com.ibm.j9ddr.CorruptDataException;
import com.ibm.j9ddr.vm29.j9.gc.GCJNIGlobalReferenceIterator;
import com.ibm.j9ddr.vm29.pointer.PointerPointer;
import com.ibm.j9ddr.vm29.pointer.VoidPointer;
import com.ibm.j9ddr.vm29.pointer.generated.J9ObjectPointer;

import static com.ibm.j9ddr.vm29.tools.ddrinteractive.gccheck.CheckBase.*;

class CheckJNIGlobalReferences extends Check
{
	@Override
	public void check()
	{
		try {
			VoidPointer globalRefs = VoidPointer.cast(getJavaVM().jniGlobalReferences()); 
			GCJNIGlobalReferenceIterator jniGlobalReferenceIterator = GCJNIGlobalReferenceIterator.from();
			while(jniGlobalReferenceIterator.hasNext()) {
				PointerPointer slot = PointerPointer.cast(jniGlobalReferenceIterator.nextAddress());
				if(slot.notNull()) {
					if (_engine.checkSlotPool(slot, globalRefs) != J9MODRON_SLOT_ITERATOR_OK) {
						return;
					}
				}
			}
		} catch (CorruptDataException e) {
			// TODO: handle exception
		}
	}

	@Override
	public String getCheckName()
	{
		return "JNI GLOBAL REFS";
	}

	@Override
	public void print()
	{
		try {
			VoidPointer globalRefs = VoidPointer.cast(getJavaVM().jniGlobalReferences()); 
			GCJNIGlobalReferenceIterator jniGlobalReferenceIterator = GCJNIGlobalReferenceIterator.from();
			ScanFormatter formatter = new ScanFormatter(this, "jniGlobalReferences", globalRefs);
			while(jniGlobalReferenceIterator.hasNext()) {
				J9ObjectPointer slot = jniGlobalReferenceIterator.next();
				if(slot.notNull()) {
					formatter.entry(slot);
				}
			}
			formatter.end("jniGlobalReferences", globalRefs);
		} catch (CorruptDataException e) {
			// TODO: handle exception
		}
	}

}
