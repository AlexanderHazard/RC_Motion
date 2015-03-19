/* 
 * File:   IMU_reader.h
 * Author: alex
 *
 * Created on 21 Май 2014 г., 9:03
 */

#ifndef IMU_READER_H
#define	IMU_READER_H


//#include <mutex>

using namespace std;

class IMU_reader {
public:
    IMU_reader();
    IMU_reader(const IMU_reader& orig);
    virtual ~IMU_reader();
private:
    void setup(void);//setup i2c sensors
    void run_read(void);//procedure of reading
    void setDataIMU(float*);
public:
    void read_cycle(void);
    void getDataIMU(int*, int*, int*);//get IMU data
    
private:
    static int cYaw, cPitch, cRoll;
   // mutex mpu_MUTEX;

};

#endif	/* IMU_READER_H */

