#include "Cmd/Pov.h"

#include <iostream>

#include <algorithm>
#include "Compass.h"
#include "Position.h"

namespace jb
{

    Position CmdPov::translateRelative(int rightOffset, int forwardOffset) const
    {
        const int x = m_position.getX();
        const int y = m_position.getY();

        if (m_heading == NORTH)
        {
            return Position(x + rightOffset, y - forwardOffset);
        }
        else if (m_heading == SOUTH)
        {
            return Position(x - rightOffset, y + forwardOffset);
        }
        else if (m_heading == EAST)
        {
            return Position(x + forwardOffset, y + rightOffset);
        }
        else 
        {
            return Position(x - forwardOffset, y - rightOffset);
        }
    }

    CmdPov::RectangleBounds CmdPov::getRectangleBounds(int rightMin, int rightMax, int forwardMin, int forwardMax) const
    {
        const Position p1 = translateRelative(rightMin, forwardMin);
        const Position p2 = translateRelative(rightMin, forwardMax);
        const Position p3 = translateRelative(rightMax, forwardMin);
        const Position p4 = translateRelative(rightMax, forwardMax);

        const int minX = std::min({ p1.getX(), p2.getX(), p3.getX(), p4.getX() });
        const int maxX = std::max({ p1.getX(), p2.getX(), p3.getX(), p4.getX() });
        const int minY = std::min({ p1.getY(), p2.getY(), p3.getY(), p4.getY() });
        const int maxY = std::max({ p1.getY(), p2.getY(), p3.getY(), p4.getY() });

        return RectangleBounds(Position(minX, minY), Position(maxX + 1, maxY + 1));
    }

    WorldGrid::CharGrid CmdPov::getPov() const
    {
        switch (m_sensorType)
        {
        case SENSOR_A:
        default:
        {
            RectangleBounds bounds = getRectangleBounds(-1, 1, -1, 2);
            WorldGrid::CharGrid rect = m_grid.getRectangle(bounds.from, bounds.afterTo);
            WorldGrid::CharGrid pov;

            for (int forward = 2; forward >= -1; --forward)
            {
                WorldGrid::CharRow row;

                for (int right = -1; right <= 1; ++right)
                {
                    if (forward == 0 && right == 0)
                    {
                        row.push_back('X');
                    }
                    else
                    {
                        row.push_back(getCharFromRectangle(rect, bounds, right, forward));
                    }
                }

                pov.push_back(row);
            }

            return pov;
        }

        case SENSOR_B:
        {
            RectangleBounds bounds = getRectangleBounds(-2, 2, 1, 1);
            WorldGrid::CharGrid rect = m_grid.getRectangle(bounds.from, bounds.afterTo);
            WorldGrid::CharGrid pov;

            WorldGrid::CharRow frontRow;
            for (int right = -2; right <= 2; ++right)
            {
                frontRow.push_back(getCharFromRectangle(rect, bounds, right, 1));
            }
            pov.push_back(frontRow);

            WorldGrid::CharRow droneRow(5, ' ');
            droneRow[2] = 'X';
            pov.push_back(droneRow);

            return pov;
        }

        case SENSOR_C:
        {
            RectangleBounds bounds = getRectangleBounds(-2, 2, 1, 3);
            WorldGrid::CharGrid rect = m_grid.getRectangle(bounds.from, bounds.afterTo);
            WorldGrid::CharGrid pov;

            WorldGrid::CharRow farRow;
            for (int right = -2; right <= 2; ++right)
            {
                farRow.push_back(getCharFromRectangle(rect, bounds, right, 3));
            }
            pov.push_back(farRow);

            WorldGrid::CharRow middleRow(5, ' ');
            middleRow[1] = getCharFromRectangle(rect, bounds, -1, 2);
            middleRow[2] = getCharFromRectangle(rect, bounds, 0, 2);
            middleRow[3] = getCharFromRectangle(rect, bounds, 1, 2);
            pov.push_back(middleRow);

            WorldGrid::CharRow nearRow(5, ' ');
            nearRow[2] = getCharFromRectangle(rect, bounds, 0, 1);
            pov.push_back(nearRow);

            WorldGrid::CharRow droneRow(5, ' ');
            droneRow[2] = 'X';
            pov.push_back(droneRow);

            return pov;
        }
        }
    }

    char CmdPov::getCharFromRectangle(const WorldGrid::CharGrid& rect,
        const RectangleBounds& bounds,
        int rightOffset,
        int forwardOffset) const
    {
        Position target = translateRelative(rightOffset, forwardOffset);

        const int row = target.getY() - bounds.from.getY();
        const int col = target.getX() - bounds.from.getX();

        size_t droneId = 0;
        if (m_occupancy.getDroneAt(target, droneId))
        {
            return 'D';
        }

        return rect[row][col];
    }

    ExecuteResult CmdPov::execute(std::ostream& out) const
    {
        WorldGrid::CharGrid pov = getPov();

        for (const WorldGrid::CharRow& row : pov)
        {
            for (char ch : row)
            {
                out << ch;
            }
            out << '\n';
        }
        
        return { ExecuteStatus::Success };
    }

    unsigned int CmdPov::getEnergyConsumption() const  // changeeeee
    {
        switch (m_sensorType)
        {
        case SENSOR_A: return 30;
        case SENSOR_B: return 15;
        case SENSOR_C: return 50;
        default: return 15;
        }
    }

} // jb
