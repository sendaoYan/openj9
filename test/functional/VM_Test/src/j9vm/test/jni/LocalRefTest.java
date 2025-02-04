/*******************************************************************************
 * Copyright (c) 2001, 2012 IBM Corp. and others
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
package j9vm.test.jni;

public class LocalRefTest  {

public static void main(String[] args) {
	try {
		System.loadLibrary("j9ben");
		LocalRefTest test = new LocalRefTest();
		if( !test.testPushLocalFrame1()) {
			// Throw an exception if we get false back
			System.out.println("**FAILURE** JNI Push/PopLocalFrame not working, or weak JNI references don't work");
			throw new RuntimeException();
		}
		if( !test.testPushLocalFrame2()) {
			// Throw an exception if we get false back
			System.out.println("**FAILURE** JNI Push/PopLocalFrame not working, or weak JNI references don't work");
			throw new RuntimeException();
		}
		if( !test.testPushLocalFrame3()) {
			// Throw an exception if we get false back
			System.out.println("**FAILURE** JNI Push/PopLocalFrame not working, or weak JNI references don't work");
			throw new RuntimeException();
		}
		if( !test.testPushLocalFrame4()) {
			// Throw an exception if we get false back
			System.out.println("**FAILURE** JNI Push/PopLocalFrame not working, or weak JNI references don't work");
			throw new RuntimeException();
		}
		if( !test.testPushLocalFrameNeverPop()) {
			// Throw an exception if we get false back
			System.out.println("**FAILURE** JNI extra pushed frames not being cleaned up correctly");
			throw new RuntimeException();
		}
	} catch (UnsatisfiedLinkError e) {
		System.out.println("Problem opening JNI library");
		e.printStackTrace();
		throw new RuntimeException();
	}
	System.out.println("JNI Push/PopLocalFrame seem to work");
}
	
public native boolean testPushLocalFrame1();
public native boolean testPushLocalFrame2();
public native boolean testPushLocalFrame3();
public native boolean testPushLocalFrame4();
public native boolean testPushLocalFrameNeverPop();
}
