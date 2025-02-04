<!--
Copyright (c) 2018, 2022 IBM Corp. and others

This program and the accompanying materials are made available under
the terms of the Eclipse Public License 2.0 which accompanies this
distribution and is available at https://www.eclipse.org/legal/epl-2.0/
or the Apache License, Version 2.0 which accompanies this distribution and
is available at https://www.apache.org/licenses/LICENSE-2.0.

This Source Code may also be made available under the following
Secondary Licenses when the conditions for such availability set
forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
General Public License, version 2 with the GNU Classpath
Exception [1] and GNU General Public License, version 2 with the
OpenJDK Assembly Exception [2].

[1] https://www.gnu.org/software/classpath/license.html
[2] https://openjdk.org/legal/assembly-exception.html

SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
-->

# JITServer Client Sessions

The server stores data associated with each client  in **client sessions** which persist as long as the client is connected. Client Sessions store client metadata and persistent caches. Relevant structures (detailed below) are defined in `runtime/JITClientSession.hpp`. All cached data that remains valid across compilations is stored there.

## Accessing ROM classes

Some of the most commonly used items in the client session data are the cached ROM classes. From a `J9Class` pointer (or equivalently, `TR_OpaqueClassBlock`), you can get the corresponding ROM class by calling `TR::CompilationInfoPerThread::getAndCacheRemoteROMClass`. Since ROM classes are read-only, the copies on the server can persist across compilations, unless they are redefined or unloaded. Processing of unloaded and redefined classes happens in `ClientSessionData::processUnloadedClasses`, which is called at the beginning of every compilation from `J9CompileDispatcher::compile`.

## Adding new items to the client session

1. Modify the relevant structure (`ClientSessionData`, `ClassInfo`, or `J9MethodInfo`) by adding a new field and change the constructor to initialize the new field. See below for information about what goes where.
2. Modify ClassInfoTuple (add to end)
3. Modify `enum ClassInfoDataType`
4. Modify `JITServerHelpers::cacheRemoteROMClass` and `JITServerHelpers::packRemoteROMClassInfo`
5. Modify `JITServerHelpers::getROMClassData`to return the new field when asked
6. Update the version `MINOR_NUMBER` for JITServer

## `ClientSessionData`

Stores the data for an individual client session. During a compilation, this is accessible via the method `TR::CompilationInfoPerThread::getClientData()`, typically referenced as `_compInfoPT->getClientData()`. For access during other times and lifetime information, see [`ClientSessionHT`](#clientsessionht).

This includes a few pointers to global objects in the JVM, the hash tables containing `ClassInfo` and `J9MethodInfo`, and the server copy of the CHTable.

## `ClassInfo`

Stores cached data about a class loaded on the client VM. This includes the ROM class, which is copied in full to the server, as well as other items which are just pointers to data on the client.`ClassInfo` will persist on the server until the corresponding Java class gets unloaded or replaced by HCR mechanism (which server also treats as a class unload event). At that point, server will be notified and the cache will be purged.

### Examples of data stored in `ClassInfo`

- `*parentClass` - pointer to the parent class of this class.
- `*_fieldAttributesCache` - pointer to a hash table of cp indices to attributes of a field at that index. The persistent version of a cache that stores field attributes, per-compilation version is inside resolved method.

## `J9MethodInfo`

Similar to `ClassInfo` but stores info about methods. Includes the ROM method, which is part of the ROM class, and some other pointers to client data. It is also purged when a corresponding class gets unloaded.

## `VMInfo`

Struct that stores vm-specific information that will never change during JVM's lifetime. Has to be requested from the client only once, by calling `ClientSessionData::getOrCacheVMInfo`. All subsequent calls to this method will return the cached `VMInfo` on the server.

### Client ID

Intended to uniquely represent a client, the client ID is a random number generated by the client in `J9Options.cpp` and sent to the server in the compilation request, where it is stored in the `J9ServerStream` object corresponding with the compilation. Note that currently, there is nothing done to prevent collisions between client IDs. Such a collision would probably lead to a crash, however unlikely.

## `ClientSessionHT`

Hash table of all client sessions, indexed by client ID. The table is periodically purged to delete sessions from clients which are no longer active.

Accessible via `TR::CompilationInfo::getClientSessionHT()`.

When accessing `ClientSessionData` through this table (via `ClientSessionHT::findClientSession`), it is important that you call `sessionData->decInUse()` after you are done with it to update the reference count. Usually this is not needed, since most access to `ClientSessionData` instead happen via `TR::CompilationInfoPerThread::getClientData()`, which is a reference which lives for the duration of the current compilation. So, `findClientSession` is only really used when outside of a compilation thread and when the compilation thread is initialized. There should only be a single active instance of `ClientSessionData` per compilation thread at any given time (otherwise you risk overflowing the reference count).
