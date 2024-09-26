#include "utils.h"
#include "Game.h"



std::string BASE_IMAGE_PATH = "data/images/";
std::string mainBuffer;
sf::RenderWindow* windowPointer;

sf::Vector2f screen_shake_offset{ randrangefloat(0,1), randrangefloat(0,1) };



sf::Vector2i TileOffsets[9] = { {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {0, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1} };
//-1,-1  ,  0,-1  ,   1,-1  ,  -1,0  ,  0,0  ,  1,0  ,  -1,1  ,  0,1  ,  1,1

sf::FloatRect rect[9]; // make function to get tiles positions around a rect

// loads an image, creates mask, return texture
sf::Texture load_image(std::string path) {
    sf::Image image;
    image.loadFromFile(path);
    image.createMaskFromColor(sf::Color::Black);
    sf::Texture texture;
    texture.loadFromImage(image);
    return texture;
}



std::vector<sf::Texture> load_images(std::string path) {
    // std::filesystem::path::make_preferred('/');
    std::vector<sf::Texture> vectexture;
    for (const auto& entry : std::filesystem::directory_iterator(BASE_IMAGE_PATH + path)) {
        if (entry.is_directory())    continue; // can skip diresctories push_back, commented to get constant exceptions and bad links
        std::string pathstr = (entry.path()).string();
        std::replace(pathstr.begin(), pathstr.end(), '\\', '/');

        // std::cout << pathstr << std::endl;
        vectexture.push_back(load_image(pathstr)); // gets texture form load_image pushed to vector

        //if (path == "particles/leaf/")
            //std::cout << pathstr << "\n";
    }

    return vectexture;
}

void setWindowPtr(sf::RenderWindow& windowptr)
{
    windowPointer = &windowptr;
}

sf::RenderWindow* getWindowPtr()
{
    return windowPointer;;
}


/// gives random number in a given range
int randrangeint(int min, int max)
{
    return   (rand() % max) + min;
}

float randrangefloat(float min, float max)
{
    float a = (float(rand()) / RAND_MAX) * (max - min)  + min;
    return a;
}

std::string getgridposString(int x, int y)
{
    std::string pos = std::to_string(x) + ";" + std::to_string(y);
    return pos;
}

std::string getgridposString(sf::Vector2i pos)
{
    std::string gpos = std::to_string(pos.x) + ";" + std::to_string(pos.y);
    return gpos;
}



sf::Vector2f screenShake(sf::Vector2f offset, float shakeRoughness)
{
    //screen_shake_offset = { randrangefloat(0,1), randrangefloat(0,1) };
    screen_shake_offset.x *= -1;
    screen_shake_offset.y *= -1;
    sf::Vector2f Offter = offset + screen_shake_offset * shakeRoughness;

    return Offter;
}

sf::Vector2i getStringtoVector2i(std::string pos)
{
    int i = 0;
    for ( i = 0; pos.size() - 1; i++) {
        if (pos[i] == ';')   break;
    }

    int x = stoi(pos.substr(0, i));
    int y = stoi(pos.substr(i + 1, pos.size() - 1));

    return sf::Vector2i(x, y);
}



sf::Vector2i getGridposCalculated(sf::Vector2f worldPos)
{
    int x = worldPos.x / 32;
    int y = worldPos.y / 32;
    if (worldPos.x < 0)	x--;
    if (worldPos.y < 0)	y--;

    return sf::Vector2i(x, y);
}

sf::Vector2i* getTilesAround(TileMap& tilemap, PhysicsEntity& entity) 
{
    sf::Vector2i entityPos = getGridposCalculated(entity.worldPos);
    for (int i = 0; i < 9; i++) {
        if (tilemap.ongridTileMap.contains(getgridposString(entityPos + TileOffsets[i]))) {
            char buffer[100];
            sprintf_s(buffer, "Tile type = %s", tilemap.ongridTileMap[getgridposString(entityPos + TileOffsets[i])].type.c_str());
            //appendToBuffer(buffer);
        }
        
    }
    
    return TileOffsets;
}


std::string& getMainBuffer() {
    return mainBuffer;
}

void appendToBuffer(std::string str) {
    mainBuffer += str;
}