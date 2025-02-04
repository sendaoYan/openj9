/*******************************************************************************
 * Copyright (c) 1991, 2020 IBM Corp. and others
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

#ifndef jextractnatives_api_h
#define jextractnatives_api_h

/**
* @file jextractnatives_api.h
* @brief Public API for the JEXTRACTNATIVES module.
*
* This file contains public function prototypes and
* type definitions for the JEXTRACTNATIVES module.
*/

#include "j9.h"
#include "j9comp.h"
#include "jni.h"

/* this is a debugger extension so include the common interface it extends */
#include "dbgext_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------- jextractnatives.c ---------------- */

/**
* @brief
* @param *env
* @param obj
* @param dumpObj
* @param commandObject
* @return void
*/
void JNICALL
Java_com_ibm_jvm_j9_dump_extract_Main_doCommand(JNIEnv *env, jobject obj, jobject dumpObj, jstring commandObject);

/**
* @brief
* @param *env
* @param obj
* @param dumpObj
* @param disableBuildIdCheck
* @return jlong environment pointer
*/
jlong JNICALL
Java_com_ibm_jvm_j9_dump_extract_Main_getEnvironmentPointer(JNIEnv * env, jobject obj, jobject dumpObj, jboolean disableBuildIdCheck);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* jextractnatives_api_h */
