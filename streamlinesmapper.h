#ifndef HORIZONTALSLICETOCONTOURMAPPER_H
#define HORIZONTALSLICETOCONTOURMAPPER_H

#include <QImage>
#include "flowdatasource.h"

class StreamLinesMapper
{
    FlowDataSource *_data_source;

    int xs = 16;
    int ys = 16;
    int zs = 16;
    int cs = 3;
public:
    StreamLinesMapper();
    void setDataSource(FlowDataSource *data_source);
    QVector<QVector3D> mapSliceToContour(int time, int iz, float c);
    QVector3D getIntersection(int x1, int y1, int x2, int y2, int iz, float c);
    QVector3D interpolateWindVetor(QVector3D position);
};

#endif // HORIZONTALSLICETOCONTOURMAPPER_H
