//#include "WorldWide.h"
//#include "Position.h"
//WorldGrid w;
//
////const const_iterator begin(const Position& start);
////const const_iterator end(const Position& end);
//
//Position from(2, 1);
//Position afterTo(6, 5);
//WorldGrid::const_iterator itr = w.begin(from);
//WorldGrid::const_iterator end = w.end(afterTo);
//
//for (; itr != end; ++itr)
//{
//    const Tile& tile = *itr;
//}
//
//
////0123456789ABCDEFG
////0 ### #####E#######
////1 # # #####   ###
////2 #    ##      #  #
////3 ##             ##
////4 #################
//
//void checkBeginZeroIdxGridCell(const WorldGrid & w)
//{
//    const Tile& t = w.begin(Position{ 0,0 });
//    assert(*t == WALL);
//}
//
//void checkBeginForMiddleCell(const WorldGrid & w)
//{
//    const Tile& t = w.begin(Position{ 3,1 });
//    assert(*t == EMPTY);
//    const Tile& t = w.begin(Position{ 9,0 });
//    assert(*t == EXIT);
//    const Tile& t = w.begin(Position{ 5,2 });
//    assert(*t == WALL);
//}
//
//void checkOutOfBounds(const WorldGrid & w)
//{
//    const Tile& t = w.begin(Position{ -1,1 });
//    assert(*t == WALL);
//}
//
//int main()
//{
//    const WorldGrid w("tests.map");
//    checkBeginZeroIdxGridCell(w);
//    checkBeginForMiddleCell(w);
//    checkOutOfBounds(w);
//}