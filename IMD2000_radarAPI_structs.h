#ifndef IMD2000_RADARAPI_STRUCTS_H
#define IMD2000_RADARAPI_STRUCTS_H

/**************************************************************************************
  includes
**************************************************************************************/
#include "IMD2000_radarAPI_basicTypes.h"
#include "IMD2000_radarAPI_enums.h"


/**************************************************************************************
 defines
**************************************************************************************/
#if defined(_WIN32) && !defined(IMD2000_RADARAPI_LIBRARY_AS_SOURCE)
    #ifdef IMD2000_RADARAPI_LIBRARY
        #define IMD2000_API_EXPORT __declspec(dllexport)
    #else
        #define IMD2000_API_EXPORT __declspec(dllimport)
    #endif
#else
    #ifndef IMD2000_API_EXPORT
        #define IMD2000_API_EXPORT
    #endif
#endif

#define IMD2000_MAX_TARGETS  (20)

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************************
   typedefs
**************************************************************************************/

typedef struct IMD2000Handle *IMD2000Handle_t;


typedef struct {
    float32_t f32_range_m;                  /* [m]*/
    float32_t f32_velocity_mps;             /* [m/s] */
    float32_t f32_signal_dB;                /* [dB] */
    float32_t f32_estimatedTimeOfArrival_s; /* [s] */
} IMD2000_Target_t;

typedef struct {
    uint16_t ui16_nrOfTargets;
    uint16_t ui16_targetListId;
    uint16_t ui16_blockageDetection;
    uint16_t ui16_reserved;
    IMD2000_Target_t target[IMD2000_MAX_TARGETS];
} IMD2000_TargetList_t;


#ifdef __cplusplus
}
#endif

#endif // IMD2000_RADARAPI_STRUCTS_H
