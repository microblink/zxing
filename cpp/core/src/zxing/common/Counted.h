
// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-
#pragma once

/*
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

//#define DEBUG_COUNTING

#include <boost/config.hpp>
#include <boost/assert.hpp>

#include <Utils/disable_warnings.hpp>

#include <atomic>
#include <cstdint>
#include <limits>
#include <string>

MB_DISABLE_WARNING_PUSH
MB_DISABLE_WARNING_GCC( "-Wnonnull" )
namespace pping {

/* base class for reference-counted objects */
// The count is atomic: shared objects such as the Galois fields and their polynomials are
// referenced from every thread that decodes at the same time.
class Counted {
private:
  std::atomic<std::uint_fast16_t> references_;
  template< typename T > friend void intrusive_ptr_add_ref( T* ) noexcept;
  template< typename T > friend void intrusive_ptr_release( T* ) noexcept;
protected:
    virtual ~Counted() noexcept = default;
public:
  Counted() noexcept :
      references_(0) {
#ifdef DEBUG_COUNTING
    cout << "instantiating " << typeid(*this).name() << " " << this <<
         " @ " << count_ << "\n";
#endif
  }
  Counted(const Counted&) noexcept :
      references_(0) {
  }
  Counted& operator=(const Counted& other) noexcept {
      if (this != &other) {
          // don't change count
      }
      return *this;
  }
  Counted *retain() noexcept {
#ifdef DEBUG_COUNTING
    cout << "retaining " << typeid(*this).name() << " " << this <<
         " @ " << count_;
#endif
    [[maybe_unused]] auto const previous = references_.fetch_add( 1, std::memory_order_relaxed );
    BOOST_ASSERT( previous < std::numeric_limits<std::uint_fast16_t>::max() );
#ifdef DEBUG_COUNTING
    cout << "->" << count_ << "\n";
#endif
    return this;
  }
  void release() noexcept {
#ifdef DEBUG_COUNTING
    cout << "releasing " << typeid(*this).name() << " " << this <<
         " @ " << count_;
#endif
    auto const previous = references_.fetch_sub( 1, std::memory_order_acq_rel );
    BOOST_ASSERT_MSG( previous != 0, "Overreleasing already-deleted object" );
    if ( BOOST_UNLIKELY( previous == 1 ) ) {
#ifdef DEBUG_COUNTING
      cout << "deleting " << typeid(*this).name() << " " << this << "\n";
#endif
      delete this;
    }
  }


  /* return the current count for denugging purposes or similar */
  int count() const noexcept {
    return references_.load( std::memory_order_relaxed );
  }
};

template< typename T >
void intrusive_ptr_add_ref( T* x ) noexcept {
    [[maybe_unused]] auto const previous = x->references_.fetch_add( 1, std::memory_order_relaxed );
    BOOST_ASSERT( previous < std::numeric_limits<std::uint_fast16_t>::max() );
}

template< typename T >
void intrusive_ptr_release( T* x ) noexcept {
    if ( BOOST_UNLIKELY( x->references_.fetch_sub( 1, std::memory_order_acq_rel ) == 1 ) ) delete x;
}

/* counting reference to reference-counted objects */
template<typename T> class Ref {
private:
public:
  T *object_;
  explicit Ref(T *o = 0) noexcept :
      object_(0) {
#ifdef DEBUG_COUNTING
    cout << "instantiating Ref " << this << " from pointer" << o << "\n";
#endif
    reset(o);
  }

  explicit Ref(const T &o) noexcept :
      object_(0) {
#ifdef DEBUG_COUNTING
    cout << "instantiating Ref " << this << " from reference\n";
#endif
    reset(const_cast<T *>(&o));
  }

  Ref(const Ref &other) noexcept :
      object_(0) {
#ifdef DEBUG_COUNTING
    cout << "instantiating Ref " << this << " from Ref " << &other << "\n";
#endif
    reset(other.object_);
  }

  template<class Y>
  Ref(const Ref<Y> &other) noexcept :
      object_(0) {
#ifdef DEBUG_COUNTING
    cout << "instantiating Ref " << this << " from reference\n";
#endif
    reset(other.object_);
  }

  ~Ref() noexcept {
#ifdef DEBUG_COUNTING
    cout << "destroying Ref " << this << " with " <<
         (object_ ? typeid(*object_).name() : "NULL") << " " << object_ << "\n";
#endif
    if (object_) {
      object_->release();
    }
  }

  void reset(T *o) noexcept {
#ifdef DEBUG_COUNTING
    cout << "resetting Ref " << this << " from " <<
         (object_ ? typeid(*object_).name() : "NULL") << " " << object_ <<
         " to " << (o ? typeid(*o).name() : "NULL") << " " << o << "\n";
#endif
    if (o) {
      o->retain();
    }
    if (object_ != 0) {
      object_->release();
    }
    object_ = o;
  }
  Ref& operator=(const Ref &other) noexcept {
    reset(other.object_);
    return *this;
  }
  template<class Y>
  Ref& operator=(const Ref<Y> &other) noexcept {
    reset(other.object_);
    return *this;
  }
  Ref& operator=(T* o) noexcept {
    reset(o);
    return *this;
  }
  template<class Y>
  Ref& operator=(Y* o) noexcept {
    reset(o);
    return *this;
  }

  T& operator*() noexcept {
    return *object_;
  }
  T* operator->() const noexcept {
    return object_;
  }
  operator T*() const noexcept {
    return object_;
  }

  bool operator==(const T* that) noexcept {
    return object_ == that;
  }
  bool operator==(const Ref &other) const noexcept {
    return object_ == other.object_ || *object_ == *(other.object_);
  }
  template<class Y>
  bool operator==(const Ref<Y> &other) const noexcept {
    return object_ == other.object_ || *object_ == *(other.object_);
  }

  bool operator!=(const T* that) noexcept {
    return !(*this == that);
  }

  bool empty() const noexcept {
    return object_ == 0;
  }
};
}

MB_DISABLE_WARNING_POP
