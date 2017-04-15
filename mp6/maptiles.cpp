/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

 #include <iostream>
 #include <map>
 #include "maptiles.h"

 using namespace std;

 MosaicCanvas* mapTiles(SourceImage const& theSource, vector<TileImage> const& theTiles)
 {
     /**
      * @todo Implement this function!
      */
    vector< Point<3> > colors;
    int rows = theSource.getRows();
    int columns = theSource.getColumns();
 		MosaicCanvas* canvas = new MosaicCanvas(rows, columns);
 	  map<Point<3>, TileImage> tiles;
    Point<3> point;
    RGBAPixel pixel;

    for(size_t i = 0; i<theTiles.size(); i++ ){
 		   pixel = theTiles[i].getAverageColor();
 		   point = Point<3>(pixel.red, pixel.green, pixel.blue);
 		   colors.push_back(point);
 		   tiles[point] = theTiles[i];
 	   }

 	   KDTree<3> tree(colors);

     for(int i = 0; i<rows; i++){
 		     for(int j = 0; j<columns; j++){
 			       pixel = theSource.getRegionColor(i,j);
 			       point = Point<3>(pixel.red, pixel.green, pixel.blue);
 			       point = tree.findNearestNeighbor(point);
 			       canvas->setTile(i, j, tiles[point]);
 		      }
 	     }
 	    return canvas;
 }
