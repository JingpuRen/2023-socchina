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
#ifndef HIVIEW_PLUGIN_EXAMPLES_EVENT_PROCESSOR_EXAMPLE3
#define HIVIEW_PLUGIN_EXAMPLES_EVENT_PROCESSOR_EXAMPLE3
#include "event_source_example.h"
#include "plugin.h"

namespace OHOS {
namespace HiviewDFX {
class EventProcessorExample3Event : public EventSourceExampleEvent {
public:
    EventProcessorExample3Event(const std::string& sender, PipelineEventProducer* handler)
        : EventSourceExampleEvent(sender, handler), exampleAddon_("EventProcessorExample3AddOn"){};
    explicit EventProcessorExample3Event(const EventSourceExampleEvent& obj) : EventSourceExampleEvent(obj){};
    ~EventProcessorExample3Event(){};
    std::string exampleAddon_;
};

class EventProcessorExample3 : public Plugin {
public:
    bool CanProcessEvent(std::shared_ptr<Event> event) override;
    bool OnEvent(std::shared_ptr<Event>& event) override;
    void OnLoad() override;
    void OnUnload() override;
};
} // namespace HiviewDFX
} // namespace OHOS
#endif // HIVIEW_PLUGIN_EXAMPLES_EVENT_PROCESSOR_EXAMPLE3