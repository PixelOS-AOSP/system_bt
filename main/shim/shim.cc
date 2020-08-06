/*
 * Copyright 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "bt_shim"

#include "main/shim/shim.h"
#include "main/shim/entry.h"
#include "main/shim/stack.h"

#include "gd/common/init_flags.h"
#include "gd/os/log.h"

future_t* IdleModuleStartUp() {
  bluetooth::shim::Stack::GetInstance()->StartIdleMode();
  return kReturnImmediate;
}

future_t* ShimModuleStartUp() {
  bluetooth::shim::Stack::GetInstance()->StartEverything();
  return kReturnImmediate;
}

future_t* GeneralShutDown() {
  bluetooth::shim::Stack::GetInstance()->Stop();
  return kReturnImmediate;
}

EXPORT_SYMBOL extern const module_t gd_idle_module = {
    .name = GD_IDLE_MODULE,
    .init = kUnusedModuleApi,
    .start_up = IdleModuleStartUp,
    .shut_down = GeneralShutDown,
    .clean_up = kUnusedModuleApi,
    .dependencies = {kUnusedModuleDependencies}};

EXPORT_SYMBOL extern const module_t gd_shim_module = {
    .name = GD_SHIM_MODULE,
    .init = kUnusedModuleApi,
    .start_up = ShimModuleStartUp,
    .shut_down = GeneralShutDown,
    .clean_up = kUnusedModuleApi,
    .dependencies = {kUnusedModuleDependencies}};

bool bluetooth::shim::is_gd_hci_enabled() {
  return bluetooth::common::InitFlags::GdHciEnabled();
}

bool bluetooth::shim::is_gd_shim_enabled() {
  return bluetooth::common::InitFlags::GdCoreEnabled();
}

bool bluetooth::shim::is_any_gd_enabled() {
  return bluetooth::common::InitFlags::GdHciEnabled();
}

bool bluetooth::shim::is_gd_stack_started_up() {
  return bluetooth::shim::Stack::GetInstance()->IsRunning();
}
