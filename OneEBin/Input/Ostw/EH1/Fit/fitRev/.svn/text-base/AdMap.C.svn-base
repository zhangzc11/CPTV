#include "AdMap.h"

/* Site 1,2,4 */
/* LocalAdNo 1,2,3,4 */

/* GlobalAdIdx 1,2,3,4,5,6,7,8 */

int SiteMap[6]      = {1,1,2,4,4,4};
int LocalAdNoMap[6] = {1,2,1,1,2,3};

int GlobalAdIdx(int Site, int LocalAdNo)
{
  if( Site == 1 ) return LocalAdNo;
  if( Site == 2 ) return 2+LocalAdNo;
  if( Site == 4 ) return 3+LocalAdNo;
  
  /* Invalid */
  return -1;
}

int ToSite(int GlobalAdIdx)
{
  return SiteMap[GlobalAdIdx-1];
}

int ToLocalAdNo(int GlobalAdIdx)
{
  return LocalAdNoMap[GlobalAdIdx-1];
}
