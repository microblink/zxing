// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-
/*
 *  AztecReader.h
 *  zxing
 *
 *  Created by Lukas Stabe on 08/02/2012.
 *  Copyright 2012 ZXing authors All rights reserved.
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

#include <zxing/DecodeHints.h>            // for DecodeHints
#include <zxing/Reader.h>                 // for Reader
#include <zxing/aztec/decoder/Decoder.h>  // for Decoder

#include "zxing/common/Counted.h"         // for Ref
#include "zxing/common/Error.hpp"

namespace pping {
class BinaryBitmap;
class Result;
}  // namespace pping

#pragma once

namespace pping {
    namespace aztec {
        
        class AztecReader : public Reader {
        private:
            Decoder decoder_;
            
        protected:
            Decoder &getDecoder();
            
        public:
            AztecReader();
            virtual FallibleRef<Result> decode(Ref<BinaryBitmap> image) MB_NOEXCEPT_EXCEPT_BADALLOC override;
            virtual FallibleRef<Result> decode(Ref<BinaryBitmap> image, DecodeHints hints) MB_NOEXCEPT_EXCEPT_BADALLOC override;
            virtual ~AztecReader();
        };
        
    }
}

