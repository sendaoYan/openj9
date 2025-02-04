/*******************************************************************************
 * Copyright (c) 2001, 2018 IBM Corp. and others
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
// Test file: IntegerToLong.java
// Testing the casting  operation from integer to long type.

package jit.test.jitt.math2;

import org.testng.annotations.Test;
import org.testng.Assert;

@Test(groups = { "level.sanity","component.jit" })
public class IntegerToLong extends jit.test.jitt.Test {

   @Test
   public void testIntegerToLong() {

        int A;
        long B;

        A = -1;
        B = tstdoI2L(A);
        if (B != -1L)
                Assert.fail("IntegerToLong->run: Incorrect casting operation for test #1!");


        A = 1;
        B = tstdoI2L(A);
        if (B != 1L)
                Assert.fail("IntegerToLong->run: Incorrect casting operation for test #2!");


   }

   static long tstdoI2L(int A){
    long C=(long)A;

    return C;
   }

}



