/*******************************************************************************
 * Copyright (c) 2001, 2017 IBM Corp. and others
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
package com.ibm.j9.uma.configuration.freemarker;

import java.util.Iterator;
import java.util.Set;

import com.ibm.j9.uma.configuration.ConfigurationImpl;

import freemarker.template.TemplateCollectionModel;
import freemarker.template.TemplateModel;
import freemarker.template.TemplateModelException;
import freemarker.template.TemplateModelIterator;

public class Source implements TemplateCollectionModel {
	
	ConfigurationImpl config;
	Set<String> projects;
	
	public Source(ConfigurationImpl config) {
		this.config = config;
		projects = config.getBuildSpec().getSources().keySet();
	}

	public Source(ConfigurationImpl config, Set<String> projects) {
		this.config = config;
		this.projects = projects;
	}


	class ProjectIterator implements TemplateModelIterator {
		Iterator<String> iterator;
	
		public ProjectIterator() {
			iterator = projects.iterator();
		}
		public boolean hasNext() throws TemplateModelException {
			return iterator.hasNext();
		}
		public TemplateModel next() throws TemplateModelException {
			return new Project(config, iterator.next());			
		}
	}
	
	public TemplateModelIterator iterator() throws TemplateModelException {
		return new ProjectIterator();
	}

}
