#ifndef HORIZONTALSLICETOIMAGEMAPPER_H
#define HORIZONTALSLICETOIMAGEMAPPER_H

#include <QImage>
#include "flowdatasource.h"


class HorizontalSliceToImageMapper
{
    FlowDataSource *_data_source;

    int xs = 16;
    int ys = 16;
    int zs = 16;
    int cs = 3;
public:
    HorizontalSliceToImageMapper();
    void setDataSource(FlowDataSource *data_source);
    QImage mapSliceToImage(int time, int iz);
};

#endif // HORIZONTALSLICETOIMAGEMAPPER_H
