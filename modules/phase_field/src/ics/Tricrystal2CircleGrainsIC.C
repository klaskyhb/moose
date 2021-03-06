/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "Tricrystal2CircleGrainsIC.h"
#include "MooseRandom.h"
#include "MooseMesh.h"

template<>
InputParameters validParams<Tricrystal2CircleGrainsIC>()
{
  InputParameters params = validParams<InitialCondition>();
  params.addClassDescription("Tricrystal with two circles/bubbles");
  params.addRequiredParam<unsigned int>("op_num", "Number of grain order parameters");
  params.addRequiredParam<unsigned int>("op_index", "Index for the current grain order parameter");
  return params;
}

Tricrystal2CircleGrainsIC::Tricrystal2CircleGrainsIC(const InputParameters & parameters) :
    InitialCondition(parameters),
    _mesh(_fe_problem.mesh()),
    _nl(_fe_problem.getNonlinearSystem()),
    _op_num(getParam<unsigned int>("op_num")),
    _op_index(getParam<unsigned int>("op_index"))
{
  if (_op_num != 3)
    mooseError("Tricrystal ICs must have op_num = 3");

  //Set up domain bounds with mesh tools
  for (unsigned int i = 0; i < LIBMESH_DIM; i++)
  {
    _bottom_left(i) = _mesh.getMinInDimension(i);
    _top_right(i) = _mesh.getMaxInDimension(i);
  }
  _range = _top_right - _bottom_left;
}

Real
Tricrystal2CircleGrainsIC::value(const Point & p)
{
  Point grain_center_left;
  grain_center_left(0) = _bottom_left(0) + _range(0)/4.0;
  grain_center_left(1) = _bottom_left(1) + _range(1)/2.0;
  grain_center_left(2) = _bottom_left(2) + _range(2)/2.0;

  Point grain_center_right;
  grain_center_right(0) = _bottom_left(0) + _range(0)*3.0/4.0;
  grain_center_right(1) = _bottom_left(1) + _range(1)/2.0;
  grain_center_right(2) = _bottom_left(2) + _range(2)/2.0;

  Real radius = _range(0)/5.0;
  Real dist_left = (p - grain_center_left).norm();
  Real dist_right = (p - grain_center_right).norm();

  if ((dist_left <= radius && _op_index == 1) || (dist_right <= radius && _op_index == 2) || (dist_left > radius && dist_right > radius && _op_index == 0))
    return 1.0;
  else
    return 0.0;
}

