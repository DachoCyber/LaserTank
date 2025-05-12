#include "tinyxml2/tinyxml2.h"
#include "include/extractMatrix.h"
#include <sstream>

using namespace tinyxml2;

const int N = 18;
void readMapFromXML(std::vector<std::vector<int>>& map) {
    map.resize(N, std::vector<int>(N));

    XMLDocument doc;
    XMLError res = doc.LoadFile("map1.tmx");

    if(res != XML_SUCCESS) {
        throw std::runtime_error("Failed to load file map1.tmx!");
    }

    XMLElement* root = doc.FirstChildElement("map");
    if(!root) {
        throw std::runtime_error("Invalid map file: no 'map' element found");
    }

    for(XMLElement* layer = root->FirstChildElement("layer");
        layer != nullptr;
        layer = layer->NextSiblingElement("layer")) {

        XMLElement* data = layer->FirstChildElement("data");
        if(data) {
            const char* encoding = data->Attribute("encoding");
            if(encoding && std::string(encoding) == "csv") {
                const char* csvText = data->GetText();
                if(!csvText) continue;

                std::string csvData = csvText;
                std::istringstream iss(csvData);
                std::string token;
                int currElCount = 0;

                while (std::getline(iss, token, ',')) {
                    if (currElCount >= N * N) break;  // prevent overflow
                    
                    try {
                        int value = std::stoi(token);
                        map[currElCount / N][currElCount % N] = value;
                        currElCount++;
                    } catch(const std::exception& e) {
                        // Handle or log conversion error
                        continue;
                    }
                }
            }
        }
    }
}