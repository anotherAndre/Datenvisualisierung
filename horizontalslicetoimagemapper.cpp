#include "horizontalslicetoimagemapper.h"
#include "flowdatasource.h"

HorizontalSliceToImageMapper::HorizontalSliceToImageMapper()
{

}


void HorizontalSliceToImageMapper::setDataSource(FlowDataSource *data_source)
{
    _data_source = data_source;
}


QImage HorizontalSliceToImageMapper::mapSliceToImage(int iz)
{
    // initialisierung von irgendeinem QImage mit den ausmaßen dataSource->xs und dataSource-ys
    QImage image(xs, ys, QImage::Format_RGB32);
    int red, green, blue;

    for (int ix=0; ix < xs; ix ++)
    {
        for (int iy = 0; iy < ys; iy ++)
        {
            int xWind = _data_source->getDataValue(iz, iy, ix, 0);
            //getDataValue(iz, iy, ix, 1)
            //getDataValue(iz, iy, ix, 2)
            green = 0;
            if (xWind > 0)
            {
                red = xWind*3*255;
                blue = 0;
            }
            else
            {
                blue = -1*xWind*3*255;
                red = 0;
            }

            image.setPixelColor(ix, iy, QColor(red, green, blue, 255));
        }
    }
    return image;
}
