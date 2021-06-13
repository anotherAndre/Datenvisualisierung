#include "horizontalslicetoimagemapper.h"
#include "flowdatasource.h"

HorizontalSliceToImageMapper::HorizontalSliceToImageMapper()
{

}


void HorizontalSliceToImageMapper::setDataSource(FlowDataSource *data_source)
{
    _data_source = data_source;
}


QImage HorizontalSliceToImageMapper::mapSliceToImage(int time, int iz)
{
    // initialisierung von irgendeinem QImage mit den ausmaßen dataSource->xs und dataSource-ys
    //_data_source->createData();

    QImage image = QImage(16, 16, QImage::Format_RGB32);
    if(image.isNull())
        std::cout << "Image in mapSliceToImage is Null";

    for (int ix=0; ix < 16; ix ++)
    {
        for (int iy = 0; iy < 16; iy ++)
        {
            int xWindColorValue = _data_source->getDataValue(iz, iy, ix, 0) *3*255;
            //int xWindColorValue = 100;
            //getDataValue(iz, iy, ix, 1)
            //getDataValue(iz, iy, ix, 2)
            QColor color;
            if (xWindColorValue < 0)
            {
                color.setRgb(0, 0, (int)-xWindColorValue);
            }
            else
            {
                color.setRgb((int)xWindColorValue, 0, 0);
            }

            image.setPixelColor(ix, iy, color);
        }
    }
    return image;
}
