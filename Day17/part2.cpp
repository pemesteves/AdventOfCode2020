#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Point
{
    int x, y, z, w;

public:
    Point(int x, int y, int z, int w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
    Point(const Point &p)
    {
        this->x = p.getX();
        this->y = p.getY();
        this->z = p.getZ();
        this->w = p.getW();
    }

    int getX() const { return x; }
    int getY() const { return y; }
    int getZ() const { return z; }
    int getW() const { return w; }

    bool operator==(const Point &rhs) const
    {
        return this->x == rhs.getX() 
            && this->y == rhs.getY() 
            && this->z == rhs.getZ() 
            && this->w == rhs.getW();
    }
};

namespace std
{
    template <>
    struct hash<Point>
    {
        size_t
        operator()(const Point &obj) const
        {
            return hash<int>()(obj.getX() * obj.getY() * obj.getZ() * obj.getW());
        }
    };
} // namespace std

vector<vector<int>> offsets = {
    {-1, 0, 0, 0},
    {1, 0, 0, 0},
    {0, -1, 0, 0},
    {0, 1, 0, 0},
    {0, 0, -1, 0},
    {0, 0, 1, 0},
    {0, 0, 0, -1},
    {0, 0, 0, 1},

    {-1, -1, 0, 0},
    {-1, 1, 0, 0},
    {1, -1, 0, 0},
    {1, 1, 0, 0},
    
    {-1, 0, -1, 0},
    {-1, 0, 1, 0},
    {1, 0, -1, 0},
    {1, 0, 1, 0},
    
    {-1, 0, 0, -1},
    {-1, 0, 0, 1},
    {1, 0, 0, -1},
    {1, 0, 0, 1},
    
    {0, -1, -1, 0},
    {0, -1, 1, 0},
    {0, 1, -1, 0},
    {0, 1, 1, 0},
    
    {0, -1, 0, -1},
    {0, -1, 0, 1},
    {0, 1, 0, -1},
    {0, 1, 0, 1},
    
    {0, 0, -1, -1},
    {0, 0, -1, 1},
    {0, 0, 1, -1},
    {0, 0, 1, 1},
    
    {-1, -1, -1, 0},
    {-1, -1, 1, 0},
    {-1, 1, -1, 0},
    {-1, 1, 1, 0},
    {1, -1, -1, 0},
    {1, -1, 1, 0},
    {1, 1, -1, 0},
    {1, 1, 1, 0},

    {-1, -1, 0, -1},
    {-1, -1, 0, 1},
    {-1, 1, 0, -1},
    {-1, 1, 0, 1},
    {1, -1, 0, -1},
    {1, -1, 0, 1},
    {1, 1, 0, -1},
    {1, 1, 0, 1},
    
    {-1, 0, -1, -1},
    {-1, 0, -1, 1},
    {-1, 0, 1, -1},
    {-1, 0, 1, 1},
    {1, 0, -1, -1},
    {1, 0, -1, 1},
    {1, 0, 1, -1},
    {1, 0, 1, 1},
    
    {0, -1, -1, -1},
    {0, -1, -1, 1},
    {0, -1, 1, -1},
    {0, -1, 1, 1},
    {0, 1, -1, -1},
    {0, 1, -1, 1},
    {0, 1, 1, -1},
    {0, 1, 1, 1},
    
    {-1, -1, -1, -1},
    {-1, -1, -1, 1},
    {-1, -1, 1, -1},
    {-1, -1, 1, 1},
    {-1, 1, -1, -1},
    {-1, 1, -1, 1},
    {-1, 1, 1, -1},
    {-1, 1, 1, 1},
    {1, -1, -1, -1},
    {1, -1, -1, 1},
    {1, -1, 1, -1},
    {1, -1, 1, 1},
    {1, 1, -1, -1},
    {1, 1, -1, 1},
    {1, 1, 1, -1},
    {1, 1, 1, 1},
};

void addPoint(unordered_set<Point> points, unordered_set<Point> &tmp, Point &p)
{
    if (tmp.find(p) == tmp.end())
    {
        char isActive = points.find(p) == points.end() ? false : true;

        int numActNei = 0;

        for(size_t j = 0; j < offsets.size(); j++) {
            if (points.find(Point(p.getX() + offsets[j][0], p.getY() + offsets[j][1], p.getZ() + offsets[j][2], p.getW() + offsets[j][3])) 
                != points.end())
                numActNei++;
            if (numActNei > 3)
                return;
        }
    
        if (isActive && (numActNei == 2 || numActNei == 3))
        {
            tmp.insert(p);
        }
        else if (!isActive && numActNei == 3)
        {
            tmp.insert(p);
        }
    }
}

int main()
{
    ifstream f;
    f.open("input.txt");

    string line;

    int z = 0;
    int w = 0;
    int y = 0;

    unordered_set<Point> points;

    while (!f.eof())
    {
        getline(f, line);

        for (int x = 0; x < line.length(); x++)
        {
            if (line[x] == '#')
                points.insert(Point(x, y, z, w));
        }

        y++;
    }

    f.close();

    for (int i = 0; i < 6; i++)
    {
        unordered_set<Point> tmp;

        for (auto it = points.begin(); it != points.end(); it++)
        {
            int x = it->getX(), y = it->getY(), z = it->getZ(), w = it->getW();

            for(size_t j = 0; j < offsets.size(); j++) {
                Point p(x + offsets[j][0], y + offsets[j][1], z + offsets[j][2], w + offsets[j][3]);
                addPoint(points, tmp, p);
            }
        }

        points = tmp;
    }

    cout << points.size() << endl;

    return 0;
}