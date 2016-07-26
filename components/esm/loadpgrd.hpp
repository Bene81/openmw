#ifndef OPENMW_ESM_PGRD_H
#define OPENMW_ESM_PGRD_H

#include <string>
#include <vector>

namespace ESM
{

class ESMReader;
class ESMWriter;

/*
 * Path grid.
 */
struct Pathgrid
{
    static unsigned int sRecordId;
    /// Return a string descriptor for this record type. Currently used for debugging / error logs only.
    static std::string getRecordType() { return "Pathgrid"; }

    struct DATAstruct
    {
        int mX, mY; // Grid location, matches cell for exterior cells
        short mS1; // ?? Usually but not always a power of 2. Doesn't seem
                  // to have any relation to the size of PGRC.
        short mS2; // Number of path points.
    }; // 12 bytes

    struct Point // path grid point
    {
        int mX, mY, mZ; // Location of point
        unsigned char mAutogenerated; // autogenerated vs. user coloring flag?
        unsigned char mConnectionNum; // number of connections for this point
        short mUnknown;
        Point& operator=(const float[3]);
        Point(const float[3]);
        Point();
        Point(int x, int y, int z) : mX(x), mY(y), mZ(z) {}
    }; // 16 bytes

    struct Edge // path grid edge
    {
        int mV0, mV1; // index of points connected with this edge
    }; // 8 bytes

    std::string mCell; // Cell name
    DATAstruct mData;

    typedef std::vector<Point> PointList;
    PointList mPoints;

    typedef std::vector<Edge> EdgeList;
    EdgeList mEdges;

    void load(ESMReader &esm, bool &isDeleted);
    void save(ESMWriter &esm, bool isDeleted = false) const;

    void blank();
};
}
#endif
