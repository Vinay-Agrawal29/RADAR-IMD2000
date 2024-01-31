#ifndef IMD2000_API_IF_H
#define IMD2000_API_IF_H

#include "IMD2000_radarAPI_basicTypes.h"
#include "IMD2000_radarAPI_enums.h"
#include "IMD2000_radarAPI_structs.h"
//#include "InnoSenT_Structs_Embedded.h"

/**************************************************************************************
 defines
**************************************************************************************/
#if defined(_WIN32) && !defined(IMD2000_API_AS_SOURCE)
    #ifdef IMD2000_RADARAPI_LIBRARY
        #define IMD2000_API_EXPORT __declspec(dllexport)
    #else
        #define IMD2000_API_EXPORT __declspec(dllimport)
    #endif
#else
    #define IMD2000_API_EXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************************
 api functions
**************************************************************************************/
#ifndef __linux__
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_initComPort(IMD2000Handle_t *pHandle, uint8_t comportNr, IMD2000_Baudrate_t baudrate);
#else
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_initComPort(IMD2000Handle_t *pHandle, char *comport, int length, IMD2000_Baudrate_t baudrate);
#endif

IMD2000_API_EXPORT IMD2000_Result_t IMD2000_initSystem(IMD2000Handle_t pHandle, uint8_t destAddress, uint32_t timeout);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_exitComPort(IMD2000Handle_t pHandle);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_exitSystem(IMD2000Handle_t pHandle, uint8_t destAddress);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_getApiVersion(float32_t *version);

/*SD2 - D1 */
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_StartAcquisition(IMD2000Handle_t pHandle, uint8_t destAddress, uint32_t timeout);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_StopAcquisition(IMD2000Handle_t pHandle, uint8_t destAddress, uint32_t timeout);

IMD2000_API_EXPORT IMD2000_Result_t IMD2000_getTxAntenna(IMD2000Handle_t pHandle, uint8_t *enable, uint8_t destAddress, uint32_t timeout);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_setTxAntenna(IMD2000Handle_t pHandle, uint8_t enable, uint8_t destAddress, uint32_t timeout);

/*SD2 - D2 */
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_getSerialNumber(IMD2000Handle_t pHandle,uint32_t *serialNumber, uint8_t destAddress, uint32_t timeout);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_getFirmwareVersion(IMD2000Handle_t pHandle, uint16_t *major, uint16_t *fix, uint16_t *minor, uint8_t destAddress, uint32_t timeout);

/*SD2 - D3 */

/*SD2 - D4 */
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_getVelocityLowerBound(IMD2000Handle_t pHandle,float32_t *velocity, uint8_t destAddress, uint32_t timeout);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_getVelocityUpperBound(IMD2000Handle_t pHandle,float32_t *velocity, uint8_t destAddress, uint32_t timeout);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_getRangeLowerBound(IMD2000Handle_t pHandle,float32_t *range, uint8_t destAddress, uint32_t timeout);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_getRangeUpperBound(IMD2000Handle_t pHandle,float32_t *range, uint8_t destAddress, uint32_t timeout);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_getSignalMagnitudeLowerBound(IMD2000Handle_t pHandle,float32_t *signalMagnitude, uint8_t destAddress, uint32_t timeout);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_getSignalMagnitudeUpperBound(IMD2000Handle_t pHandle,float32_t *signalMagnitude, uint8_t destAddress, uint32_t timeout);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_getDetectionThresholdBeta(IMD2000Handle_t pHandle,float32_t *detectionThreshold, uint8_t destAddress, uint32_t timeout);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_getFalseAlarmSuppression(IMD2000Handle_t pHandle,uint16_t *falseAlarmSuppression, uint8_t destAddress, uint32_t timeout);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_getFrequencyChannel(IMD2000Handle_t pHandle, uint16_t *pFrequencyChannel, uint8_t destAddress, uint32_t timeout);

/*SD2 - D5 */
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_setVelocityLowerBound(IMD2000Handle_t pHandle, float32_t velocity, uint8_t destAddress, uint32_t timeout);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_setVelocityUpperBound(IMD2000Handle_t pHandle, float32_t velocity, uint8_t destAddress, uint32_t timeout);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_setRangeLowerBound(IMD2000Handle_t pHandle, float32_t range, uint8_t destAddress, uint32_t timeout);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_setRangeUpperBound(IMD2000Handle_t pHandle, float32_t range, uint8_t destAddress, uint32_t timeout);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_setSignalMagnitudeLowerBound(IMD2000Handle_t pHandle, float32_t signalMagnitude, uint8_t destAddress, uint32_t timeout);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_setSignalMagnitudeUpperBound(IMD2000Handle_t pHandle, float32_t signalMagnitude, uint8_t destAddress, uint32_t timeout);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_setDetectionThresholdBeta(IMD2000Handle_t pHandle, float32_t detectionThreshold, uint8_t destAddress, uint32_t timeout);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_setFalseAlarmSuppression(IMD2000Handle_t pHandle, uint16_t falseAlarmSuppression, uint8_t destAddress, uint32_t timeout);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_setFrequencyChannel(IMD2000Handle_t pHandle, uint16_t frequencyChannel, uint8_t destAddress, uint32_t timeout);


/*SD2 - D6 */
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_getProductInfo(IMD2000Handle_t pHandle, uint16_t *productInfo, uint8_t destAddress, uint32_t timeout);

/*SD2 - DA */
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_getTargetList(IMD2000Handle_t pHandle, IMD2000_TargetList_t *pTargetList, uint8_t destAddress, uint32_t timeout);

/*SD2 - DF */
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_setDefaultAppSetting(IMD2000Handle_t pHandle, uint16_t productNr, uint8_t destAddress, uint32_t timeout);
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_EEPROM_WriteBufferToFlash(IMD2000Handle_t pHandle, uint8_t *result, uint8_t destAddress, uint32_t timeout);

/*SD2 - BC */
IMD2000_API_EXPORT IMD2000_Result_t IMD2000_resetSensor(IMD2000Handle_t pHandle, uint8_t destAddress);



#ifdef __cplusplus
}
#endif

#endif // IMD2000_API_IF_H
