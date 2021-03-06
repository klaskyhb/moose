/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

// MOOSE includes
#include "NumElems.h"
#include "SubProblem.h"
#include "MooseMesh.h"

template<>
InputParameters validParams<NumElems>()
{
  InputParameters params = validParams<GeneralPostprocessor>();
  return params;
}

NumElems::NumElems(const InputParameters & parameters) :
    GeneralPostprocessor(parameters)
{}

Real
NumElems::getValue()
{
  return _subproblem.mesh().nElem();
}

