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
#include <memory>
#include <unordered_map>
#include <random>

#include "libcargo.h"

using namespace cargo;

class GRASP : public RSAlgorithm {
 public:
  GRASP();

  /* My overrides */
  virtual void handle_vehicle(const Vehicle &);
  virtual void match();
  virtual void end();
  virtual void listen(bool skip_assigned = true, bool skip_delayed = true);

 private:
  Grid grid_;

  std::mt19937 gen;
  std::uniform_real_distribution<> d;

  /* Workspace variables */
  std::vector<Stop> sch;
  std::vector<Wayp> rte;
  std::vector<MutableVehicleSptr> candidates;
  tick_t timeout_0;

  DistInt best_solcst;
  dict<CustId, bool> is_matched;
  dict<MutableVehicleSptr, vec_t<Customer>> candidates_list;
  dict<Customer, vec_t<MutableVehicleSptr>> candidates_list_by_cust;

  std::vector<std::tuple<Customer, MutableVehicle, DistInt>> best_sol;
  std::unordered_map<VehlId, std::vector<Customer>> commit_cadd;
  std::unordered_map<VehlId, std::vector<Wayp>> commit_rte;
  std::unordered_map<VehlId, std::vector<Stop>> commit_sch;

  void initialize_by_vehl(dict<MutableVehicleSptr, vec_t<Customer>> &, vec_t<CustId> &);
  void initialize_by_cust(dict<MutableVehicleSptr, vec_t<Customer>> &, vec_t<CustId> &);

  MutableVehicleSptr replace(
    const dict<MutableVehicleSptr, vec_t<Customer>> &,  // solution
    const vec_t<Customer> &,  // unassigned
    DistInt &,                // amount of improvement
    vec_t<Stop> &,            // schedule after replace
    vec_t<Wayp> &,            // route after replace
    CustId &,                 // replaced customer (previously assigned)
    CustId &);                // replace by

  std::pair<MutableVehicleSptr, MutableVehicleSptr> swap(
    const dict<MutableVehicleSptr, vec_t<Customer>> &,  // solution
    DistInt &,                // amount of improvement
    vec_t<Stop> &,            // schedule1 after swap
    vec_t<Wayp> &,            // route1 after swap
    vec_t<Stop> &,            // schedule2 after swap
    vec_t<Wayp> &,            // route2 after swap
    CustId &,                 // swapped to 1
    CustId &);                // swapped to 2

  DistInt max_rank(const vec_t<std::pair<DistInt, Customer>> &);
  DistInt max_rank(const vec_t<std::pair<DistInt, MutableVehicleSptr>> &);

  void reset_workspace();
};

