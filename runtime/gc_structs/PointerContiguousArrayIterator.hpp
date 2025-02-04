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

#if !defined(POINTERCONTIGUOUSARRAYITERATOR_HPP_)
#define POINTERCONTIGUOUSARRAYITERATOR_HPP_

#include "j9.h"
#include "j9cfg.h"
#include "ModronAssertions.h"

#include "ArrayObjectModel.hpp"
#include "Bits.hpp"
#include "GCExtensionsBase.hpp"
#include "ObjectIteratorState.hpp"
#include "SlotObject.hpp"
#include "ArrayletObjectModel.hpp"

/**
 * Iterate over all slots in a pointer array which contain an object reference
 * @ingroup GC_Structs
 */
class GC_PointerContiguousArrayIterator
{
private:
	J9IndexableObject *_arrayPtr;	/**< pointer to the array object being iterated */
	GC_SlotObject _slotObject;		/**< Create own SlotObject class to provide output */
	fj9object_t *_scanPtr;			/**< pointer to the current array slot */
	fj9object_t *_endPtr;			/**< pointer to the array slot where the iteration will terminate */

protected:
#if defined(OMR_GC_COMPRESSED_POINTERS) && defined(OMR_GC_FULL_POINTERS)
	bool const _compressObjectReferences;
#endif /* defined(OMR_GC_COMPRESSED_POINTERS) && defined(OMR_GC_FULL_POINTERS) */
	OMR_VM *_omrVM;

public:
	/**
	 * Return back true if object references are compressed
	 * @return true, if object references are compressed
	 */
	MMINLINE bool compressObjectReferences() {
		return OMR_COMPRESS_OBJECT_REFERENCES(_compressObjectReferences);
	}

	MMINLINE void initialize(J9Object *objectPtr)
	{
		MM_GCExtensionsBase *extensions = MM_GCExtensionsBase::getExtensions(_omrVM);
		bool const compressed = compressObjectReferences();

		_arrayPtr = (J9IndexableObject *)objectPtr;
		
		/* Set current and end scan pointers */
		_endPtr = GC_SlotObject::subtractFromSlotAddress((fj9object_t*)extensions->indexableObjectModel.getDataPointerForContiguous(_arrayPtr), 1, compressed);
		_scanPtr = GC_SlotObject::addToSlotAddress(_endPtr, extensions->indexableObjectModel.getSizeInElements(_arrayPtr), compressed);

	}

	MMINLINE GC_SlotObject *nextSlot()
	{
		if (_scanPtr > _endPtr) {
			/* Record the slot information */
			_slotObject.writeAddressToSlot(_scanPtr);

			/* Advance the scan pointer */
			_scanPtr = GC_SlotObject::subtractFromSlotAddress(_scanPtr, 1, compressObjectReferences());

			return &_slotObject;
		}

		/* No more object slots to scan */
		return NULL;
	}

	GC_PointerContiguousArrayIterator(OMR_VM *omrVM)
		: _arrayPtr(NULL)
		, _slotObject(GC_SlotObject(omrVM, NULL))
		, _scanPtr(NULL)
		, _endPtr(NULL)
#if defined(OMR_GC_COMPRESSED_POINTERS) && defined(OMR_GC_FULL_POINTERS)
		, _compressObjectReferences(OMRVM_COMPRESS_OBJECT_REFERENCES(omrVM))
#endif /* defined(OMR_GC_COMPRESSED_POINTERS) && defined(OMR_GC_FULL_POINTERS) */
		, _omrVM(omrVM)
	{
	}

	/**
	 * @param objectPtr the array object to be processed
	 */
	GC_PointerContiguousArrayIterator(OMR_VM *omrVM, J9Object *objectPtr)
		: _arrayPtr(NULL)
		, _slotObject(GC_SlotObject(omrVM, NULL))
		, _scanPtr(NULL)
		, _endPtr(NULL)
#if defined(OMR_GC_COMPRESSED_POINTERS) && defined(OMR_GC_FULL_POINTERS)
		, _compressObjectReferences(OMRVM_COMPRESS_OBJECT_REFERENCES(omrVM))
#endif /* defined(OMR_GC_COMPRESSED_POINTERS) && defined(OMR_GC_FULL_POINTERS) */
		, _omrVM(omrVM)
	{
		initialize(objectPtr);
	}

	MMINLINE J9Object *getObject()
	{
		return (J9Object *)_arrayPtr;
	}

	/**
	 * Gets the current slot's array index.
	 * @return slot number (or zero based array index) of the last call to nextSlot.
	 * @return undefined if nextSlot has yet to be called.
	 */
	MMINLINE UDATA getIndex() {
		return GC_SlotObject::subtractSlotAddresses(_scanPtr, _endPtr, compressObjectReferences());
	}

	MMINLINE void setIndex(UDATA index) {
		_scanPtr =  GC_SlotObject::addToSlotAddress(_endPtr, index, compressObjectReferences());
	}

	/**
	 * Restores the iterator state into this class
	 * @param[in] objectIteratorState partially scanned object iterator state
	 */
	MMINLINE void restore(GC_ObjectIteratorState *objectIteratorState) {
		_scanPtr = objectIteratorState->_scanPtr;
		_endPtr = objectIteratorState->_endPtr;
	}


	/**
	 * Saves the partially scanned state of this class
	 * @param[in] objectIteratorState where to store the state
	 */
	MMINLINE void save(GC_ObjectIteratorState *objectIteratorState) {
		objectIteratorState->_scanPtr = _scanPtr;
		objectIteratorState->_endPtr  = _endPtr;
	}
};

#endif /* POINTERCONTIGUOUSARRAYITERATOR_HPP_ */
