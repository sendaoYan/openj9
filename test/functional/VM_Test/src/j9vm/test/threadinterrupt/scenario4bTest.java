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
package j9vm.test.threadinterrupt;

class scenario4bTest {
	public static void main(String args[]) {
		scenario4bTest t = new scenario4bTest();
		t.Run();
	}

	public void Run() {
		Object a = new Object();
		Interrupter interrupter = new Interrupter(Thread.currentThread(), a);

		synchronized (a) {
			interrupter.start();
			try {
				System.out.println("main  waiting");
				a.wait(1000);
				System.out.println("main  done waiting");
			} catch (Exception e) {
				throw new Error("main shouldn't have been interrupted");
			}
		}
		System.out.println("SUCCESS");
	}

	class Interrupter extends Thread {
		Thread m_interruptee;
		Object m_a;

		Interrupter(Thread interruptee, Object a) {
			m_interruptee = interruptee;
			m_a = a;
		}

		public void run() {
			synchronized (m_a) {
				System.out.println("inter synced on a");
				System.out.println("inter notifying main");
				m_a.notify();
				System.out.println("inter done notifying main");
				System.out.println("inter notifying main");
				m_interruptee.interrupt();
				System.out.println("inter done interrupting main");
				System.out.println("inter sleeping for 5 seconds...");
				try {
					sleep(5 * 1000);
				} catch (Exception e) {
					System.out.println("!!! " + e);
				}
				System.out.println("inter done sleeping");
			}
		}
	}

}
