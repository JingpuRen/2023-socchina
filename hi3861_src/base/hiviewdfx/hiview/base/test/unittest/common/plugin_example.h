/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef HIVIEW_PLATFORM_PLUGIN_FACTORY_TEST_PLUGIN_EXAMPLE_H
#define HIVIEW_PLATFORM_PLUGIN_FACTORY_TEST_PLUGIN_EXAMPLE_H
#include "defines.h"
#include "pipeline.h"
#include "plugin.h"

namespace OHOS {
namespace HiviewDFX {
class PluginExampleEvent : public PipelineEvent {
public:
    PluginExampleEvent(const std::string& sender, PipelineEventProducer* handler)
        : PipelineEvent(sender, handler){};

    ~PluginExampleEvent(){};
};
class PluginExample : public Plugin {
public:
    PluginExample() : isConstructed_(true) {};
    virtual ~PluginExample() {};
    bool OnEvent(std::shared_ptr<Event>& event) override;
    void OnLoad() override;
    void OnUnload() override {};
    bool isConstructed_ = false;
};

__UNUSED static std::shared_ptr<Plugin> CreatePluginExampleInstance()
{
    return std::make_shared<PluginExample>();
}
} // namespace HiviewDFX
} // namespace OHOS
#endif // HIVIEW_PLATFORM_PLUGIN_FACTORY_TEST_PLUGIN_EXAMPLE_H