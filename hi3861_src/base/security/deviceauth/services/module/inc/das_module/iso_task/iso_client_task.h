/*
 * Copyright (C) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ISO_CLIENT_TASK_H
#define ISO_CLIENT_TASK_H

#include "base_sub_task.h"
#include "iso_base_cur_task.h"

typedef struct {
    SubTaskBase taskBase;
    IsoParams params;
    SymBaseCurTask *curTask;
} IsoClientTask;

SubTaskBase *CreateIsoClientTask(const CJson *in);

#endif
