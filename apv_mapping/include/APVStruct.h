#ifndef APV_STRUCT_H
#define APV_STRUCT_H

#include <unordered_map>
#include <ostream>
#include <cstdlib>
#include <functional>

namespace base_cad::apv_mapping 
{
    ////////////////////////////////////////////////////////////////
    // slot address for MPD
    struct MPDAddress
    {
        int crate_id;
        int mpd_id;

        // default ctor
        MPDAddress():
            crate_id(0), mpd_id(0)
        {}

        // ctor
        MPDAddress(int cid, int mid):
            crate_id(cid), mpd_id(mid)
        {}

        // copy constructor
        MPDAddress(const MPDAddress &r):
            crate_id(r.crate_id), mpd_id(r.mpd_id)
        {}

        // copy assignment
        MPDAddress& operator=(const MPDAddress& r)
        {
            crate_id = r.crate_id;
            mpd_id = r.mpd_id;
            return *this;
        }

        // equal operator
        bool operator ==(const MPDAddress &r) const
        {
            return (r.crate_id == crate_id) && (r.mpd_id == mpd_id);
        }

        // < operator
        bool operator <(const MPDAddress &a) const
        {
            if(crate_id < a.crate_id)
                return true;

            else if(crate_id == a.crate_id)
            {
                if(mpd_id < a.mpd_id) return true;
                else return false;
            }
            else  return false;
        }

        // > operator
        bool operator >(const MPDAddress &a) const
        {
            if(crate_id > a.crate_id)
                return true;

            else if(crate_id == a.crate_id)
            {
                if(mpd_id > a.mpd_id) return true;
                else return false;
            }
            else  return false;
        }
    };

    std::ostream &operator<<(std::ostream &, const MPDAddress &addr);

    ////////////////////////////////////////////////////////////////
    // apv address
    struct APVAddress
    {
        int crate_id;  // 8 bit
        int mpd_id;    // 7 bit
        int adc_ch;    // 4 bit

        // default ctor
        APVAddress():
            crate_id(0), mpd_id(0), adc_ch(0)
        {}

        // ctor
        APVAddress(int cid, int mid, int aid) :
            crate_id(cid), mpd_id(mid), adc_ch(aid)
        {}

        // copy constructor, should not increase address_id
        APVAddress(const APVAddress & r) : 
            crate_id(r.crate_id), mpd_id(r.mpd_id), adc_ch(r.adc_ch)
        {}

        // copy assignment, should not increase address_id
        APVAddress & operator=(const APVAddress &r)
        {
            crate_id = r.crate_id;
            mpd_id = r.mpd_id;
            adc_ch = r.adc_ch;
            return *this;
        }

        bool operator==(const APVAddress &a) const {
            return (a.crate_id == crate_id) && 
                (a.mpd_id == mpd_id) && (a.adc_ch == adc_ch);
        }

        bool operator<(const APVAddress &a) const 
        {
            if(crate_id < a.crate_id) return true;
            else if(crate_id == a.crate_id)
            {
                if(mpd_id < a.mpd_id) return true;
                else if(mpd_id == a.mpd_id) 
                {
                    if(adc_ch < a.adc_ch) return true;
                    else  return false;
                }
                else return false;
            }
            else return false;
        }

        bool operator>(const APVAddress &a) const 
        {
            if(crate_id > a.crate_id) return true;
            else if(crate_id == a.crate_id)
            {
                if(mpd_id > a.mpd_id) return true;
                else if(mpd_id == a.mpd_id)
                {
                    if(adc_ch > a.adc_ch) return true;
                    else return false;
                }
                else return false;
            }
            else return false;
        }
    };

    std::ostream &operator <<(std::ostream &os, const APVAddress &ad);
    ////////////////////////////////////////////////////////////////
    // apv strip address

    struct APVStripAddress
    {
        int crate_id;     // 8 bit
        int mpd_id;       // 7 bit
        int adc_ch;       // 4 bit
        int strip_no;     // 7 bit

        // default ctor
        APVStripAddress():
            crate_id(0), mpd_id(0), adc_ch(0), strip_no(0)
        {}

        // ctor
        APVStripAddress(int cid, int mid, int aid, int chid) :
            crate_id(cid), mpd_id(mid), adc_ch(aid), strip_no(chid)
        {}

        // ctor
        APVStripAddress(const APVAddress &apv_addr, int stripNo)
        {
            crate_id = apv_addr.crate_id;
            mpd_id = apv_addr.mpd_id;
            adc_ch = apv_addr.adc_ch;
            strip_no = stripNo;
        }

        // copy constructor, should not increase address_id
        APVStripAddress(const APVStripAddress & r) : 
            crate_id(r.crate_id), mpd_id(r.mpd_id), adc_ch(r.adc_ch), strip_no(r.strip_no)
        {}

        // copy assignment, should not increase address_id
        APVStripAddress & operator=(const APVStripAddress &r)
        {
            crate_id = r.crate_id;
            mpd_id = r.mpd_id;
            adc_ch = r.adc_ch;
            strip_no = r.strip_no;
            return *this;
        }

        bool operator == (const APVStripAddress & c) const 
        {
            return ( (c.crate_id == crate_id) && 
                    (c.mpd_id == mpd_id) && (c.adc_ch == adc_ch) 
                    && (c.strip_no == strip_no) );
        }
    };
}

////////////////////////////////////////////////////////////////
// add a hash function for MPDAddress
namespace std {
    template<> struct hash<base_cad::apv_mapping::MPDAddress>
    {
        std::size_t operator()(const base_cad::apv_mapping::MPDAddress &k) const
        {
            return ( ((k.mpd_id & 0x7f)) 
                    | ((k.crate_id & 0xff) << 7)
                   );
        }
    };
}

////////////////////////////////////////////////////////////////
// add a hash function for APVAddress
namespace std {
    template<> struct hash<base_cad::apv_mapping::APVAddress>
    {
        std::size_t operator()(const base_cad::apv_mapping::APVAddress &k) const
        {
            return ( (k.adc_ch & 0xf)
                    | ((k.mpd_id & 0x7f) << 4) 
                    | ((k.crate_id & 0xff) << 11)
                   );
        }
    };
}

////////////////////////////////////////////////////////////////
// add a hash function for APVAddress
namespace std {
    template<> struct hash<base_cad::apv_mapping::APVStripAddress>
    {
        std::size_t operator()(const base_cad::apv_mapping::APVStripAddress &k) const
        {
            using std::size_t;
            using std::hash;

            // this should be the ad-hoc method, however 
            // due to the large number of APV channels,
            // this method might introduce collision when
            // crate_id > 0, because if one do a (<< 18)
            // operation, one get at least a number: 2^18
            // = 262144, that is bigger than the default modulus 
            // of underdered_map
            //
            // As a result, one should avoid using
            // APVStripAddress as unordered_map keys
            return ( hash<int>()(k.strip_no & 0x7f)
                    | (hash<int>()(k.adc_ch & 0xf) << 7) 
                    | (hash<int>()(k.mpd_id & 0x7f) << 11)
                    | (hash<int>()(k.crate_id & 0xff) << 18)
                   );
        }
    };
}

#endif
