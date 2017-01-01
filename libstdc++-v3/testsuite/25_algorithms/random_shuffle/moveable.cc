// { dg-do run { target c++11 } }

// Copyright (C) 2009-2017 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

// 25.2.11 random_shuffle()

// XXX FIXME:  parallel-mode should deal correctly with moveable-only types
// per C++0x, at minimum smoothly fall back to serial.
#undef _GLIBCXX_PARALLEL

#include <algorithm>
#include <testsuite_hooks.h>
#include <testsuite_iterators.h>
#include <testsuite_rvalref.h>

using __gnu_test::test_container;
using __gnu_test::random_access_iterator_wrapper;
using __gnu_test::rvalstruct;

typedef test_container<rvalstruct, random_access_iterator_wrapper> Container;

const unsigned int N = 10000;
int A[N]; // This is made global because we don't want it on the stack

void fill_ascending()
{
  for (int i = 0; i < N; ++i)
    A[i] = i;
}

void
test01()
{
  fill_ascending();
  rvalstruct rv[N];
  std::copy(A, A + N, rv);
  Container con(rv, rv + N);
  std::random_shuffle(con.begin(), con.end());

  // The chance that random_shuffle leaves the order as is by coincidence
  // is negligible, so we expect it to be permuted
  VERIFY( !std::equal(rv, rv + N, A) );

  std::sort(con.begin(), con.end());
  VERIFY( std::equal(rv, rv + N, A) );
}

int random_generator(int)
{ return 0; }

void
test02()
{
  rvalstruct rv[10] = {1,2,3,4,5,6,7,8,9,10};
  int result[10] = {10,1,2,3,4,5,6,7,8,9};
  Container con(rv, rv + 10);
  std::random_shuffle(con.begin(), con.end(), random_generator);
  // The above answer was generated by hand. It is not required by the standard,
  // but is produced by the current algorithm.
  VERIFY( std::equal(rv, rv + 10, result) );
}

int
main()
{
  test01();
  test02();
  return 0;
}
