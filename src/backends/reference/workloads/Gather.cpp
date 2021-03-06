//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#include "Gather.hpp"

#include "RefWorkloadUtils.hpp"

#include <backendsCommon/WorkloadData.hpp>

#include <boost/numeric/conversion/cast.hpp>

namespace armnn
{

void Gather(const TensorInfo& paramsInfo,
            const TensorInfo& indicesInfo,
            const TensorInfo& outputInfo,
            Decoder<float>& params,
            const int32_t* indices,
            Encoder<float>& output)
{
    const TensorShape& paramsShape = paramsInfo.GetShape();

    unsigned int paramsProduct = 1;
    for (unsigned int i = 1; i < paramsInfo.GetNumDimensions(); ++i)
    {
        paramsProduct = paramsProduct * paramsShape[i];
    }

    unsigned int outIndex = 0;
    for (unsigned int i = 0; i < indicesInfo.GetNumElements(); ++i)
    {
        unsigned int indx = boost::numeric_cast<unsigned int>(indices[i]);

        BOOST_ASSERT(indices[i] >= 0 && indx < paramsShape[0]);

        unsigned int startOffset = indx * paramsProduct;
        unsigned int endOffset = startOffset + paramsProduct;

        for (unsigned int j = startOffset; j < endOffset; ++j)
        {
            params[j];
            float outputValue = params.Get();
            output[outIndex];
            output.Set(outputValue);
            ++outIndex;
        }
    }

    BOOST_ASSERT(outIndex == outputInfo.GetNumElements());
}

} //namespace armnn
