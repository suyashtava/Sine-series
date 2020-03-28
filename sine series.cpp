{\rtf1\ansi\ansicpg1252\deff0\nouicompat\deflang1033{\fonttbl{\f0\fnil\fcharset0 Calibri;}}
{\*\generator Riched20 10.0.18362}\viewkind4\uc1 
\pard\sa200\sl276\slmult1\f0\fs22\lang9 #include <iostream>\par
#include <boost/math/constants/constants.hpp>\par
#include <boost/multiprecision/cpp_bin_float.hpp>\par
#include <boost/multiprecision/number.hpp>\par
#include <numeric>\par
using namespace boost::multiprecision;\par
typedef cpp_bin_float_50 num;\par
using namespace boost::math::constants;\par
num eval_sin(const num& val)\par
\{\par
   num       EPS  = std::numeric_limits<num>::epsilon();\par
   const num PI   = boost::math::constants::pi<num>();\par
   const num PI_2 = boost::math::constants::half_pi<num>();\par
   num  x             = val;\par
   bool negate_result = false;\par
   if (x.sign() < 0)\par
   \{\par
      negate_result = true;\par
      x= -x;\par
   \}\par
   while (x > PI)\par
   \{\par
      x -= PI;\par
      negate_result = !negate_result;\par
   \}\par
   if (x > PI_2)\par
   \{\par
      x = PI - x;\par
   \}\par
   const num MINUS_ONE = -1.0;\par
   const num ONE       = 1.0;\par
   const num TWO       = 2.0;\par
   num result     = 0;\par
   num multiplier = ONE;\par
   num seq        = x;\par
   do\par
   \{\par
      result += seq;\par
      seq        = (MINUS_ONE * seq * x * x) / ((multiplier + ONE) * (multiplier + TWO));\par
      multiplier = multiplier + TWO;\par
   \} while (abs(seq) > EPS);\par
   if (negate_result)\par
   \{\par
      result = -result;\par
   \}\par
   return result;\par
\}\par
int main()\par
\{\par
   //Case 1:  PI / 2\par
   num t1(boost::math::constants::half_pi<num>());\par
   std::cout << "Calculated: " << std::setprecision(std::numeric_limits<num>::digits10) << eval_sin(t1) << std::endl;\par
   std::cout << "Library Code: " << std::setprecision(std::numeric_limits<num>::digits10) << sin(t1) << std::endl;\par
\par
   // Case 2: PI / 3\par
   num t2(boost::math::constants::third_pi<num>());\par
   std::cout << "Calculated: " << std::setprecision(std::numeric_limits<num>::digits10) << eval_sin(t2) << std::endl;\par
   std::cout << "Library Code: " << std::setprecision(std::numeric_limits<num>::digits10) << sin(t2) << std::endl;\par
\par
   //Case 3 :  2\par
   num t3(2);\par
   std::cout << "Calculated: " << std::setprecision(std::numeric_limits<num>::digits10) << eval_sin(t3) << std::endl;\par
   std::cout << "Library Code: " << std::setprecision(std::numeric_limits<num>::digits10) << sin(t3) << std::endl;\par
\par
   // case 4: pi+2\par
   num t4(boost::math::constants::pi<num>() + 2);\par
   std::cout << "Calculated: " << std::setprecision(std::numeric_limits<num>::digits10) << eval_sin(t4) << std::endl;\par
   std::cout << "Library Code: " << std::setprecision(std::numeric_limits<num>::digits10) << sin(t4) << std::endl;\par
\}\par
}
 