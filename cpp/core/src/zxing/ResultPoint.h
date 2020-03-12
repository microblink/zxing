// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-
#pragma once

/*
 *  ResultPoint.h
 *  zxing
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

#include <zxing/common/Counted.h>  // for Counted
#include <vector>                  // for vector

namespace pping {

class ResultPoint : public Counted {
protected:
  float posX_;
  float posY_;
  
public:
  ResultPoint();
  ResultPoint(float x, float y);
  virtual ~ResultPoint();

  virtual float getX() const;
  virtual float getY() const;

  bool equals(Ref<ResultPoint> other);

  static void orderBestPatterns(std::vector<Ref<ResultPoint> > &patterns);
  static float distance(Ref<ResultPoint> point1, Ref<ResultPoint> point2);
  static float distance(float x1, float x2, float y1, float y2);

private:
  static float crossProductZ(Ref<ResultPoint> pointA, Ref<ResultPoint> pointB, Ref<ResultPoint> pointC);
};

}

