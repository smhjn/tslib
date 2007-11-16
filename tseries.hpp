#ifndef TSERIES_HPP
#define TSERIES_HPP

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>
#include "tseries.data.hpp"
#include "utils/rangeSpecifier.hpp"
#include "utils/copyVector.hpp"
#include "utils/ts.ts.opp.hpp"
#include "utils/ts.scalar.opp.hpp"
using namespace std;

// pre-declare template friends
template<typename TDATE, typename TDATA> class TSeries;
template<typename TDATE, typename TDATA> TSeries<TDATE,TDATA> operator+(const TSeries<TDATE,TDATA>& lhs, const TSeries<TDATE,TDATA>& rhs);
template<typename TDATE, typename TDATA> TSeries<TDATE,TDATA> operator-(const TSeries<TDATE,TDATA>& lhs, const TSeries<TDATE,TDATA>& rhs);
template<typename TDATE, typename TDATA> TSeries<TDATE,TDATA> operator*(const TSeries<TDATE,TDATA>& lhs, const TSeries<TDATE,TDATA>& rhs);
template<typename TDATE, typename TDATA> TSeries<TDATE,TDATA> operator/(const TSeries<TDATE,TDATA>& lhs, const TSeries<TDATE,TDATA>& rhs);

template<typename TDATE, typename TDATA> TSeries<TDATE,TDATA> operator+(const TDATA lhs, const TSeries<TDATE,TDATA>& rhs);
template<typename TDATE, typename TDATA> TSeries<TDATE,TDATA> operator-(const TDATA lhs, const TSeries<TDATE,TDATA>& rhs);
template<typename TDATE, typename TDATA> TSeries<TDATE,TDATA> operator*(const TDATA lhs, const TSeries<TDATE,TDATA>& rhs);
template<typename TDATE, typename TDATA> TSeries<TDATE,TDATA> operator/(const TDATA lhs, const TSeries<TDATE,TDATA>& rhs);

template<typename TDATE, typename TDATA> TSeries<TDATE,TDATA> operator+(const TSeries<TDATE,TDATA>& lhs, const TDATA rhs);
template<typename TDATE, typename TDATA> TSeries<TDATE,TDATA> operator-(const TSeries<TDATE,TDATA>& lhs, const TDATA rhs);
template<typename TDATE, typename TDATA> TSeries<TDATE,TDATA> operator*(const TSeries<TDATE,TDATA>& lhs, const TDATA rhs);
template<typename TDATE, typename TDATA> TSeries<TDATE,TDATA> operator/(const TSeries<TDATE,TDATA>& lhs, const TDATA rhs);


template<typename TDATE, typename TDATA> std::ostream& operator<<(std::ostream& os, const TSeries<TDATE,TDATA>& ts);

template <typename TDATE,typename TDATA>
class TSeries {
private:
  TSdata<TDATE,TDATA>* tsdata_;

public:
  ~TSeries();
  TSeries();
  TSeries(const TSDIM rows, const TSDIM cols);
  TSeries(const TSeries& T);

  TSeries<TDATE,TDATA> copy() const;

  // accessors
  vector<string> getColnames() const;
  const TSDIM nrow() const;
  const TSDIM ncol() const;
  TDATA* getData() const;
  TDATE* getDates() const;

  // mutators
  int setColnames(const vector<string>& cnames);

  //operators
  friend TSeries<TDATE,TDATA> operator+ <> (const TSeries<TDATE,TDATA>& lhs, const TSeries<TDATE,TDATA>& rhs);
  friend TSeries<TDATE,TDATA> operator- <> (const TSeries<TDATE,TDATA>& lhs, const TSeries<TDATE,TDATA>& rhs);
  friend TSeries<TDATE,TDATA> operator* <> (const TSeries<TDATE,TDATA>& lhs, const TSeries<TDATE,TDATA>& rhs);
  friend TSeries<TDATE,TDATA> operator/ <> (const TSeries<TDATE,TDATA>& lhs, const TSeries<TDATE,TDATA>& rhs);

  friend TSeries<TDATE,TDATA> operator+ <> (const TDATA lhs, const TSeries<TDATE,TDATA>& rhs);
  friend TSeries<TDATE,TDATA> operator- <> (const TDATA lhs, const TSeries<TDATE,TDATA>& rhs);
  friend TSeries<TDATE,TDATA> operator* <> (const TDATA lhs, const TSeries<TDATE,TDATA>& rhs);
  friend TSeries<TDATE,TDATA> operator/ <> (const TDATA lhs, const TSeries<TDATE,TDATA>& rhs);

  friend TSeries<TDATE,TDATA> operator+ <> (const TSeries<TDATE,TDATA>& lhs, const TDATA rhs);
  friend TSeries<TDATE,TDATA> operator- <> (const TSeries<TDATE,TDATA>& lhs, const TDATA rhs);
  friend TSeries<TDATE,TDATA> operator* <> (const TSeries<TDATE,TDATA>& lhs, const TDATA rhs);
  friend TSeries<TDATE,TDATA> operator/ <> (const TSeries<TDATE,TDATA>& lhs, const TDATA rhs);


  friend std::ostream& operator<< <> (std::ostream& os, const TSeries<TDATE,TDATA>& ts);
};

template <typename TDATE, typename TDATA>
TSeries<TDATE,TDATA> operator+(const TSeries<TDATE,TDATA>& lhs, const TSeries<TDATE,TDATA>& rhs) {
  return apply_opp(lhs,rhs,plus<TDATA>());
}

template <typename TDATE, typename TDATA>
TSeries<TDATE,TDATA> operator-(const TSeries<TDATE,TDATA>& lhs, const TSeries<TDATE,TDATA>& rhs) {
  return apply_opp(lhs,rhs,minus<TDATA>());
}

