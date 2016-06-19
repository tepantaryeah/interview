#include <stdio.h>
#include <assert.h>
#include <vector>
using namespace std;
#define H_ARRAYSIZE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
    static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))
 
typedef struct  Triple1
{
    int triple[3];
}Triple;

typedef struct Point1{
    int x;
    int y;
    int source;
    Point1(int _x, int _y, int _source)
    {
        x = _x;
        y = _y;
        source = _source;
    }
}Point;

void help(vector <Point> &vPointList, vector <Triple> vTripleList, int x)
{
    vector <Point> vPointListTemp;
    for (int i = 0; i < vTripleList.size(); ++i)
    {
        if(x == vTripleList[i].triple[0] || x == vTripleList[i].triple[1])
        {
            if(0 == vPointListTemp.size())
            {
                for(int y=0; y<=vTripleList[i].triple[2]; y++)
                {
                    Point point(x, y, i);
                    vPointListTemp.push_back(point);
                }
            }
            else
            {
                for(int y=0; y<=vTripleList[i].triple[2]; y++)
                {
                    for(int j=0; j<vPointListTemp.size(); j++)
                    {
                        if(vPointListTemp[j].y >= y)
                            continue;
                    
                        Point point(x, y, i);
                        vPointListTemp.push_back(point);
                    }
                }
            }
        }
        else if(x>vTripleList[i].triple[0]  && x<vTripleList[i].triple[1])
        {
            for(int j=0; j<vPointListTemp.size(); )
            {
                if(vPointListTemp[j].y >= vTripleList[i].triple[2])
                {
                    j++;
                    continue;
                }
                if (vPointListTemp[j].source != i)
                {
                    vPointListTemp.erase(vPointListTemp[j]);
                }
                
            }
            if(vPointListTemp.size() == 0)
            {
                Point point(x, vTripleList[i].triple[2], i);
                vPointListTemp.push_back(point);
            }
        }
    }
    for(int i=0; i<vPointListTemp.size(); i++)
       vPointList.push_back(vPointListTemp[i]);
}

int resolve(const char* input)
{
    if(input == NULL || input[0] == '0')
    {
        return 0;
    }
    int count = input[0]-'0';
    input++;
    vector<Triple> tripleList;
    for (int i = 0; i < count; ++i)
    {
        if(*input == '\0')
            break;
        if(*input == '\n')
        {
            Triple temp;
            for(int j=0; j<3;)
            {
                if(*input == ',')
                    continue;
                temp.triple[j] = *input-'0';
                j++;
            }
            tripleList.push_back(temp);
        }

    }
    vector<Point> resultPath;
    Point path0(0,0,-1);
    resultPath.push_back(path0);
    for(int i=0; i<tripleList[count-1].triple[1]; i++)
    {
        help(resultPath, tripleList, i);
    }
    return resultPath.size()-1;
}

int main(int argc, char* argv[]) 
{
    const char* input[] = {
        "3\n1,3,2\n2,4,4\n6,7,5\n", //The giving example
        "1\n1,2,1\n",
        "2\n1,2,1\n2,3,2",
        "3\n1,2,1\n2,3,2\n3,6,1",
        "4\n1,2,1\n2,3,2\n3,6,1\n5,8,2",
        "5\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n7,9,1",
        "1\n0,1,1",
        "2\n0,1,1\n2,4,3",
        "3\n0,1,1\n2,4,3\n3,5,1",
        "4\n0,1,1\n2,4,3\n3,5,1\n5,6,1",
        "5\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n6,8,3",
        //TODO please add more test case here
        };
    printf("%s\n", input[0]);
    int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20};
    for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
    {
        assert(resolve(input[i]) == expectedSteps[i]);
    }
    
    return 0;
}
