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
#ifndef HIVIEW_BASE_EVENT_DISPATCH_QUEUE_IMPL_H
#define HIVIEW_BASE_EVENT_DISPATCH_QUEUE_IMPL_H
#include <condition_variable>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include "event.h"
namespace OHOS {
namespace HiviewDFX {
class EventDispatchQueue {
public:
    EventDispatchQueue(const std::string& name, Event::ManageType type);
    ~EventDispatchQueue();

    void Stop();
    void Start();
    void Enqueue(std::shared_ptr<Event> event);
    void RegisterListener(std::weak_ptr<EventListener> listener);
    int GetWaitQueueSize() const;
    bool IsRunning() const
    {
        return isRunning_;
    }

private:
    void Run();
    void ProcessOrderedEvent(Event &event);
    void ProcessUnorderedEvent(const Event &event);
    bool IsEventMatchCurrentListener(const Event& event, std::shared_ptr<EventListener> listener);

    volatile bool stop_;
    bool isRunning_ = false;
    std::string threadName_;
    Event::ManageType type_;
    mutable std::mutex mutexLock_;
    std::condition_variable condition_;
    std::list<std::shared_ptr<Event>> pendingEvents_;
    std::list<std::weak_ptr<EventListener>> listeners_;
    std::unique_ptr<std::thread> thread_;
};
} // namespace HiviewDFX
} // namespace OHOS
#endif // HIVIEW_BASE_EVENT_DISPATCH_QUEUE_IMPL_H