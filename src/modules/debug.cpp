// Copyright 2015 Google Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "breadboard/modules/debug.h"

#include <string>

#include "breadboard/base_node.h"
#include "breadboard/module_registry.h"
#include "breadboard/log.h"

namespace breadboard {

// Prints a string to the logger.
class ConsolePrintNode : public BaseNode {
 public:
  virtual ~ConsolePrintNode() {}

  static void OnRegister(NodeSignature* node_sig) {
    node_sig->AddInput<void>();
    node_sig->AddInput<std::string>();
    node_sig->AddOutput<std::string>();
  }

  virtual void Execute(NodeArguments* args) {
    auto str = args->GetInput<std::string>(1);
    CallLogFunc("%s\n", str->c_str());
    args->SetOutput(0, *str);
  }
};

void InitializeDebugModule(ModuleRegistry* module_registry) {
  Module* module = module_registry->RegisterModule("debug");
  module->RegisterNode<ConsolePrintNode>("console_print");
}

}  // namespace breadboard
