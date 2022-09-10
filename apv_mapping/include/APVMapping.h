#ifndef APV_MAPPING_H
#define APV_MAPPING_H

#include <unordered_map>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include "APVStruct.h"

namespace base_cad::apv_mapping
{
    ////////////////////////////////////////////////////////////////////////////////
    // a struct stores all apv information 
    struct APVInfo
    {
        int crate_id, layer_id, mpd_id;

        // detector id is an unique number assigned to each GEM during assembly in UVa
        // it is labeled on each detector
        int detector_id;

        // x/y plane (0=x; 1=y; to be changed to string)
        int dimension;
        int adc_ch, i2c_ch, apv_pos, invert;
        std::string discriptor;
        int backplane_id, gem_pos;

        APVInfo(){};
        APVInfo(const std::string &str)
        {
            if(str.find("APV") == std::string::npos)
                return;

            std::istringstream entry(str);
            std::string token;
            std::vector<std::string> tmp;

            while(std::getline(entry, token, ','))
                tmp.push_back(token);

            crate_id    = std::stoi(tmp[1]);
            layer_id    = std::stoi(tmp[2]); 
            mpd_id      = std::stoi(tmp[3]);
            detector_id = std::stoi(tmp[4]);
            dimension   = std::stoi(tmp[5]);
            adc_ch      = std::stoi(tmp[6]); 
            i2c_ch      = std::stoi(tmp[7]);
            apv_pos     = std::stoi(tmp[8]);   
            invert      = std::stoi(tmp[9]);
            discriptor  = tmp[10];          
            backplane_id= std::stoi(tmp[11]);
            gem_pos     = std::stoi(tmp[12]);
        }
    };

    std::ostream &operator<<(std::ostream& out, const APVInfo &);

    ////////////////////////////////////////////////////////////////////////////////
    // a struct stores all layer information 
    struct LayerInfo
    {
        int layer_id, chambers_per_layer;
        std::string readout_type;
        float x_offset, y_offset;
        std::string gem_type;
        int nb_apvs_x, nb_apvs_y;
        float x_pitch, y_pitch;
        int x_flip, y_flip;

        LayerInfo() {};
        LayerInfo(const std::string &str)
        {
            if(str.find("Layer") == std::string::npos)
                return;

            std::istringstream entry(str);
            std::string token;
            std::vector<std::string> tmp;
            while(std::getline(entry, token, ','))
                tmp.push_back(token);

            layer_id     = std::stoi(tmp[1]);
            chambers_per_layer = std::stoi(tmp[2]); 
            readout_type = tmp[3];
            x_offset     = std::stod(tmp[4]);
            y_offset     = std::stod(tmp[5]); 
            gem_type     = tmp[6];
            nb_apvs_x    = std::stoi(tmp[7]);
            nb_apvs_y    = std::stoi(tmp[8]);          
            x_pitch      = std::stod(tmp[9]);
            y_pitch      = std::stod(tmp[10]);
            x_flip       = std::stoi(tmp[11]);
            y_flip       = std::stoi(tmp[12]);
        }
    };

    std::ostream &operator<<(std::ostream& out, const LayerInfo &);

    ////////////////////////////////////////////////////////////////////////////////
    // a gem mapping class
    // this class is redundant, to be removed in the future
    class Mapping 
    {
    public:
        static Mapping* Instance()
        {
            if(!instance)
                instance = new Mapping();
            return instance;
        }

        Mapping(Mapping const &) = delete;
        void operator=(Mapping const &) = delete;

        ~Mapping(){}

        void LoadMap(const char* path);
        void Print();

        // members
        void ExtractMPDAddress();
        void ExtractAPVAddress();
        void ExtractDetectorID();
        void ExtractLayerID();

        // getters
        int GetTotalNumberOfDetectors();
        int GetTotalNumberOfLayers();
        int GetTotalNumberOfAPVs() const;

        int GetTotalMPDs();
        const std::vector<MPDAddress> & GetMPDAddressVec() const;
        const std::vector<APVAddress> & GetAPVAddressVec() const;
        const std::vector<int> & GetLayerIDVec() const;
        const std::map<int, LayerInfo> & GetLayerMap() const;

    private:
        static Mapping* instance;
        Mapping();

        std::unordered_map<APVAddress, APVInfo> apvs;
        std::vector<MPDAddress> vMPDAddr;
        std::vector<APVAddress> vAPVAddr;
        std::vector<int> vDetID;
        std::vector<int> vLayerID;

        std::map<int, LayerInfo> layers;

        bool map_loadded = false;
    };
}

#endif
