/*
 *
 *  Copyright 2010 ZXing authors All rights reserved.
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

#include <float.h>                                           // for FLT_MAX
#include <math.h>                                            // for fabsf, sqrt
#include <algorithm>                                         // for max
#include <vector>                                            // for vector, allocator

#include "FinderPatternAnalizator.hpp"
#include "zxing/common/Counted.h"                            // for Ref
#include "zxing/qrcode/detector/ZXingQRCodeFinderPattern.h"  // for FinderPattern

namespace pping {

namespace qrcode {

ZXingFinderPatternVector::ZXingFinderPatternVector(const Ref<FinderPattern> from, const Ref<FinderPattern> to) :
        x_(to->getX() - from->getX()), y_(to->getY() - from->getY()){
    norm_ = (float)sqrt(x_ * x_ + y_ * y_);
}

ZXingFinderPatternVector::~ZXingFinderPatternVector(){
    // nothing to do
}

float ZXingFinderPatternVector::getNorm(){
    return norm_;
}

float ZXingFinderPatternVector::getCosinusAngle(const ZXingFinderPatternVector& other) const {
    float scalarProduct = x_ * other.x_ + y_ * other.y_;
    scalarProduct = scalarProduct/(norm_ * other.norm_);
    return scalarProduct;
}

FinderPatternAnalizator::FinderPatternAnalizator(){
    // nothing to do
}

FinderPatternAnalizator::~FinderPatternAnalizator(){
    // nothing to do
}

float FinderPatternAnalizator::analize(const Ref<FinderPattern> first, const Ref<FinderPattern> second, const Ref<FinderPattern> third){
    std::vector<ZXingFinderPatternVector> triangle;
    triangle.push_back(ZXingFinderPatternVector(first, second));
    triangle.push_back(ZXingFinderPatternVector(second, third));
    triangle.push_back(ZXingFinderPatternVector(third, first));

    float error = FLT_MAX;
    for (int i = 0; i < (int) triangle.size(); ++i){

        float angleError = fabsf(triangle[i].getCosinusAngle(triangle[(i+1)%3]));

        float n1 = triangle[i].getNorm();
        float n2 = triangle[(i + 1) % 3].getNorm();
        float lengthError = fabsf(n1 - n2)/std::max(n1, n2);

        float currError = angleError + lengthError;

        if (currError < error){
            error = currError;
        }
    }

    return error;
}

} /* namespace qrcode */

} /* namespace pping */
