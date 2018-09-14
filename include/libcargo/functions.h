// MIT License
//
// Copyright (c) 2018 the Cargo authors
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#ifndef CARGO_INCLUDE_LIBCARGO_FUNCTIONS_H_
#define CARGO_INCLUDE_LIBCARGO_FUNCTIONS_H_
#include <memory> /* shared_ptr */

#include "cargo.h"
#include "classes.h"
#include "dbsql.h"
#include "types.h"

#include "../gtree/gtree.h"
#include "../sqlite3/sqlite3.h"

namespace cargo {

/* Print ---------------------------------------------------------------------*/
void print_rte(const vec_t<Wayp> &);
void print_sch(const vec_t<Stop> &);


/* Random customer -----------------------------------------------------------*/
CustId randcust(const vec_t<Stop> &);


/* Pickup range --------------------------------------------------------------*/
DistInt pickup_range(const Customer &, const SimlTime &);


/* Route operations ----------------------------------------------------------*/
DistInt route_through(  // use specific g-tree
  const vec_t<Stop> &,
        vec_t<Wayp> &,
        GTree::G_Tree &
);
DistInt route_through(  // use global g-tree
  const vec_t<Stop> &,
        vec_t<Wayp> &
);
bool chkpc(const Schedule &);
bool chktw(const vec_t<Stop> &, const vec_t<Wayp> &);


/* Schedule operations -------------------------------------------------------*/
void opdel(vec_t<Stop> &, const CustId &);

// TODO: Having all of these is horrible. Clean this up.
DistInt sop_insert(
  const vec_t<Stop> &,
  const Stop &,
  const Stop &,
        bool,
        bool,
        vec_t<Stop> &,
        vec_t<Wayp> &,
        GTree::G_Tree &
);
DistInt sop_insert(
  const vec_t<Stop> &,
  const Stop &,
  const Stop &,
        bool,
        bool,
        vec_t<Stop> &,
        vec_t<Wayp> &
);
DistInt sop_insert(
  const Vehicle &,
  const Customer &,
        vec_t<Stop> &,
        vec_t<Wayp> &,
        GTree::G_Tree &
);
DistInt sop_insert(
  const Vehicle &,
  const Customer &,
        vec_t<Stop> &,
        vec_t<Wayp> &
);
DistInt sop_insert(
  const std::shared_ptr<MutableVehicle> &,
  const Customer &,
        vec_t<Stop> &,
        vec_t<Wayp> &
);
DistInt sop_replace(
  const std::shared_ptr<MutableVehicle> &,
  const CustId &,
  const Customer &,
        vec_t<Stop> &,
        vec_t<Wayp> &
);

}  // namespace cargo

#endif  // CARGO_INCLUDE_LIBCARGO_FUNCTIONS_H_

