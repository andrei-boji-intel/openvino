// Copyright (C) 2018-2023 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include <gtest/gtest.h>

#include "openvino/op/greater.hpp"
#include "comparison.hpp"

using namespace ov;
using ComparisonTypes = ngraph::helpers::ComparisonTypes;

namespace reference_tests {
namespace ComparisonOpsRefTestDefinitions {
namespace {
TEST_P(ReferenceComparisonLayerTest, GreaterCompareWithHardcodedRefs) {
    Exec();
}

template <element::Type_t IN_ET>
std::vector<RefComparisonParams> generateComparisonParams(const element::Type& type) {
    using T = typename element_type_traits<IN_ET>::value_type;
    std::vector<RefComparisonParams> compParams {
        // 1D // 2D // 3D // 4D
        Builder {}
            .compType(ComparisonTypes::GREATER)
            .input1({{2, 2}, type, std::vector<T> {0, 12, 23, 0}})
            .input2({{2, 2}, type, std::vector<T> {0, 12, 23, 0}})
            .expected({{2, 2}, element::boolean, std::vector<char> {0, 0, 0, 0}}),
        Builder {}
            .compType(ComparisonTypes::GREATER)
            .input1({{2, 3}, type, std::vector<T> {0, 6, 45, 1, 21, 21}})
            .input2({{2, 3}, type, std::vector<T> {1, 18, 23, 1, 19, 21}})
            .expected({{2, 3}, element::boolean, std::vector<char> {0, 0, 1, 0, 1, 0}}),
        Builder {}
            .compType(ComparisonTypes::GREATER)
            .input1({{1}, type, std::vector<T> {53}})
            .input2({{1}, type, std::vector<T> {53}})
            .expected({{1}, element::boolean, std::vector<char> {0}}),
        Builder {}
            .compType(ComparisonTypes::GREATER)
            .input1({{2, 4}, type, std::vector<T> {0, 12, 23, 0, 1, 5, 12, 8}})
            .input2({{2, 4}, type, std::vector<T> {0, 12, 23, 0, 10, 5, 11, 8}})
            .expected({{2, 4}, element::boolean, std::vector<char> {0, 0, 0, 0, 0, 0, 1, 0}}),
        Builder {}
            .compType(ComparisonTypes::GREATER)
            .input1({{3, 1, 2}, type, std::vector<T> {2, 1, 4, 1, 3, 1}})
            .input2({{1, 2, 1}, type, std::vector<T> {1, 1}})
            .expected({{3, 2, 2}, element::boolean, std::vector<char> {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}}),
        Builder {}
            .compType(ComparisonTypes::GREATER)
            .input1({{2, 1, 2, 1}, type, std::vector<T> {2, 1, 4, 1}})
            .input2({{1, 2, 1}, type, std::vector<T> {1, 1}})
            .expected({{2, 1, 2, 1}, element::boolean, std::vector<char> {1, 0, 1, 0}})};
    return compParams;
}

std::vector<RefComparisonParams> generateComparisonCombinedParams() {
    const std::vector<std::vector<RefComparisonParams>> compTypeParams {
        generateComparisonParams<element::Type_t::f32>(element::f32),
        generateComparisonParams<element::Type_t::f16>(element::f16),
        generateComparisonParams<element::Type_t::i32>(element::i32),
        generateComparisonParams<element::Type_t::i64>(element::i64),
        generateComparisonParams<element::Type_t::u32>(element::u32),
        generateComparisonParams<element::Type_t::u64>(element::u64),
        generateComparisonParams<element::Type_t::boolean>(element::boolean)};
    std::vector<RefComparisonParams> combinedParams;

    for (const auto& params : compTypeParams) {
        combinedParams.insert(combinedParams.end(), params.begin(), params.end());
    }
    return combinedParams;
}

} // namespace
INSTANTIATE_TEST_SUITE_P(smoke_Comparison_With_Hardcoded_Refs, ReferenceComparisonLayerTest, ::testing::ValuesIn(generateComparisonCombinedParams()),
                         ReferenceComparisonLayerTest::getTestCaseName);
} // namespace ComparisonOpsRefTestDefinitions
} // namespace reference_tests
