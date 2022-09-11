#ifndef GEOMETRY_BUILDER_H
#define GEOMETRY_BUILDER_H

#include <string>
#include <unordered_map>
#include <utility>
#include <functional>
#include "Module.h"
#include "Cube.h"
#include "APVMapping.h"
#include "APVStruct.h"
#include <QColor>
#include "json_fwd.hpp"

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

    class GeometryBuilder
    {
    public:
        GeometryBuilder();
        ~GeometryBuilder();

        void SetTextFile(const char* path);
        Module * GetCompleteAssembly() const;
        void SetWorldHalfW(float w);
        void Build();

    protected:
        void SetupVolume();
        void BuildFromJsonFile();

    private:
        void build_geometry_from_json_file_impl();
        Module* __build(const nlohmann::json &);
        Module* __build_primitive(const nlohmann::json &);
        // unit test
        Module * build_chamber_test();
        Module * build_apv_test();
        Module * build_chamber_apv_test();
        Module * build_layer_test();
        Module * build_assembly_test();
        void geometry_test();

    private:
        apv_mapping::Mapping *map = nullptr;
        std::string path;
        std::unordered_map<apv_mapping::APVAddress, Cube> apv_volumes;
        std::unordered_map<apv_mapping::APVAddress, QColor> apv_color;
        std::unordered_map<ChamberAddress, Cube> chamber_volumes;
        Module *assembly = nullptr;

        float world_halfw = 1000;
        float unit = 0.001;

        nlohmann::json *json_parser;
    };
}

#endif
