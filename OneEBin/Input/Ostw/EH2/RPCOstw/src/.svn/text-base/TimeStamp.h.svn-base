#ifndef TIMESTAMP_HH
#define TIMESTAMP_HH
/**
 * \class TimeStamp
 *
 * \ingroup Validity
 *
 * \brief Encapsulate the seconds and ns since EPOCH
 * 
 * Stolen shamelessly from MINOS framework. 
 *
 * CAUTION: this class takes and returns values that are implicitly in
 * units of seconds and not in the standard CLHEP SystemOfUnits that
 * are used elsewhere.  Be sure to convert take this into account when
 * mixing TimeStamps with times that are expressed in the
 * SystemOfUnits.  For example:
 *
 * #include "CLHEP/Units/SystemOfUnits.h"
 * ...
 * double timeStampToSystemOfUnits(const TimeStamp& ts) 
 * {
 *   // States that ts *IS* in seconds so multiply
 *   return (double)ts * CLHEP::seconds;
 * }
 *
 * TimeStamp systemOfUnitsToTimeStamp(double time)
 * {
 *   // States that we *WANT* time in seconds so divide
 *   return TimeStamp(time / CLHEP::seconds);
 * }
 *
 *
 * TimeStamp extends (and isolates) struct timespec
 *
 *    struct timespec
 *       {
 *          time_t   tv_sec;   // seconds
 *          long     tv_nsec;  // nanoseconds
 *       }
 *    time_t seconds is relative to Jan 1, 1970 00:00:00 UTC
 *
 * Due to ROOT/CINT limitations TimeStamp does not explicitly
 * hold a timespec struct; attempting to do so means the Streamer
 * must be hand written.  Instead we have chosen to simply contain
 * similar fields within the private area of this class.
 *
 * \note
 *       the use of time_t (and its default implementation as a 32 int)
 *       implies overflow conditions occurs somewhere around
 *       Jan 18, 19:14:07, 2038.
 *       If this experiment is still going when it becomes significant
 *       someone will have to deal with it.
 *

 *
 * \author Robert Hatcher (MINOS). Introduced to Dyb by Nathaniel Tagg.
 *
 * \version $Revision: 1.2 $
 *
 * \date $Date: 2006/10/31 19:59:24 $
 *
 * Contact: N. Tagg
 *
 * Created on: Wed Apr 13 17:53:23 2005
 *
 * $Id: TimeStamp.hh,v 1.2 2006/10/31 19:59:24 tagg Exp $
 *
 */


/// Omit this section from doxygen:
#include <ctime>

// make the TimeStamp cout'able
#include <iosfwd>


class TimeStamp;
std::ostream& operator<<(std::ostream& os, const TimeStamp& vldts);

class TimeStamp {

    friend bool operator==(const TimeStamp &lhs, const TimeStamp &rhs);
    friend bool operator!=(const TimeStamp &lhs, const TimeStamp &rhs);
    friend bool operator< (const TimeStamp &lhs, const TimeStamp &rhs);
    friend bool operator<=(const TimeStamp &lhs, const TimeStamp &rhs);
    friend bool operator> (const TimeStamp &lhs, const TimeStamp &rhs);
    friend bool operator>=(const TimeStamp &lhs, const TimeStamp &rhs);

    friend TimeStamp operator- (const TimeStamp &lhs, const TimeStamp &rhs);

public:

    /// Static method to return the "beginning of time" (start of Unix EPOCH)
    static TimeStamp GetBOT();

    /// Static method to return the "end of time" which is sometime in
    /// the future and near or at the limit of TimeStamp's ability
    /// to hold large times.
    static TimeStamp GetEOT();

    /// Static method to return the "negative beginning of time", i.e. the
    /// earliest time prior to start of Unix EPOCH which is negative seconds.
    static TimeStamp GetNBOT();

    /// Empty ctor (builds current time with nsec field filled as best possible)
    TimeStamp();

    /// Copy
    TimeStamp(const TimeStamp &source)
        { mSec = source.mSec; mNanoSec = source.mNanoSec; }
    /// Assignment
    TimeStamp& operator=(const TimeStamp &source)
        { if (this != &source) {mSec = source.mSec; mNanoSec = source.mNanoSec;}
            return *this; }

