
#include "stdio.h"
#include "iostream"
#include "time.h"
#include "math.h"

#include <QDebug>
#include <QThread>

#include "IMD2000_radarAPI_if.h"
#include "IMD2000_radarAPI_structs.h"
#include "IMD2000_radarAPI_enums.h"

//#define READ_ONLY_FUNCTIONS     /* uncomment to write default vlaues */

#define IMD200_COMPORT      (5)
#define IMD2000_ADDRESS     (100)
#define IMD2000_TIMEOUT     (150)

//#define SET_DEFAULT_APP_SETTING
//#define RESET_SENSOR

int main(void)
{
    printf("example project started\n\n");

    /************** CHECK API VERSION **************/
    IMD2000Handle_t handle;
    IMD2000_Result_t res;

    float32_t version;
    res = IMD2000_getApiVersion(&version);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_getApiVersion failed";
        qDebug() << "error: " <<res;
        return 0;
    }else{
        qDebug() << "IMD2000_getApiVersion - " << QString::number(static_cast<double>(version),'f',3);
    }
    QThread::msleep(50);

    /************** CONNECT DEVICE **************/
    /* Init serial port */
    uint8_t port = IMD200_COMPORT;
    #ifndef __linux__
        res = IMD2000_initComPort(&handle,port,IMD2000_BAUDRATE_256000);
    #else
        res = IMD2000_initComPort(&handle,"/dev/ttyUSB0",MDR_BAUDRATE_256000);
    #endif
    if(res != IMD2000_API_ERR_OK){
            qDebug() << "IMD2000_initComPort failed";
            return 0;
    }else{
        qDebug() << "IMD2000_initComPort - " << port;
    }
    QThread::msleep(50);

    /* Init System with */
    uint8_t addr = IMD2000_ADDRESS;
    res = IMD2000_initSystem(handle,addr,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_initSystem failed";
        qDebug() << "error: " <<res;
        return 0;
    }else{
        qDebug() << "IMD2000_initSystem - " << addr;
    }
    QThread::msleep(50);


    /************** GET SYSTEM INFORMATION **************/
    /* get sensor info */
    uint16_t productInfo_ui16;
    res = IMD2000_getProductInfo(handle, &productInfo_ui16, IMD2000_ADDRESS, IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_getProductInfo failed";
        qDebug() << "error: " <<res;
        return 0;
    }else{
        qDebug() << "IMD2000_getProductInfo - product info :" << productInfo_ui16;
    }
    QThread::msleep(50);

    /* get sensor serial number */
    uint32_t serialNumber_u32 = 0u;
    res = IMD2000_getSerialNumber(handle,&serialNumber_u32,IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_getSerialNumber failed; error: " << res;
        return res;
    }else{
        qDebug() << "IMD2000_getSerialNumber successful; serial number =" << serialNumber_u32;
    }
    QThread::msleep(50);

    /* get firmware version */

    uint16_t major;
    uint16_t fix;
    uint16_t minor;
    res = IMD2000_getFirmwareVersion(handle, &major, &fix, &minor, IMD2000_ADDRESS, IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_getFirmwareVersion failed";
        qDebug() << "error: " <<res;
        return 0;
    }else{
        qDebug() << "IMD2000_getFirmwareVersion - major:" << major << " minor:" << minor;
    }
    QThread::msleep(100);


    /************** GET TARGET LIST **************/
    /* Start Acquisition -> make sure sensor is in acquisition mode */
    res = IMD2000_StartAcquisition(handle,IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_StopAcquisition failed error: " <<res;
        return res;
    }else{
        qDebug() << "IMD2000_StopAcquisition successful";
    }
    QThread::msleep(200);

    IMD2000_TargetList_t *p_targetList = new IMD2000_TargetList_t;
    memset((void*)p_targetList, 0, sizeof (IMD2000_TargetList_t));
    res = IMD2000_getTargetList(handle,p_targetList,IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_getTargetList failed";
        qDebug() << "error: " <<res;
        return 0;
    }else{
        qDebug() << "IMD2000_getTargetList success";
    }
    delete p_targetList;
    QThread::msleep(50);

    /************** GET APPLICATION SETTING **************/
    /* get velocity lower bound */
    float32_t velocityMin_f32;
    res = IMD2000_getVelocityLowerBound(handle, &velocityMin_f32, IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_getVelocityLowerBound failed; error: " << res;
        return res;
    }
    else
    {
        qDebug() << "IMD2000_getVelocityLowerBound successful; velocity lower bound =" << velocityMin_f32;
    }
    QThread::msleep(50);

    /* get velocity upper bound */
    float32_t velocityMax_f32;
    res = IMD2000_getVelocityUpperBound(handle, &velocityMax_f32, IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_getVelocityUpperBound failed; error: " << res;
        return res;
    }
    else
    {
        qDebug() << "IMD2000_getVelocityUpperBound successful; velocity upper bound =" << velocityMax_f32;
    }
    QThread::msleep(50);

    /* get range lower bound */
    float32_t rangeMin_f32;
    res = IMD2000_getRangeLowerBound(handle, &rangeMin_f32, IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_getRangeLowerBound failed; error: " << res;
        return res;
    }
    else
    {
        qDebug() << "IMD2000_getRangeLowerBound successful; range lower bound =" << rangeMin_f32;
    }
    QThread::msleep(50);

    /* get range upper bound */
    float32_t rangeMax_f32;
    res = IMD2000_getRangeUpperBound(handle, &rangeMax_f32, IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_getRangeUpperBound failed; error: " << res;
        return res;
    }
    else
    {
        qDebug() << "IMD2000_getRangeUpperBound successful; range upper bound =" << rangeMax_f32;
    }
    QThread::msleep(50);


    /* get signal magnitude lower bound */
    float32_t signalMagMin_f32;
    res = IMD2000_getSignalMagnitudeLowerBound(handle, &signalMagMin_f32, IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_getSignalMagnitudeLowerBound failed; error: " << res;
        return res;
    }
    else
    {
        qDebug() << "IMD2000_getSignalMagnitudeLowerBound successful; signal magnitude lower bound =" << signalMagMin_f32;
    }
    QThread::msleep(50);


    /* get signal magnitude upper bound */
    float32_t signalMagMax_f32;
    res = IMD2000_getSignalMagnitudeUpperBound(handle, &signalMagMax_f32, IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_getSignalMagnitudeUpperBound failed; error: " << res;
        return res;
    }
    else
    {
        qDebug() << "IMD2000_getSignalMagnitudeUpperBound successful; signal magnitude upper bound =" << signalMagMax_f32;
    }
    QThread::msleep(50);


    /* get detetion threshold beta */
    float32_t detectionThreshold_f32;
    res = IMD2000_getDetectionThresholdBeta(handle, &detectionThreshold_f32, IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_getDetectionThresholdBeta failed; error: " << res;
        return res;
    }
    else
    {
        qDebug() << "IMD2000_getDetectionThresholdBeta successful; detection threshold beta =" << detectionThreshold_f32;
    }
    QThread::msleep(50);

    /* get false alarm suppresion status */
    uint16_t falseAlarmSuppression_ui16;
    res = IMD2000_getFalseAlarmSuppression(handle, &falseAlarmSuppression_ui16, IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_getFalseAlarmSuppression failed; error: " << res;
        return res;
    }
    else
    {
        qDebug() << "IMD2000_getFalseAlarmSuppression successful; false alarm suppression Enable =" << falseAlarmSuppression_ui16;
    }
    QThread::msleep(50);

    /* get frequency channel */
    uint16_t frequencyChannelGet_ui16 = 0u;
    res = IMD2000_getFrequencyChannel(handle,&frequencyChannelGet_ui16,IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_getFrequencyChannel failed; error: " << res;
        return res;
    }else{
        qDebug() << "IMD2000_getFrequencyChannel successful; frequency channel =" << frequencyChannelGet_ui16;
    }
    QThread::msleep(50);


    /************** SET APPLICATION SETTING **************/
    /* set velocity lower bound */
    float32_t velocityMinSet_f32 = -7.1f;
    res = IMD2000_setVelocityLowerBound(handle, velocityMinSet_f32, IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_setVelocityLowerBound failed; error: " << res;
        return res;
    }
    else
    {
        qDebug() << "IMD2000_setVelocityLowerBound successful";
    }
    QThread::msleep(50);


    /* set velocity upper bound */
    float32_t velocityMaxSet_f32 = 7.1f;
    res = IMD2000_setVelocityUpperBound(handle, velocityMaxSet_f32, IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_setVelocityUpperBound failed; error: " << res;
        return res;
    }
    else
    {
        qDebug() << "IMD2000_setVelocityUpperBound successful";
    }
    QThread::msleep(50);


    /* set range lower bound */
    float32_t rangeMinSet_f32 = 0.6f;
    res = IMD2000_setRangeLowerBound(handle, rangeMinSet_f32, IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_setRangeLowerBound failed; error: " << res;
        return res;
    }
    else
    {
        qDebug() << "IMD2000_setRangeLowerBound successful";
    }
    QThread::msleep(50);


    /* set range upper bound */
    float32_t rangeMaxSet_f32 = 19.9f;
    res = IMD2000_setRangeUpperBound(handle, rangeMaxSet_f32, IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_setRangeUpperBound failed; error: " << res;
        return res;
    }
    else
    {
        qDebug() << "IMD2000_setRangeUpperBound successful";
    }
    QThread::msleep(50);


    /* set signal magnitude lower bound */
    float32_t signalMagMinSet_f32 = 20.0f;
    res = IMD2000_setSignalMagnitudeLowerBound(handle, signalMagMinSet_f32, IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_setSignalMagnitudeLowerBound failed; error: " << res;
        return res;
    }
    else
    {
        qDebug() << "IMD2000_setSignalMagnitudeLowerBound successful";
    }
    QThread::msleep(50);


    /* set signal magnitude upper bound */
    float32_t signalMagMaxSet_f32 = 99.0f;
    res = IMD2000_setSignalMagnitudeUpperBound(handle, signalMagMaxSet_f32, IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_setSignalMagnitudeUpperBound failed; error: " << res;
        return res;
    }
    else
    {
        qDebug() << "IMD2000_setSignalMagnitudeUpperBound successful";
    }
    QThread::msleep(50);


    /* set detection threshold beta */
    float32_t detectionThresholdSet_f32 = 0.5f;
    res = IMD2000_setDetectionThresholdBeta(handle, detectionThresholdSet_f32, IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_setDetectionThresholdBeta failed; error: " << res;
        return res;
    }
    else
    {
        qDebug() << "IMD2000_setDetectionThresholdBeta successful";
    }
    QThread::msleep(50);


    /* set false alarm suppression */
    uint16_t falseAlarmSuppressionSet_ui16 = 0;
    res = IMD2000_setFalseAlarmSuppression(handle, falseAlarmSuppressionSet_ui16, IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_setFalseAlarmSuppression failed; error: " << res;
        return res;
    }
    else
    {
        qDebug() << "IMD2000_setFalseAlarmSuppression successful";
    }
    QThread::msleep(50);

    /* set frequency channel */
    uint16_t frequencyChannelSet_ui16 = 1;
    res = IMD2000_setFrequencyChannel(handle,frequencyChannelSet_ui16,IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_setFrequencyChannel failed; error: " << res;
        return res;
    }else{
        qDebug() << "IMD2000_setFrequencyChannel successful";
    }
    QThread::msleep(100);


    /************** SET DEFAULT APPLICATION SETTING **************/
