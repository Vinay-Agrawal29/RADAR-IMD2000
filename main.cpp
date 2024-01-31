#include "stdio.h"
#include "iostream"
#include "time.h"
#include "math.h"

#include <fstream>
#include <string>
#include <filesystem>
#include <ctime>
#include <chrono>

#include <QDebug>
#include <QThread>
#include "IMD2000_radarAPI_if.h"
#include "IMD2000_radarAPI_structs.h"
#include "IMD2000_radarAPI_enums.h"

#define IMD2000_COMPORT      (5)   // edit this port to your corresponding com port
#define IMD2000_ADDRESS     (100)
#define IMD2000_TIMEOUT     (250)

/************** SET AMOUNT OF CYCLES FOR TIMING TEST **************/
#define IMD2000_TIMINGTEST_CYCLES   (500) // 600 cycles correspond to 1 minute with an update rate of 100ms


int main(void)
{
    auto startTime = std::chrono::high_resolution_clock::now();
    printf("example project for timing test started\n\n");

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
    uint8_t port = IMD2000_COMPORT;
    #ifndef __linux__
        res = IMD2000_initComPort(&handle,port,IMD2000_BAUDRATE_256000);
    #else
        res = IMD2000_initComPort(&handle,"/dev/ttyUSB0",IMD2000_BAUDRATE_256000);
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


    /************** GET TARGET LIST AND PERFORM TIMING TEST **************/
    /* Start Acquisition -> make sure sensor is in acquisition mode */
    res = IMD2000_StartAcquisition(handle,IMD2000_ADDRESS,IMD2000_TIMEOUT);
    if(res != IMD2000_API_ERR_OK){
        qDebug() << "IMD2000_StartAcquisition failed error: " <<res;
        return res;
    }else{
        qDebug() << "IMD2000_StartAcquisition successful";
    }
    QThread::msleep(200);

    IMD2000_TargetList_t *p_targetList = new IMD2000_TargetList_t;
    QElapsedTimer timingTest_time;
    uint32_t timingTest_current = 0;
    uint32_t timingTest_sum = 0;
    uint16_t i_timingTest = 0;
    uint16_t timingTest_targetlist_errors = 0;
    uint16_t timingTest_targetlist_id_dropframe_last = 0;
    uint16_t i_timingTest_targetlist_id_dropframe_result = 0;

    qDebug() << "\n-----BEGIN TIMING TEST FOR" << IMD2000_TIMINGTEST_CYCLES << "CYCLES WITH TIMEOUT OF" << IMD2000_TIMEOUT << "ms-----\n";


    std::ofstream csvFile("C:\\Users\\VINAY AGRAWAL\\Desktop\\Working RADAR\\IMD-2000_Software_Package\\IMD-2000_RadarAPI\\IMD2000_ExampleProject_timing_test\\target_data.csv", std::ios::out | std::ios::trunc);

    if (!csvFile.is_open()) {
        qDebug() << "Failed to open CSV file for writing!";
        return 0;
    }


    csvFile << "Timestamp (ms),TargetIndex (Tid),Range (m),Velocity (m/s),Direction,Signal (dB),Estimated Time of Arrival (s)\n";

    // std::time_t lastTimestamp = -1;



    for(i_timingTest = 0; i_timingTest < IMD2000_TIMINGTEST_CYCLES; ++i_timingTest){
        timingTest_targetlist_id_dropframe_last = p_targetList->ui16_targetListId;
        memset((void*)p_targetList, 0, sizeof (IMD2000_TargetList_t));
        timingTest_time.start();


        res = IMD2000_getTargetList(handle,p_targetList,IMD2000_ADDRESS,IMD2000_TIMEOUT);
        if(res != IMD2000_API_ERR_OK){
            qDebug() << "IMD2000_getTargetList failed";
            qDebug() << "error: " <<res;
            timingTest_targetlist_errors += 1;
        }else{
            timingTest_current = timingTest_time.elapsed();
            timingTest_sum += timingTest_current;
            if(p_targetList->ui16_targetListId - timingTest_targetlist_id_dropframe_last > 1){
                i_timingTest_targetlist_id_dropframe_result++;
            }

            qDebug() << "IMD2000_getTargetList success - latency for current cycle:" << timingTest_current << "ms - current cycle:" << i_timingTest << " - target list ID:" << p_targetList->ui16_targetListId;

            // Print velocity and range for each target in the list
            for (uint16_t targetIndex = 0; targetIndex < p_targetList->ui16_nrOfTargets; ++targetIndex) {
                IMD2000_Target_t target = p_targetList->target[targetIndex];

                auto elapsedMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count();

                qDebug() << "Target" << targetIndex + 1 << ":";
                qDebug() << "Range: " << target.f32_range_m << "m";
                qDebug() << "Velocity: " << target.f32_velocity_mps << "m/s";
                qDebug() << "Signal dB: " << target.f32_signal_dB << "dB";
                qDebug() << "Estimated Time of Arrival: " << target.f32_estimatedTimeOfArrival_s << "s";



                if (targetIndex != 0) {
                    // Print an empty timestamp
                    csvFile << ",";
                } else {
                    // Print the timestamp for the first target with a new timestamp
                    csvFile << elapsedMilliseconds << ",";
                }
                csvFile << targetIndex + 1 << ","; // TargetIndex
                csvFile << target.f32_range_m << ","; // Range (m)
                csvFile << target.f32_velocity_mps << ","; // Velocity (m/s)
                if(target.f32_velocity_mps > 0)
                    csvFile << "Towards the RADAR" << ",";
                else
                    csvFile << "Away from the RADAR" << ",";
                csvFile << target.f32_signal_dB << ","; // Signal dB
                csvFile << target.f32_estimatedTimeOfArrival_s << "\n"; // Estimated Time of Arrival (s)

            }


            qDebug() << "-----------------------------------------------------------";
        }
    }

    csvFile.close();
    delete p_targetList;
    qDebug() << "\n-----END OF TIMING TEST-----\n";

    /* Calculate mean latency for transmission over IMD2000_TIMINGTEST_CYCLES */
    qDebug() << "\n-----RESULTS-----";
    qDebug() << "ProductInfo:" << productInfo_ui16;
    qDebug() << "ApiVersion - " << QString::number(static_cast<double>(version),'f',3);
    qDebug() << "SerialNumber :" << serialNumber_u32;
    qDebug() << "FirmwareVersion - major:" << major << " minor:" << minor;
    qDebug() << "Average transmission latency over" << IMD2000_TIMINGTEST_CYCLES << "cycles:" << (timingTest_sum / IMD2000_TIMINGTEST_CYCLES) << "ms";
    qDebug() << "Amount of target list errors:" << timingTest_targetlist_errors << "errors";
    qDebug() << "Amount of drop frames:" << i_timingTest_targetlist_id_dropframe_result - 1 << "frames";
    qDebug() << "Test parameters: Timeout:" << IMD2000_TIMEOUT << "ms - cycles:" << IMD2000_TIMINGTEST_CYCLES;
    qDebug() << "-----RESULTS END-----\n";



    /************** EXIT DEVICE **************/
    /* Exit System with Deviceaddress 128 */
    res = IMD2000_exitSystem(handle,IMD2000_ADDRESS);
    if(res != IMD2000_API_ERR_OK){
        return 0;
    }else{
        qDebug() << "IMD2000_exitSystem - successful";
    }
    QThread::msleep(50);

    /* Close serialport connection */
    res = IMD2000_exitComPort(handle);
    if(res != IMD2000_API_ERR_OK){
        return 0;
    }else{
        qDebug() << "IMD2000_exitComPort - successful";
    }
    QThread::msleep(50);

    /************** Example project finished **************/
    printf("example project for timing test finished\n\n");

    system("pause"); // prevent application  from closing automatically
    return 0;
}
