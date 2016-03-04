#include <sstream>
#include <string>
using namespace std;

string i2a(int intValue) {
  ostringstream oss (ostringstream::out);
  oss <<intValue;
  string strRetVal=oss.str();
  return(strRetVal);
}

string d2a(double dValue) {
  ostringstream oss (ostringstream::out);
  oss <<dValue;
  string strRetVal=oss.str();
  return(strRetVal);
}