    /// Construction from timespec struct
    TimeStamp(const timespec &ts)
        { mSec = ts.tv_sec; mNanoSec = ts.tv_nsec; NormalizeNanoSec(); }

    /// Construction from time_t and separate nsec
    TimeStamp(const time_t &t, const int nsec)
        { mSec = t; mNanoSec = 0; mNanoSec = nsec; NormalizeNanoSec(); }

    /// Create a TimeStamp and set it to the specified year, month,
    /// day, time, hour, minute, second and nanosec.
    /// If !isUTC then it is assumed to be the standard local time zone.
    ///
    /// If local time is PST then one can use
    ///
    ///    TimeStamp(year,month,day,hour,min,sec,nsec,false,0);
    ///
    /// or
    ///
    ///    int secOffset = 8*60*60;
    ///    TimeStamp(year,month,day,hour,min,sec,nsec,true,8*60*60);
    TimeStamp(unsigned int year, unsigned int month,
              unsigned int day,  unsigned int hour,
              unsigned int min,  unsigned int sec,
              unsigned int nsec=0, 
              bool isUTC=true, int secOffset=0);

    /// Create a TimeStamp and set it to the specified date, time, nanosec.
    /// If !isUTC then it is assumed to be the standard local time zone.
    TimeStamp(unsigned int date, unsigned int time, unsigned int nsec, 
              bool isUTC=true, int secOffset=0);

    // Create a TimeStamp using double precision floating point
    // seconds from the EPOCH.
    //
    // \warning This will truncate precision to no better than about 1
    // microsecond.  Do not use this constructor for timestamps that
    // are expected to be more precise!
    //
    TimeStamp(double seconds)
        { mSec = (int)seconds; mNanoSec = (int)((seconds-mSec)*1.0e9); 
            NormalizeNanoSec();}
  

    virtual ~TimeStamp();

    // Implicitly convert a TimeStamp to a double.
    //
    // \warning This will truncate precision to no better than about 1
    // microsecond.  Do not compare/subtract TimeStamps that have
    // been converted to doubles if you require the full nanosecond
    // precision!
  
    operator double() const { return mSec + 1.0e-9 * mNanoSec; }
  
  
    /// Get timestamp as a timespec
    timespec     GetTimeSpec() const { timespec value = {mSec,mNanoSec}; return value; }
  
    /// Get (integral) seconds after the EPOCH
    time_t         GetSec(void) const { return mSec;}
    /// Get nanoseconds after the second
    int          GetNanoSec(void) const { return mNanoSec; }
  
    /// Get time from the epoch in seconds
    double GetSeconds(void) const { return mSec+(mNanoSec/1.0e9); }
  
    //    Return the date & time as a string.
    //   
    //    Result is pointer to a statically allocated string.
    //    User should copy this into their own buffer before calling
    //    this method again.  This is somewhat mitigated
    //    by use of a circular buffer of strings.
    //   
    //    Option "l" returns it in local zone format
    //    (can be applied to default or compact format).
    //   
    //    Default format is RFC822 compliant:
    //      "Mon, 02 Jan 2001 18:11:12 +0000 (GMT) +999999999 nsec"
    //      "Mon, 02 Jan 2001 10:11:12 -0800 (PST) +999999999 nsec"
    //   
    //    Option "c" compact is (almost) ISO 8601 compliant:
    //      "2001-01-02 18:11:12.9999999999Z"
    //      "2001-01-02 10:11:12.9999999999-0800"  if PST
    //         * uses "-" as date separator as specified in ISO 8601
    //         * uses "." rather than preferred "," for decimal separator
    //         * -HHMM is the difference between local and UTC (if behind, + if ahead).
    //      The "-HHMM" is replaced with "Z" if given as UTC.
    //      To be strictly conforming it should use "T" instead of the
    //      blank separating the date and time.
    //   
    //    Option "2" returns as {sec,nsec} integers.
    //   
    //    Option "s" returns "2001-01-02 18:11:12" with an implied UTC,
    //    overrides "l" option.
    //   
    //    Internally uses a circular list of buffers to avoid problems
    //    using AsString multiple times in a single statement.
    //    
    const char    *AsString(const char* option="") const;
    void           Copy(TimeStamp &vldts) const;

