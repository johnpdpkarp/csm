//#############################################################################
//
//    FILENAME:   RasterGM.cpp
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    This file provides implementation for methods declared in the
//    csm::RasterGM class.
//
//>     06-Dec-2012   JPK  Initial Coding
//                         Changed ParamSet to param::Set.  De-inlined
//                         destructor and getFamily() methods.
//                         Replaced vector<double> with EcefLocus for
//                         imageTo*Locus methods.  Added inline method
//                         getCovarianceMatrix().  Provided reference
//                         implementations for computeAllSensorPartials()
//                         methods.
//<
//    NOTES:
//
//
//    Refer to RasterGM.h for more information.
//
//#############################################################################

#define CSM_LIBRARY

#include "RasterGM.h"

namespace csm {

//*****************************************************************************
// RasterGM::~RasterGM()
//*****************************************************************************
RasterGM::~RasterGM()
{}

//*****************************************************************************
// RasterGM::getFamily()
//*****************************************************************************
std::string RasterGM::getFamily() const
{
   return (GeometricModel::getFamily() + CSM_RASTER_FAMILY);
}

//*****************************************************************************
// RasterGM::computeAllSensorPartials()
//*****************************************************************************
std::vector<RasterGM::SensorPartials>
RasterGM::computeAllSensorPartials(const EcefCoord& groundPt,
                                   param::Set       pSet,
                                   double           desiredPrecision,
                                   double*          achievedPrecision,
                                   WarningList*     warnings) const
{
   
   const std::vector<int> indices = getParameterSetIndices(pSet);
   
   std::vector<RasterGM::SensorPartials> val;

   const int NUM_PARAMS = indices.size();

   if (NUM_PARAMS)
   {
      val.resize(NUM_PARAMS);

      //***
      // The acheived precision should be the MAXIMUM of the achieved
      // precision values found for each desired index.
      //***
      if (achievedPrecision) *achievedPrecision = 0.0;

      for(int i = 0; i < NUM_PARAMS; ++i)
      {
         double prec = 0.0;
         val[i] = computeSensorPartials(indices[i],
                                        groundPt,
                                        desiredPrecision,
                                        &prec,
                                        warnings);
         
         if (achievedPrecision && (prec > *achievedPrecision))
         {
            *achievedPrecision = prec;
         }
      }
   }
   return val;
}


//*****************************************************************************
// RasterGM::computeAllSensorPartials()
//*****************************************************************************
std::vector<RasterGM::SensorPartials>
RasterGM::computeAllSensorPartials(const ImageCoord& imagePt,
                                   const EcefCoord&  groundPt,
                                   param::Set        pSet,
                                   double            desiredPrecision,
                                   double*           achievedPrecision,
                                   WarningList*      warnings) const
{
  const std::vector<int> indices = getParameterSetIndices(pSet);
   
   std::vector<RasterGM::SensorPartials> val;

   const int NUM_PARAMS = indices.size();

   if (NUM_PARAMS)
   {
      val.resize(NUM_PARAMS);

      //***
      // The acheived precision should be the MAXIMUM of the achieved
      // precision values found for each desired index.
      //***
      if (achievedPrecision) *achievedPrecision = 0.0;

      for(int i = 0; i < NUM_PARAMS; ++i)
      {
         double prec = 0.0;
         val[i] = computeSensorPartials(indices[i],
                                        imagePt,
                                        groundPt,
                                        desiredPrecision,
                                        &prec,
                                        warnings);
         
         if (achievedPrecision && (prec > *achievedPrecision))
         {
            *achievedPrecision = prec;
         }
      }
   }
   return val;
}

} // namespace csm
