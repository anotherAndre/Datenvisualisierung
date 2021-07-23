#ifndef FLOWDATASOURCE_H
#define FLOWDATASOURCE_H

#include <QCoreApplication>
#include <math.h>
#include <iostream>

using namespace std;


class FlowDataSource
{
    float *cartesianDataGrid;

    void print_array(float arr[16*16*16*3]);

private:
    int last_time = -1;
public:
//    int xs = 16;
//    int ys = 16;
//    int zs = 16;
//    int cs = 3;
    FlowDataSource();
    void gen_tornado( int xs, int ys, int zs, int time, float *tornado );
    void createData(int time);
    float getDataValue(int iz, int iy, int ix, int ic);
    QVector3D getDataVector(int iz, int iy, int ix);
    void printValuesOfOrthogonalSlice(int iz);
};

#endif // FLOWDATASOURCE_H
