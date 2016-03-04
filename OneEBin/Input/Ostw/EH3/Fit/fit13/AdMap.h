#ifndef __ADMAP_H__
#define __ADMAP_H__

#include <map>

/* Site 1,2,4 */
/* LocalAdNo 1,2,3,4 */

/* GlobalAdIdx 1,2,3,4,5,6,7,8 */
/* Follow the convention in constants.h */

extern int SiteMap[6];
extern int LocalAdNoMap[6];

int GlobalAdIdx(int Site, int LocalAdNo);

int ToSite(int GlobalAdIdx);

int ToLocalAdNo(int GlobalAdIdx);

#endif // __ADMAP_H__
