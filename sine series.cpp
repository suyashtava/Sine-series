#include <iostream>
#include <boost/math/constants/constants.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/multiprecision/number.hpp>
#include <numeric>
using namespace boost::multiprecision;
typedef cpp_bin_float_50 num;
using namespace boost::math::constants;
num eval_sin(const num& val)
{
   num       EPS  = std::numeric_limits<num>::epsilon();
   const num PI   = boost::math::constants::pi<num>();
   const num PI_2 = boost::math::constants::half_pi<num>();
   num  x             = val;
   bool negate_result = false;
   if (x.sign() < 0)
   {
      negate_result = true;
      x= -x;
   }
   while (x > PI)
   {
      x -= PI;
      negate_result = !negate_result;
   }
   if (x > PI_2)
   {
      x = PI - x;
   }
   const num MINUS_ONE = -1.0;
   const num ONE       = 1.0;
   const num TWO       = 2.0;
   num result     = 0;
   num multiplier = ONE;
   num seq        = x;
   do
   {
      result += seq;
      seq        = (MINUS_ONE * seq * x * x) / ((multiplier + ONE) * (multiplier + TWO));
      multiplier = multiplier + TWO;
   } while (abs(seq) > EPS);
   if (negate_result)
   {
      result = -result;
   }
   return result;
}
int main()
{
   //Case 1:  PI / 2
   num t1(boost::math::constants::half_pi<num>());
   std::cout << "Calculated: " << std::setprecision(std::numeric_limits<num>::digits10) << eval_sin(t1) << std::endl;
   std::cout << "Library Code: " << std::setprecision(std::numeric_limits<num>::digits10) << sin(t1) << std::endl;

   // Case 2: PI / 3
   num t2(boost::math::constants::third_pi<num>());
   std::cout << "Calculated: " << std::setprecision(std::numeric_limits<num>::digits10) << eval_sin(t2) << std::endl;
   std::cout << "Library Code: " << std::setprecision(std::numeric_limits<num>::digits10) << sin(t2) << std::endl;

   //Case 3 :  2
   num t3(2);
   std::cout << "Calculated: " << std::setprecision(std::numeric_limits<num>::digits10) << eval_sin(t3) << std::endl;
   std::cout << "Library Code: " << std::setprecision(std::numeric_limits<num>::digits10) << sin(t3) << std::endl;

   // case 4: pi+2
   num t4(boost::math::constants::pi<num>() + 2);
   std::cout << "Calculated: " << std::setprecision(std::numeric_limits<num>::digits10) << eval_sin(t4) << std::endl;
   std::cout << "Library Code: " << std::setprecision(std::numeric_limits<num>::digits10) << sin(t4) << std::endl;
}
