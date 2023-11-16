template<typename Scalar>
class Accumulator {
  unsigned long long n;
  Scalar sum;
  Scalar sq_sum;

public:
  Accumulator(): n(0), sum(0.), sq_sum(0.) {}

  void add(Scalar x){
    sum = sum + x;
    sq_sum = sq_sum + x*x;
    n += 1;
  }

  Scalar getMean(){
    return sum/n;
  }

  Scalar getVar(){
    return sq_sum/n - (sum/n)*(sum/n);
  }
};