    /// Return date in form of 19971224 (i.e. 24/12/1997),
    /// if non-zero pointers supplied for year, month, day fill those as well
    int          GetDate(bool inUTC=true, int secOffset=0,
			 unsigned int *year=0, unsigned int *month=0,
			 unsigned int *day=0) const;

    /// Return time in form of 123623 (i.e. 12:36:23),
    /// if non-zero pointers supplied for hour, min, sec fill those as well
    int          GetTime(bool inUTC=true, int secOffset=0,
			 unsigned int* hour=0, unsigned int* min=0, 
			 unsigned int* sec=0) const;

    void           Add(const TimeStamp& offset);
    void           Add(double seconds);
    void           Subtract(const TimeStamp& offset);
    void           Subtract(double seconds);
    TimeStamp      CloneAndSubtract(const TimeStamp& offset);
    
    void           Print(const char* option="") const;
  
    bool          IsNull() const { return (mSec==0)&&(mNanoSec==0); };
  
    // Utility functions
  
    /// Static method returning local (current) time zone offset from UTC.
    /// This is the difference in seconds between UTC and local standard time.
    static int   GetZoneOffset();
 
    // Equivalent of standard routine "mktime" but
    // using the assumption that tm struct is filled with UTC, not local, time.
    //
    // This version *ISN'T* configured to handle every possible
    // weirdness of out-of-range values in the case of normalizing
    // the tm struct.
    //
    // This version *DOESN'T* correctly handle values that can't be
    // fit into a time_t (i.e. beyond year 2038-01-18 19:14:07, or
    // before the start of Epoch). */
  
    static time_t  MktimeFromUTC(tm* tmstruct);
  
    /// Is the given year a leap year.
    static bool  IsLeapYear(int year);
  
    /// Print out the "tm" structure:
    static void    DumpTMStruct(const tm& tmstruct);

private:

    void           Set();
    void           Set(int year, int month, int day,
                       int hour, int min, int sec, 
                       int nsec, bool isUTC, int secOffset);
    void           Set(int date, int time, int nsec,
                       bool isUTC, int secOffset);
    void           NormalizeNanoSec();

    // Data members:
    // similar fields to struct timespec
    // use ROOT versions to "know" that they are platform consistent
    // 32-bit integers to avoid IO confusion.
    int  mSec;
    int  mNanoSec;

};


//=============================================================================
// Implementation details -- inlines need to be hidden from CINT
//=============================================================================

inline bool operator==(const TimeStamp &lhs, const TimeStamp &rhs)
{ return lhs.mSec  == rhs.mSec && 
        lhs.mNanoSec == rhs.mNanoSec; }

inline bool operator!=(const TimeStamp &lhs, const TimeStamp &rhs)
{ return lhs.mSec  != rhs.mSec ||
        lhs.mNanoSec != rhs.mNanoSec; }

inline bool operator<(const TimeStamp &lhs, const TimeStamp &rhs)
{ return lhs.mSec  < rhs.mSec ||
        ( lhs.mSec  == rhs.mSec &&
          lhs.mNanoSec <  rhs.mNanoSec   ); }

inline bool operator<=(const TimeStamp &lhs, const TimeStamp &rhs)
{ return lhs.mSec  < rhs.mSec ||
        ( lhs.mSec  == rhs.mSec &&
          lhs.mNanoSec <= rhs.mNanoSec   ); }

inline bool operator>(const TimeStamp &lhs, const TimeStamp &rhs)
{ return lhs.mSec  > rhs.mSec ||
        ( lhs.mSec  == rhs.mSec &&
          lhs.mNanoSec >  rhs.mNanoSec   ); }

inline bool operator>=(const TimeStamp &lhs, const TimeStamp &rhs)
{ return lhs.mSec  > rhs.mSec ||
        ( lhs.mSec  == rhs.mSec &&
          lhs.mNanoSec >= rhs.mNanoSec   ); }

inline TimeStamp operator-(const TimeStamp& lhs, const TimeStamp& rhs)
{
    return TimeStamp(lhs.GetSec()     - rhs.GetSec(),
                     lhs.GetNanoSec() - rhs.GetNanoSec());
}

#endif // TIMESTAMP_HH
