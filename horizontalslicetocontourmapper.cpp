#include "horizontalslicetocontourmapper.h"
#include "flowdatasource.h"
#include <QVector3D>

horizontalSliceToContourMapper::horizontalSliceToContourMapper()
{
    // erzeugt eine Liste von Punkten für die Kontour Linien

}


void horizontalSliceToContourMapper::setDataSource(FlowDataSource *data_source)
{
    _data_source = data_source;
}


QVector3D horizontalSliceToContourMapper::getIntersection(int x1, int y1, int x2, int y2, int iz, float c){
    float a = _data_source->getDataValue(iz, y1, x1, 0);
    float b = _data_source->getDataValue(iz, y2, x2, 0);

    float alpha = (c - a) / (b - a);
//    if(alpha > 1.f/15.f){
//        alpha = 1.f/15.f;}
//        //return QVector3D(0,0,0);}
//    if(alpha < -1./15.f){
//        alpha = -1.f/15.f;}
        //return QVector3D(0,0,0);}

    float x = x1 + alpha * (x2 - x1);
    float y = y1 + alpha * (y2 - y1);

//    alpha = 0.5;

//    float x = ((1-alpha) * x1) + (alpha * x2);
//    float y = ((1-alpha) * y1) + (alpha * y2);

    //return QVector3D((x*2.f+1.f)/32.f, (y*2.f+1.f)/32.f, iz/15.f + 0.001);
    return QVector3D(x/15.f, y/15.f, iz/15.f+0.001);
}


QVector<QVector3D> horizontalSliceToContourMapper::mapSliceToContour(int time, int iz, float c)
{
    /* Mappt die Werte vom horizontalen Slice auf ihre Kontourlinien
     * time: Tornado generation Zeitpunkt
     * iz: z Koordinate vom Slice
     * c: Schwellwert für die Contourlinie
     */

    _data_source->createData(time);

    QVector<QVector3D> lines;

    //bool topLeft, topRight, bottomLeft, bottomRight = false;
    unsigned int configuration = 0;

    for(int ix=0; ix < xs -1; ix++){
        for(int iy=0; iy < ys -1; iy++){
            // bestimme den state der Zelle
            //topLeft = _data_source->getDataValue(iz, iy+1, ix, 0) >= c ? true : false;
            //topRight = _data_source->getDataValue(iz, iy+1, ix+1, 0) >= c ? true : false;
            //bottomLeft = _data_source->getDataValue(iz, iy, ix, 0) >= c ? true : false;
            // bottomRight = _data_source->getDataValue(iz, iy, ix+1, 0) >= c ? true : false;
            configuration = 0;
            // V0
            configuration |= _data_source->getDataValue(iz, iy, ix, 0) >= c ? 1 : 0;
            // V1
            configuration |= _data_source->getDataValue(iz, iy, ix+1, 0) >= c ? 2 : 0;
            // V2
            configuration |= _data_source->getDataValue(iz, iy+1, ix+1, 0) >= c ? 4 : 0;
            // V3
            configuration |= _data_source->getDataValue(iz, iy+1, ix, 0) >= c ? 8 : 0;

            configuration = configuration > 7 ? 15 - configuration : configuration;
            //configuration = 15 - configuration;

            // 0000 oder 1111
            if(configuration == 0){
                continue;
            }
            // 0001 oder 1110
            else if(configuration == 1)
            {
                // Schnittpunkt links und unten berechnen
                lines.append(getIntersection(ix, iy, ix, iy+1, iz, c));
                lines.append(getIntersection(ix, iy, ix+1, iy, iz, c));
            }
            // 0010 oder 1101
            else if(configuration == 2){
                // Schnittpunkt rehts und unten berechnen
                lines.append(getIntersection(ix+1, iy, ix+1, iy+1, iz, c));
                lines.append(getIntersection(ix, iy, ix+1, iy, iz, c));
            }
            // 0011 oder 1100
            else if(configuration == 3){
                // Schnittpunkt links und rechts berechnen
                lines.append(getIntersection(ix, iy, ix, iy+1, iz, c));
                lines.append(getIntersection(ix+1, iy, ix+1, iy+1, iz, c));
            }
            // 0100 oder 1011
            else if(configuration == 4){
                // Schnittpunkt oben und rechts berechnen
                lines.append(getIntersection(ix, iy+1, ix+1, iy+1, iz, c));
                lines.append(getIntersection(ix+1, iy, ix+1, iy+1, iz, c));
            }
            // 0101 oder 1010
            else if(configuration == 5){
                // Ambiguität auflösen
                // midpoint decider
                // ist midpoint über Iso?
                // TODO ggf. akkurateren decider implementieren
                bool midpointAboveIso = 0.25f*(
                    _data_source->getDataValue(iz, iy, ix, 0)
                    + _data_source->getDataValue(iz, iy, ix+1, 0)
                    + _data_source->getDataValue(iz, iy+1, ix+1, 0)
                    + _data_source->getDataValue(iz, iy+1, ix, 0)
                ) >= c;

                if(midpointAboveIso){
                    // Schnittpunkt oben und rechts berechnen
                    lines.append(getIntersection(ix, iy+1, ix+1, iy+1, iz, c));
                    lines.append(getIntersection(ix+1, iy, ix+1, iy+1, iz, c));

                    // Schnittpunkt links und unten berechnen
                    lines.append(getIntersection(ix, iy, ix, iy+1, iz, c));
                    lines.append(getIntersection(ix, iy, ix+1, iy, iz, c));
                }
                else{
                    // Schnittpunkt links und oben berechnen
                    lines.append(getIntersection(ix, iy, ix, iy+1, iz, c));
                    lines.append(getIntersection(ix, iy+1, ix+1, iy+1, iz, c));

                    // Schnittpunkt rehts und unten berechnen
                    lines.append(getIntersection(ix+1, iy, ix+1, iy+1, iz, c));
                    lines.append(getIntersection(ix, iy, ix+1, iy, iz, c));
                }
            }
            // 0110 oder 1001
            else if(configuration == 6){
                // Schnittpunkt oben und unten berechnen
                lines.append(getIntersection(ix, iy+1, ix+1, iy+1, iz, c));
                lines.append(getIntersection(ix, iy, ix+1, iy, iz, c));
            }
            // 0111 oder 1000
            else if(configuration == 7){
                // Schnittpunkt links und oben berechnen
                lines.append(getIntersection(ix, iy, ix, iy+1, iz, c));
                lines.append(getIntersection(ix, iy+1, ix+1, iy+1, iz, c));
            }
        }

    }
    return lines;
}
