#include "flowdatasource.h"


FlowDataSource::FlowDataSource()
{
    createData();
    //printValuesOfOrthogonalSlice(10);
}


void FlowDataSource::gen_tornado( int xs, int ys, int zs, int time, float *tornado )
/*
 *  Gen_Tornado creates a vector field of dimension [xs,ys,zs,3] from
 *  a proceedural function. By passing in different time arguements,
 *  a slightly different and rotating field is created.
 *
 *  The magnitude of the vector field is highest at some funnel shape
 *  and values range from 0.0 to around 0.4 (I think).
 *
 *  I just wrote these comments, 8 years after I wrote the function.
 *
 * Developed by Roger A. Crawfis, The Ohio State University
 *
 */
// Inputs:
// xs = x-Size (Anzahl der Elemente auf der x axis)
// ys = y-Size " (horizontal, orthogonal zu x)
// zs = z-Size " (vertikal, orthogonal zu x)
// time, der Zeitschritt in welchem der Tornado erzeugt wird
// tornado:
{
  float x, y, z;
  // indicies der jeweiligen Axis
  int ix, iy, iz;
  float r, xc, yc, scale, temp, z0;
  float r2 = 8;
  float SMALL = 0.00000000001;
  float xdelta = 1.0 / (xs-1.0);
  float ydelta = 1.0 / (ys-1.0);
  float zdelta = 1.0 / (zs-1.0);

  // iteritert über z (höhe) von ursprung bis max index
  for( iz = 0; iz < zs; iz++ )
  {
     z = iz * zdelta;                        // map z to 0->1
     xc = 0.5 + 0.1*sin(0.04*time+10.0*z);   // For each z-slice, determine the spiral circle.
     yc = 0.5 + 0.1*cos(0.03*time+3.0*z);    //    (xc,yc) determine the center of the circle.
     r = 0.1 + 0.4 * z*z + 0.1 * z * sin(8.0*z); //  The radius also changes at each z-slice.
     r2 = 0.2 + 0.1*z;                           //    r is the center radius, r2 is for damping
     // iteriert über die y axis vom ursprung bis max y
     for( iy = 0; iy < ys; iy++ )
     {
        y = iy * ydelta;
        // iteriert über die x axis vom ursprung bis max x
        for( ix = 0; ix < xs; ix++ )
        {
            x = ix * xdelta;
            temp = sqrt( (y-yc)*(y-yc) + (x-xc)*(x-xc) );
            scale = fabs( r - temp );
/*
 *  I do not like this next line. It produces a discontinuity
 *  in the magnitude. Fix it later.
 *
 */
           if ( scale > r2 )
              scale = 0.8 - scale;
           else
              scale = 1.0;
            z0 = 0.1 * (0.1 - temp*z );
           if ( z0 < 0.0 )  z0 = 0.0;
           temp = sqrt( temp*temp + z0*z0 );
            scale = (r + r2 - temp) * scale / (temp + SMALL);
            scale = scale / (1+z);

            // 3 aufeinander folgende Zellen erhalten die jeweiligen
            // Komponenten des Vectors im Gitterpunkt
           *(tornado++) = scale * (y-yc) + 0.1*(x-xc);
           *tornado++ = scale * -(x-xc) + 0.1*(y-yc);
           *tornado++ = scale * z0;
        }
     }
  }
}


void FlowDataSource::print_array(float arr[16*16*16*3])
{
    for (int i = 0; i < 16*16*16*3; i++){
        cout << arr[i] << ", ";
    }
    cout << "\n";
}


void FlowDataSource::createData()
{
    /**
     * Erzeugt ein Array, in welchem das kartesische Gitter gespeichert wird
    **/
    cartesianDataGrid = new float[xs*ys*zs*3];
    gen_tornado(xs, ys, zs, 0, cartesianDataGrid);
}


float FlowDataSource::getDataValue(int iz, int iy, int ix, int ic)
{
    // achtung falsch
    //int value_index = ic + 3*ix + xs*iy + ys*iz;
    int value_index = iz*ys*xs*cs + iy*xs*cs + ix*cs + ic;
    return cartesianDataGrid[value_index];
}


void FlowDataSource::printValuesOfOrthogonalSlice(int iz)
{
    for (int ix=0; ix < xs; ix ++)
    {
        for (int iy = 0; iy < ys; iy ++)
        {
            cout << "(";
            cout << getDataValue(iz, iy, ix, 0) << ",";
            cout << getDataValue(iz, iy, ix, 1) << ",";
            cout << getDataValue(iz, iy, ix, 2) << ",";
            cout << "),";
        }
    }
}


