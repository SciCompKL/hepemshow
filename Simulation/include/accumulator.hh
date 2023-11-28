#include <set>

template<typename Scalar>
class Accumulator {
  unsigned long long n = 0; //!< Accumulates number of data points.
  Scalar sum = 0.; //!< Accumulates sum of data points.
  Scalar sq_sum = 0.; //!< Accumulates sum of squares of data points.
  int nmins = 0; //!< Number of lowest data points to be excluded as potential outliers. 
  int nmaxs = 0; //!< Number of largest data points to be excluded as potential outliers.
  std::set<Scalar,std::greater<Scalar>> mins; //!< lowest data points
  std::set<Scalar> maxs; //!< largest data points

public:
  Accumulator() {}
  Accumulator(int nmins): nmins(nmins), nmaxs(nmins) {}
  Accumulator(int nmins, int nmaxs): nmins(nmins), nmaxs(nmaxs) {}

  /*! Register a data point. 
   */
  void add(Scalar x){
    sum = sum + x;
    sq_sum = sq_sum + x*x;
    n += 1;
    if(nmins>0){
      mins.insert(x);
      if(mins.size()>nmins) mins.erase(mins.begin());
    }
    if(nmaxs>0){
      maxs.insert(x);
      if(maxs.size()>nmaxs) maxs.erase(maxs.begin());
    }
  }

  /*! Get the mean of the data points that were previously registered.
   * 
   * If nmins/nmaxs were set during construction, the corresponding number
   * of outliers will be excluded. The caller should make sure that at
   * least one element remains.
   */
  Scalar getMean() const {
    Scalar extremes_sum = 0;
    for(Scalar s : mins) extremes_sum+=s;
    for(Scalar s : maxs) extremes_sum+=s;
    return (sum-extremes_sum)/(n-nmins-nmaxs);
  }

  Scalar getVar() const {
    return getMeanSq() - getMean()*getMean();
  }

  /*! Get the mean of the squares of the data points that were previously registered.
   * 
   * If nmins/nmaxs were set during construction, the corresponding number
   * of outliers will be excluded. The caller should make sure that at
   * least one element remains.
   */
  Scalar getMeanSq() const {
    Scalar extremes_sq_sum = 0;
    for(Scalar s : mins) extremes_sq_sum+=s*s;
    for(Scalar s : maxs) extremes_sq_sum+=s*s;
    return (sq_sum-extremes_sq_sum)/(n-nmins-nmaxs);
  }
};
