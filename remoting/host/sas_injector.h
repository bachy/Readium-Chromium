// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_SAS_INJECTOR_H_
#define REMOTING_HOST_SAS_INJECTOR_H_

#include "base/memory/scoped_ptr.h"

namespace remoting {

// Provides a way to simulate a Secure Attention Sequence (SAS). The default
// sequence is Ctrl+Alt+Delete.
class SasInjector {
 public:
  virtual ~SasInjector() {}

  // Sends the Secure Attention Sequence to the console session.
  virtual bool InjectSas() = 0;

  // Creates an instance of SasInjector if supported by the OS, otherwise
  // returns NULL.
  static scoped_ptr<SasInjector> Create();
};

}  // namespace remoting

#endif REMOTING_HOST_SAS_INJECTOR_H_
