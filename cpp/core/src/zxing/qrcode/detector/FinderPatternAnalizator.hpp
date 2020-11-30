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

#pragma once

namespace pping {
template <typename T> class Ref;
}  // namespace pping

namespace pping {

namespace qrcode {

class FinderPattern;

class ZXingFinderPatternVector{
public:
    ZXingFinderPatternVector(const Ref<FinderPattern> from, const Ref<FinderPattern> to);

    ~ZXingFinderPatternVector();

    float getNorm();

    float getCosinusAngle(const ZXingFinderPatternVector &other) const;

private:
    float x_;

    float y_;

    float norm_;
};

class FinderPatternAnalizator {
public:
    FinderPatternAnalizator();

    ~FinderPatternAnalizator();

    static float analize(const Ref<FinderPattern> first, const Ref<FinderPattern> second, const Ref<FinderPattern> third);
};

} /* namespace qrcode */

} /* namespace pping */
