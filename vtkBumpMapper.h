/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkBumpMapper.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkBumpMapper - copy oriented and scaled glyph geometry to every input point
// .SECTION Description
// vtkBumpMapper is a filter that copies a geometric representation (called
// a glyph) to every point in the input dataset. The glyph is defined with
// polygonal data from a source filter input. The glyph may be oriented
// along the input vectors or normals, and it may be scaled according to
// scalar data or vector magnitude. More than one glyph may be used by
// creating a table of source objects, each defining a different glyph. If a
// table of glyphs is defined, then the table can be indexed into by using
// either scalar value or vector magnitude.
//
// To use this object you'll have to provide an input dataset and a source
// to define the glyph. Then decide whether you want to scale the glyph and
// how to scale the glyph (using scalar value or vector magnitude). Next
// decide whether you want to orient the glyph, and whether to use the
// vector data or normal data to orient it. Finally, decide whether to use a
// table of glyphs, or just a single glyph. If you use a table of glyphs,
// you'll have to decide whether to index into it with scalar value or with
// vector magnitude.
//
// .SECTION Caveats
// The scaling of the glyphs is controlled by the ScaleFactor ivar multiplied
// by the scalar value at each point (if VTK_SCALE_BY_SCALAR is set), or
// multiplied by the vector magnitude (if VTK_SCALE_BY_VECTOR is set),
// Alternatively (if VTK_SCALE_BY_VECTORCOMPONENTS is set), the scaling
// may be specified for x,y,z using the vector components. The
// scale factor can be further controlled by enabling clamping using the
// Clamping ivar. If clamping is enabled, the scale is normalized by the
// Range ivar, and then multiplied by the scale factor. The normalization
// process includes clamping the scale value between (0,1).
//
// Typically this object operates on input data with scalar and/or vector
// data. However, scalar and/or vector aren't necessary, and it can be used
// to copy data from a single source to each point. In this case the scale
// factor can be used to uniformly scale the glyphs.
//
// The object uses "vector" data to scale glyphs, orient glyphs, and/or index
// into a table of glyphs. You can choose to use either the vector or normal
// data at each input point. Use the method SetVectorModeToUseVector() to use
// the vector input data, and SetVectorModeToUseNormal() to use the
// normal input data.
//
// If you do use a table of glyphs, make sure to set the Range ivar to make
// sure the index into the glyph table is computed correctly.
//
// You can turn off scaling of the glyphs completely by using the Scaling
// ivar. You can also turn off scaling due to data (either vector or scalar)
// by using the SetScaleModeToDataScalingOff() method.
//
// You can set what arrays to use for the scalars, vectors, normals, and
// color scalars by using the SetInputArrayToProcess methods in
// vtkAlgorithm. The first array is scalars, the next vectors, the next
// normals and finally color scalars.

// .SECTION See Also
// vtkTensorGlyph

#ifndef __vtkBumpMapper_h
#define __vtkBumpMapper_h

#include "vtkFiltersCoreModule.h" // For export macro
#include "vtkPolyDataAlgorithm.h"

#define VTK_SCALE_BY_SCALAR 0
#define VTK_SCALE_BY_VECTOR 1
#define VTK_SCALE_BY_VECTORCOMPONENTS 2
#define VTK_DATA_SCALING_OFF 3

#define VTK_COLOR_BY_SCALE  0
#define VTK_COLOR_BY_SCALAR 1
#define VTK_COLOR_BY_VECTOR 2

#define VTK_USE_VECTOR 0
#define VTK_USE_NORMAL 1
#define VTK_VECTOR_ROTATION_OFF 2

#define VTK_INDEXING_OFF 0
#define VTK_INDEXING_BY_SCALAR 1
#define VTK_INDEXING_BY_VECTOR 2

class vtkTransform;

class VTK_EXPORT vtkBumpMapper : public vtkPolyDataAlgorithm
{
public:
  vtkTypeMacro(vtkBumpMapper,vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);
  static vtkBumpMapper *New();

  vtkSetMacro(CurrentIntegrationTime,double);
  vtkGetMacro(CurrentIntegrationTime,double);

protected:
  vtkBumpMapper();
  ~vtkBumpMapper();
  virtual int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

  double CurrentIntegrationTime;

private:
    void BoundPoints(vtkIdType, vtkIdType*, vtkDoubleArray*, vtkIdType *);
    void WeightedAverage2Points(vtkIdType*, vtkPolyData*, double*);
};

#endif




