#ifndef HORIZONTALSLICETOCONTOURMAPPER_H
#define HORIZONTALSLICETOCONTOURMAPPER_H

#include <QImage>
#include "flowdatasource.h"

class horizontalSliceToContourMapper
{
    FlowDataSource *_data_source;

    int xs = 16;
    int ys = 16;
    int zs = 16;
    int cs = 3;
public:
    horizontalSliceToContourMapper();
    void setDataSource(FlowDataSource *data_source);
    QVector<QVector3D> mapSliceToContour(int time, int iz, float c);
    QVector3D getIntersection(int x1, int y1, int x2, int y2, int iz, float c);
};

#endif // HORIZONTALSLICETOCONTOURMAPPER_H
