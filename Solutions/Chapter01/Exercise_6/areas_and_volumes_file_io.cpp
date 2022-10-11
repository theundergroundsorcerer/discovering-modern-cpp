// Exercise 6, Chapter 1 in Discovering Modern C++ 2nd edition
// Reads radius and height as parameters, and then writes these parameters to
// a file together with areas and volumes of common 3d figures
// a second function then called that reads the contents of this file and compares
// the values in the file with the original ones

#include <fstream>
#include <iostream>
#include <filesystem>
#include <bit>
#include "toy_geometry.h"
#include <toy_utilities.h>
#include <array>
#include <vector>
#include <stdexcept>

using namespace std::string_literals;

inline std::vector<const char*> DataFieldNames() {
    return std::vector{"Radius", "Height", "Sphere surface area", "Sphere volume",
                       "Cube surface area", "Cube volume",
                       "Cylinder surface area", "Cylinder volume",
                       "Cone surface area", "Cone volume"};
}

std::vector<double> GenerateData(double radius, double height) {
    return std::vector<double> {
        radius, height, SphereSurfaceArea(radius), SphereVolume(radius),
        CubeSurfaceArea(height), CubeVolume(height),
        CylinderSurfaceArea(radius, height), CylinderVolume(radius, height),
        CylinderSurfaceArea(radius,height), CylinderVolume(radius, height)
    };
}

namespace fs = std::filesystem;

inline std::string TextDataFolderName() {
    return "area_volume_data";
}

inline std::string BinaryDataFolderName() {
    return "area_volume_binary_data";
}

std::string AreaVolumeFileName(const double radius, const double height, const std::string& folder_name) {
    constexpr auto file_prefix {"data_for_"};
    fs::path directory_path{folder_name};
    if(!fs::exists(fs::status(directory_path))) {
        fs::create_directory(directory_path);
    }

    std::ostringstream output;
    output << folder_name << '/' << file_prefix << height << "_" << radius << ".txt";
    return output.str();
}

std::string TextDataFileName(const double radius, const double height) {
    return AreaVolumeFileName(radius, height, TextDataFolderName());
}

std::string BinaryDataFileName(const double radius, const double height) {
    return AreaVolumeFileName(radius, height, BinaryDataFolderName());
}

void MakeAreaVolumeTextFile(const double radius, const double height) {
    std::string outputFileName{TextDataFileName(radius, height)};
    std::ofstream dataFile{outputFileName};

    if(!dataFile.good()) {
        std::cerr << "Could not open file " << outputFileName << "for writing.\n";
        exit(1);
    }

    for(const double value : GenerateData(radius, height)) {
        dataFile << value << ' ';
    }
    dataFile << '\n';
}

void WriteBinaryDouble(double d, std::ostream& out) {
    out.write(&(std::bit_cast<std::array<const char, sizeof(d)>>(d)[0]), sizeof(d));
}


std::vector<double> ReadTextValues(const std::string& inputFileName) {
    std::ifstream input{inputFileName};
    if(!input) {
        throw std::runtime_error{"Could not create or open" + TextDataFolderName()};
    }
    std::vector<double> result;

    double value;
    bool readSuccess = ReadFromStream(value, input);
    while(readSuccess) {
        result.push_back(value);
        readSuccess= ReadFromStream(value, input);
    }

    return result;
}

std::vector<double> ReadBinaryValues(const std::string& inputFileName) {
    std::ifstream input{inputFileName, std::ios::binary};
    if(!input) {
        throw std::runtime_error{"Could not create or open" + TextDataFolderName()};
    }
    std::vector<double> result;

    double value;
    input.read(reinterpret_cast<char *>(&value), sizeof(value));

    while(input) {
        result.push_back(value);
        input.read(reinterpret_cast<char *>(&value), sizeof(value));
    }

    return result;
}

void MakeAreaVolumeBinaryFile(const double radius, const double height) {
    std::string output_file_name{BinaryDataFileName(radius, height)};
    std::ofstream output_file{output_file_name, std::ios::binary};
    if(!output_file) {
        std::cerr << "Could not open " << output_file_name << " for writing!" << '\n';
        exit(1);
    }
    for(const double value: GenerateData(radius, height)) {
        WriteBinaryDouble(value, output_file);
    }
}

void CompareValues(const std::vector<const char*> fieldNames, const std::vector<double>& generatedData,
                   const std::vector<double>& readData) {
    if(fieldNames.size() != generatedData.size() || fieldNames.size() != readData.size()) {
        throw std::length_error{"Sizes must be equal!"};
    }

    int notEqualCount = 0;
    for (unsigned long i = 0; i < fieldNames.size(); ++i) {

        bool areEqual = readData[i] == generatedData[i];

        std::cout << fieldNames[i] << ": " << "Generated value is " << generatedData[i]
                  << ". The value stored in file is: " << readData[i] << ". Generated values and value read from file are "
                  << (areEqual ? "equal." : "not equal.") << '\n';

        if(!areEqual) {
            ++notEqualCount;
            std::cout << "Read value and generated value delta is "
                      << std::abs(readData[i] - generatedData[i]) << '\n';
        }
    }
    std::cout << "There are " << notEqualCount << " generated and read from file values that are not equal.\n"
              << std::endl;

}

void CompareTextData(const double radius, const double height) {
    MakeAreaVolumeTextFile(radius, height);
    std::string dataFileName = TextDataFileName(radius, height);


    const std::vector<const char*> fieldNames = DataFieldNames();
    const std::vector<double> generatedData = GenerateData(radius, height);
    const std::vector<double> readData= ReadTextValues(dataFileName);
    CompareValues(fieldNames, generatedData, readData);
}

void CompareBinaryData(const double radius, const double height) {
    MakeAreaVolumeBinaryFile(radius, height);
    std::string dataFileName = BinaryDataFileName(radius, height);

    const std::vector<const char*> fieldNames = DataFieldNames();
    const std::vector<double> generatedData = GenerateData(radius, height);
    const std::vector<double> readData = ReadBinaryValues(dataFileName);

    CompareValues(fieldNames, generatedData, readData);
}

int main() {
    std::cout << "Comparing text values for radius 1 and height 1.\n";
    CompareTextData(1, 1);
    std::cout << "Comparing binary values for radius 1 and height 1.\n";
    CompareBinaryData(1, 1);
}