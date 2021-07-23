#include "streamlinesmapper.h"

#include "horizontalslicetocontourmapper.h"
#include "flowdatasource.h"
#include <QVector3D>

StreamLinesMapper::StreamLinesMapper()
{
    // erzeugt eine Liste von Punkten für die Kontour Linien

}


void StreamLinesMapper::setDataSource(FlowDataSource *data_source)
{
    _data_source = data_source;
}



QVector3D StreamLinesMapper::interpolateWindVetor(QVector3D position){
    QVector3D interpolationVecor;
    position = position * 15.f;
    // Ursprung vom Cube in welchem sich position befindet.
    int x = (int) position.x();
    int y = (int) position.y();
    int z = (int) position.z();
    // delta innerhalb von Cube der jeweiligen Axen
    // x1 - x0 ist immer 1..
    float alphaX = position.x() - (float) x;
    float alphaY = position.y() - (float) y;
    float alphaZ = position.z() - (float) z;
    QVector3D v0, v1, v2, v3, v4, v5, v6, v7;
    if(x < 15 && y < 15 && z < 15){
        v0 = _data_source->getDataVector(z, y, x);
        v1 = _data_source->getDataVector(z, y, x+1);
        v2 = _data_source->getDataVector(z, y+1, x+1);
        v3 = _data_source->getDataVector(z, y+1, x);
        v4 = _data_source->getDataVector(z+1, y, x);
        v5 = _data_source->getDataVector(z+1, y, x+1);
        v6 = _data_source->getDataVector(z+1, y+1, x+1);
        v7 = _data_source->getDataVector(z+1, y+1, x);

        // TODO: schöner implementieren
        interpolationVecor = (
            ((1-alphaZ)*(
                (1-alphaY)*(
                    (1-alphaX)*v0 + alphaX*v1)
                +alphaY*(
                     (1-alphaX)*v3 + alphaX*v2
            ))) + (alphaZ * (
                (1-alphaY)*(
                    (1-alphaX)*v4 + alphaX*v5
                    ) + alphaY*((
                        (1-alphaX)*v7 + alphaX*v6
                    ))
                )
            )
        );
        return interpolationVecor;
    }

    // nicht innerhalb vom betrachteten Raum
    return QVector3D(-1, -1, -1);
}


QVector3D StreamLinesMapper::EulerIntegrate(QVector3D position, float stepSize){
    QVector3D newPoint;
    newPoint = position + stepSize * interpolateWindVetor(position);
    return newPoint;
}


QVector3D StreamLinesMapper::RKIntegrate(QVector3D position, float stepSize){
    QVector3D k1 = stepSize * interpolateWindVetor(position);
    QVector3D k2 = stepSize * interpolateWindVetor(position + k1/2.f);
    QVector3D k3 = stepSize * interpolateWindVetor(position + k2/2.f);
    QVector3D k4 = stepSize * interpolateWindVetor(position + k3);

    return position + k1/6.f + k2/3.f + k3/3.f + k4/6.f;
}


QVector<QVector3D> StreamLinesMapper::computeStreamlines(QVector<QVector3D> seedPoints, int time){
    _data_source->createData(time);

    QVector<QVector3D> streamLines;

    for(int i=0; i < seedPoints.size(); i++){
        QVector3D tmpLast = seedPoints[i];

        // TODO parameter num iterations?
        for(int j=0; j<200; j++){
            //QVector3D tmpNow = EulerIntegrate(tmpLast, -0.2f);
            QVector3D tmpNow = RKIntegrate(tmpLast, -0.2f);

            if(tmpNow.x() <= 1.f && tmpNow.x() >= 0.f && tmpNow.y() <= 1.f && tmpNow.y() >= 0.f && tmpNow.z() <= 1.f && tmpNow.z() >= 0.f){
                streamLines.append(tmpLast);
                streamLines.append(tmpNow);
                tmpLast = tmpNow;
            }
            else{
                break;
            }
        }
    }
    return streamLines;
}




