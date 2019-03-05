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

#pragma once

#include <binder/IInterface.h>
#include <cutils/compiler.h>
#include <graphicsenv/GraphicsEnv.h>

#include <vector>

namespace android {

/*
 * This class defines the Binder IPC interface for GPU-related queries and
 * control.
 */
class IGpuService : public IInterface {
public:
    DECLARE_META_INTERFACE(GpuService)

    // set GPU stats from GraphicsEnvironment.
    virtual void setGpuStats(const std::string& driverPackageName,
                             const std::string& driverVersionName, uint64_t driverVersionCode,
                             const std::string& driverBuildDate, const std::string& appPackageName,
                             GraphicsEnv::Driver driver, bool isDriverLoaded,
                             int64_t driverLoadingTime) = 0;
};

class BnGpuService : public BnInterface<IGpuService> {
public:
    enum IGpuServiceTag {
        SET_GPU_STATS = IBinder::FIRST_CALL_TRANSACTION,
        // Always append new enum to the end.
    };

    status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply,
                        uint32_t flags = 0) override;

protected:
    virtual status_t shellCommand(int in, int out, int err, std::vector<String16>& args) = 0;
};

} // namespace android
