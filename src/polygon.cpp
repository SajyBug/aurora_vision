
/* 
 * @File:     polygon.cpp
 * @Author:   Sajjad Rahnama , Hossein Hojat Ansari
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created  2016
 */

#include "polygon.h"

Polygon::Polygon()
{
  this->triangle = Triangle();
  this->square = Square();
  this->star = Star();
  this->circle = Circle();
  this->pentagon = Pentagon();
  this->heart = Heart();
  this->h_shape = H_shape();
  this->chess_shape = Chess_shape();
}

Triangle Polygon::getTriangle()
{
  return this->triangle;
}

Square Polygon::getSquare()
{
  return this->square;
}

Star Polygon::getStar()
{
  return this->star;
}

Circle Polygon::getCircle()
{
  return this->circle;
}

Pentagon Polygon::getPentagon()
{
  return this->pentagon;
}

Heart Polygon::getHeart()
{
  return this->heart;
}

H_shape Polygon::getH_shape()
{
  return this->h_shape;
}

Chess_shape Polygon::getChess_shape()
{
  return this->chess_shape;
}