#ifdef SET_DEFAULT_APP_SETTING
    res = IMD2000_setDefaultAppSetting(handle, 0, IMD2000_ADDRESS, IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_setDefaultSetting - failed: error = " << res;
    }else{
        qDebug() << "IMD2000_setDefaultSetting - successful";
    }
    QThread::msleep(100);
#endif

    /************** WRITE SETTING BUFFER TO EEPROM MEMORY **************/
    /* Stop acquisition */
    res = IMD2000_StopAcquisition(handle,IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_StopAcquisition failed error: " <<res;
        return res;
    }else{
        qDebug() << "IMD2000_StopAcquisition successful";
    }
    QThread::msleep(100);

    /* write bufer to eeprom */
    uint8_t success = 255u;
    res = IMD2000_EEPROM_WriteBufferToFlash(handle, &success, IMD2000_ADDRESS, IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_EEPROM_WriteBufferToFlash - failed: error = " << res;
    }else{
        qDebug() << "IMD2000_EEPROM_WriteBufferToFlash - successful: " << success;
    }
    QThread::msleep(100);

#ifdef RESET_SENSOR
    /************** RESET SENSOR **************/
    res = IMD2000_resetSensor(handle,IMD2000_ADDRESS);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_resetSensor failed; error: " << res;
        return res;
    }else{
        qDebug() << "IMD2000_resetSensor successful";
    }
    QThread::msleep(3000);
#endif


    /************** EXIT DEVICE **************/
    /* Exit System with Deviceaddress 128 */
    res = IMD2000_exitSystem(handle,IMD2000_ADDRESS);
    if(res != IMD2000_API_ERR_OK){
        return 0;
    }else{
        qDebug() << "IMD2000_exitSystem - successfull";
    }
    QThread::msleep(50);

    /* Close serialport connection */
    res = IMD2000_exitComPort(handle);
    if(res != IMD2000_API_ERR_OK){
        return 0;
    }else{
        qDebug() << "IMD2000_exitComPort - successfull";
    }
    QThread::msleep(50);

    /************** Example project finished **************/
    printf("example project finished\n\n");

    return 0;
}



























