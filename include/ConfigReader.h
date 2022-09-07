#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <string>
#include <unordered_map>
#include <utility>
#include <functional>
#include "Module.h"
#include "Cube.h"
#include "APVMapping.h"
#include "APVStruct.h"

namespace std {
    template<> struct hash<std::pair<int, int>>
    {
        std::size_t operator()(const std::pair<int, int> &key) const
        {
            return (std::hash<int>()(key.second & 0xf) | 
                std::hash<int>()((key.first & 0xf) << 4));
        }
    };
}

namespace base_cad
{
    using ChamberAddress = std::pair<int, int>; // layer id, module position

    class ConfigReader
    {
    public:
        ConfigReader();
        ~ConfigReader();

        void ReadAPVMapping(const char* path);
        Module * GetCompleteAssembly() const;

    protected:
        void SetupVolume();

    private:
        apv_mapping::Mapping *map = nullptr;
        std::string path;
        std::unordered_map<apv_mapping::APVAddress, Cube> apv_volumes;
        std::unordered_map<ChamberAddress, Cube> chamber_volumes;
        Module *assembly = nullptr;
    };
}

#endif
