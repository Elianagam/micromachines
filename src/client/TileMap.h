#ifndef MICROMACHINES_TILEMAP_H
#define MICROMACHINES_TILEMAP_H

#include "Tile.h"
#include "Entity.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
//TODO: Falta pista recta en | |

#define TILE_1 "../media/tiles/01_Road.png"
#define TILE_2 "../media/tiles/02_Road.png"
#define TILE_3 "../media/tiles/03_Road.png"
#define TILE_4 "../media/tiles/04_Road.png"
#define TILE_5 "../media/tiles/05_Road.png"
#define TILE_6 "../media/tiles/06_Road.png"
#define TILE_7 "../media/tiles/07_Road.png"
#define TILE_8 "../media/tiles/08_Road.png"
#define GRASS_TILE "../media/tiles/Grass_Tile.png"

// De qué forma queremos que la muestre

#define TILE_HEIGHT 33.05
#define TILE_WIDTH 33.05

class TileMap: public Entity{
    private:
        std::vector<Tile> tiles;
        Window& window;

    public:
        TileMap(Window& window,
                const std::string& mapFile,
                int zoom,
                int offset);
        void render(Camera& cam);
        ~TileMap();
};

#endif
