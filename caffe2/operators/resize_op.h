/**
 * Copyright (c) 2016-present, Facebook, Inc.
 *
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


#pragma once

#include "caffe2/core/context.h"
#include "caffe2/core/operator.h"

namespace caffe2 {

template <typename T, class Context>
class ResizeNearestOp final : public Operator<Context> {
 public:
  ResizeNearestOp(const OperatorDef& operator_def, Workspace* ws)
      : Operator<Context>(operator_def, ws), width_scale_(1), height_scale_(1) {
    if (HasArgument("width_scale")) {
      width_scale_ = static_cast<T>(
          OperatorBase::GetSingleArgument<float>("width_scale", 1));
    }
    if (HasArgument("height_scale")) {
      height_scale_ = static_cast<T>(
          OperatorBase::GetSingleArgument<float>("height_scale", 1));
    }
    CAFFE_ENFORCE_GT(width_scale_, 0);
    CAFFE_ENFORCE_GT(height_scale_, 0);
  }
  USE_OPERATOR_CONTEXT_FUNCTIONS;

  bool RunOnDevice() override;

 protected:
  T width_scale_;
  T height_scale_;
};

template <typename T, class Context>
class ResizeNearestGradientOp final : public Operator<Context> {
 public:
  ResizeNearestGradientOp(const OperatorDef& operator_def, Workspace* ws)
      : Operator<Context>(operator_def, ws), width_scale_(1), height_scale_(1) {
    width_scale_ = static_cast<T>(
        OperatorBase::GetSingleArgument<float>("width_scale", 1));
    height_scale_ = static_cast<T>(
        OperatorBase::GetSingleArgument<float>("height_scale", 1));
    CAFFE_ENFORCE_GT(width_scale_, 0);
    CAFFE_ENFORCE_GT(height_scale_, 0);
  }
  USE_OPERATOR_CONTEXT_FUNCTIONS;

  bool RunOnDevice() override;

 protected:
  T width_scale_;
  T height_scale_;
};

} // namespace caffe2
