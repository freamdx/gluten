/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <Core/Block.h>
#include <Parser/ExpandField.h>
#include <Processors/QueryPlan/IQueryPlanStep.h>
#include <Processors/QueryPlan/ITransformingStep.h>

namespace local_engine
{
class ExpandStep : public DB::ITransformingStep
{
public:
    // The input stream should only contain grouping columns.
    explicit ExpandStep(const DB::SharedHeader & input_header, const ExpandField & project_set_exprs_);
    ~ExpandStep() override = default;

    String getName() const override { return "ExpandStep"; }

    void transformPipeline(DB::QueryPipelineBuilder & pipeline, const DB::BuildQueryPipelineSettings & settings) override;
    void describePipeline(DB::IQueryPlanStep::FormatSettings & settings) const override;

protected:
    ExpandField project_set_exprs;

    void updateOutputHeader() override;

    static DB::Block buildOutputHeader(const DB::Block & header, const ExpandField & project_set_exprs_);
};
}