template <typename TDATE, typename TDATA>
TSeries<TDATE,TDATA> operator*(const TSeries<TDATE,TDATA>& lhs, const TSeries<TDATE,TDATA>& rhs) {
  return apply_opp(lhs,rhs,multiplies<TDATA>());
}

template <typename TDATE, typename TDATA>
TSeries<TDATE,TDATA> operator/(const TSeries<TDATE,TDATA>& lhs, const TSeries<TDATE,TDATA>& rhs) {
  return apply_opp(lhs,rhs,divides<TDATA>());
}

template <typename TDATE, typename TDATA>
TSeries<TDATE,TDATA> operator+(const TDATA lhs, const TSeries<TDATE,TDATA>& rhs) {
  return apply_opp(lhs,rhs,plus<TDATA>());
}

template <typename TDATE, typename TDATA>
TSeries<TDATE,TDATA> operator-(const TDATA lhs, const TSeries<TDATE,TDATA>& rhs) {
  return apply_opp(lhs,rhs,minus<TDATA>());
}

template <typename TDATE, typename TDATA>
TSeries<TDATE,TDATA> operator*(const TDATA lhs, const TSeries<TDATE,TDATA>& rhs) {
  return apply_opp(lhs,rhs,multiplies<TDATA>());
}

template <typename TDATE, typename TDATA>
TSeries<TDATE,TDATA> operator/(const TDATA lhs, const TSeries<TDATE,TDATA>& rhs) {
  return apply_opp(lhs,rhs,divides<TDATA>());
}

template <typename TDATE, typename TDATA>
TSeries<TDATE,TDATA> operator+(const TSeries<TDATE,TDATA>& lhs, const TDATA rhs) {
  return apply_opp(lhs,rhs,plus<TDATA>());
}

template <typename TDATE, typename TDATA>
TSeries<TDATE,TDATA> operator-(const TSeries<TDATE,TDATA>& lhs, const TDATA rhs) {
  return apply_opp(lhs,rhs,minus<TDATA>());
}

template <typename TDATE, typename TDATA>
TSeries<TDATE,TDATA> operator*(const TSeries<TDATE,TDATA>& lhs, const TDATA rhs) {
  return apply_opp(lhs,rhs,multiplies<TDATA>());
}

template <typename TDATE, typename TDATA>
TSeries<TDATE,TDATA> operator/(const TSeries<TDATE,TDATA>& lhs, const TDATA rhs) {
  return apply_opp(lhs,rhs,divides<TDATA>());
}

template <typename TDATE, typename TDATA>
std::ostream& operator<< (std::ostream& os, const TSeries<TDATE,TDATA>& ts) {
  vector<string> cnames(ts.getColnames());
  
  if(cnames.size()) {
    // shift out to be in line w/ first column of values (space is for dates column)
    os << "\t";
    for(vector<string>::const_iterator iter = cnames.begin(); iter != cnames.end(); iter++) {
      os << *iter++ << " ";
    }
  }

  TDATE* dates = ts.getDates();
  TDATA* data = ts.getData();
  TSDIM nr  = ts.nrow();
  TSDIM nc  = ts.ncol();
  
  for(TSDIM row = 0; row < nr; row++) {
    os << dates[row] << "\t";
    for(TSDIM col = 0; col < nc; col++) {
      os << data[row + col*nc] << " ";
    }
    os << std::endl;
  }
  return os;
}

template <typename TDATE,typename TDATA>
TSeries<TDATE,TDATA>::~TSeries() {
  tsdata_->detach();
}

template <typename TDATE,typename TDATA>
TSeries<TDATE,TDATA>::TSeries() {
  tsdata_ = TSdata<TDATE,TDATA>::init();
}

template <typename TDATE,typename TDATA>
TSeries<TDATE,TDATA>::TSeries(const TSDIM rows, const TSDIM cols) {
  tsdata_ = TSdata<TDATA,TDATA>::init(rows,cols);
}

template <typename TDATE,typename TDATA>
TSeries<TDATE,TDATA>::TSeries(const TSeries& T) {
  tsdata_ = T.tsdata_;
  tsdata_->attach();
}

template <typename TDATE,typename TDATA>
TSeries<TDATE,TDATA> TSeries<TDATE,TDATA>::copy() const {
  TSeries ans(nrow(),ncol());
  ans.setColnames(getColnames());

  copyVector(ans.getDates(), getDates(),nrow());
  copyVector(ans.getData(), getData(), nrow() * ncol() );

  return ans;
}

template <typename TDATE,typename TDATA>
inline
TDATE* TSeries<TDATE,TDATA>::getDates() const {
  return tsdata_->getDates();
}

template <typename TDATE,typename TDATA>
inline
TDATA* TSeries<TDATE,TDATA>::getData() const {
  return tsdata_->getData();
}


template <typename TDATE,typename TDATA>
inline
const TSDIM TSeries<TDATE,TDATA>::nrow() const {
  return tsdata_->nrow();
}

template <typename TDATE,typename TDATA>
inline
const TSDIM TSeries<TDATE,TDATA>::ncol() const {
  return tsdata_->ncol();
}

template <typename TDATE,typename TDATA>
inline
vector<string> TSeries<TDATE,TDATA>::getColnames() const {
  return tsdata_->getColnames();
}

template <typename TDATE,typename TDATA>
int TSeries<TDATE,TDATA>::setColnames(const vector<string>& cnames) {
  if(cnames.size() == ncol()) {
    tsdata_->setColnames(cnames);
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}


#endif // TSERIES_HPP
