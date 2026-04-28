#ifndef __WorldGrid_h__
#define __WorldGrid_h__

#include <array>
#include <istream>
#include <vector>
#include "Position.h"
#include "WorldOccupancy.h"
namespace jb
{

    class Tile;
    class Position;
    class Compass;

    class WorldGrid
    {
    public:

        WorldGrid();
        explicit WorldGrid(std::istream& input);

        using Row = std::vector< Tile*>;
        using Grid = std::vector<Row>;

        using CharRow = std::vector<char>;
        using CharGrid = std::vector<CharRow>;

        CharGrid getRectangle(const Position& from, const Position& afterTo) const;
        Tile& getTile(int x, int y) const;
        char getCharAt(int x, int y) const;
        size_t getRowSize() const;
        size_t getNumRows() const;
        void printMap(std::ostream& out, const WorldOccupancy& occupancy, size_t selfId) const;
       
        class const_iterator
        {
        public:
            const_iterator(const WorldGrid& world, const Position& from, const Position& afterTo);

            const Tile& operator*() const;
            const_iterator& operator++();
            bool operator!=(const const_iterator& other) const;
            bool operator==(const const_iterator& other) const;

        private:

            friend class WorldGrid;

            const WorldGrid& m_world;
            Position m_current;
            Position m_from;
            Position m_afterTo;
        };

        const_iterator begin(const Position& from, const Position& afterTo) const;
        const_iterator end(const Position& from, const Position& afterTo) const;

    private:

        void loadDefaultMap();
        void loadFromStream(std::istream& input);
        void initializeAsEmpty(std::size_t width, std::size_t height);
        static char tileToChar(const Tile& tile);

        Grid m_grid;
        std::size_t m_rowSize;
        std::size_t m_numRows;
    };

} 

#endif