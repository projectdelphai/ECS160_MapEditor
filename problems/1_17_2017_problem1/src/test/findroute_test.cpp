#include "gtest/gtest.h"
#include "findroute.h"

// Maps are oversized by 2 in each dimension to provide non-traversable border
// X =non-traversable border
// T =tree (non-traversable)
// Space =traversable path
std::vector<std::vector<char > > TestMap {
    { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
    { 'X', ' ', ' ', ' ', ' ', ' ', ' ', 'X' },
    { 'X', ' ', 'T', 'T', 'T', ' ', ' ', 'X' },
    { 'X', ' ', 'T', ' ', 'T', 'T', 'T', 'X' },
    { 'X', ' ', 'T', 'T', ' ', ' ', ' ', 'X' },
    { 'X', ' ', ' ', 'T', 'T', 'T', ' ', 'X' },
    { 'X', ' ', ' ', ' ', ' ', ' ', ' ', 'X' },
    { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' }
};

void PrintTo(CRouteFinder::EDirection direction, ::std::ostream* os){
    switch (direction){
        case CRouteFinder::EDirection::North:       *os << "N"; 
                                                    break;
        case CRouteFinder::EDirection::NorthEast:   *os << "NE"; 
                                                    break;
        case CRouteFinder::EDirection::East:        *os << "E"; 
                                                    break;
        case CRouteFinder::EDirection::SouthEast:   *os << "SE"; 
                                                    break;
        case CRouteFinder::EDirection::South:       *os << "S"; 
                                                    break;
        case CRouteFinder::EDirection::SouthWest:   *os << "SW"; 
                                                    break;
        case CRouteFinder::EDirection::West:        *os << "W"; 
                                                    break;
        case CRouteFinder::EDirection::NorthWest:   *os << "NW"; 
                                                    break;
        case CRouteFinder::EDirection::Max:         *os << "Max"; 
                                                    break;
    }
}

TEST(RouteFinder, IsTraversableTest) {
    CRouteFinder TestMapRouteFinder(TestMap);
    EXPECT_EQ(false, TestMapRouteFinder.IsTraversable(1, 1));
    EXPECT_EQ(false, TestMapRouteFinder.IsTraversable(-1, 1));
    EXPECT_EQ(false, TestMapRouteFinder.IsTraversable(1, -1));
    EXPECT_EQ(true, TestMapRouteFinder.IsTraversable(4, 3));
    EXPECT_EQ(true, TestMapRouteFinder.IsTraversable(0, 0));

}

TEST(RouteFinder, FindRouteTest) {
    CRouteFinder TestMapRouteFinder(TestMap);

    // move right
    EXPECT_EQ(CRouteFinder::EDirection::East , TestMapRouteFinder.FindRoute(3, 3, 4, 3));
    EXPECT_EQ(CRouteFinder::EDirection::East , TestMapRouteFinder.FindRoute(4, 3, 5, 3));
    EXPECT_EQ(CRouteFinder::EDirection::SouthEast , TestMapRouteFinder.FindRoute(4, 3, 5, 4));
    EXPECT_EQ(CRouteFinder::EDirection::SouthWest , TestMapRouteFinder.FindRoute(5, 4, 4, 5));

}
