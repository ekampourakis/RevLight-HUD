#ifndef ELM327_h
#define ELM327_h
#include "Arduino.h"
#include <SoftwareSerial.h>

//Definitions for the ELM327 library
#define ELM_MAC "001D,A5,68988C"
#define TX_PIN 7
#define RX_PIN 8
#define DEBUG

#ifndef ELM_TIMEOUT
	#warning "ELM_TIMEOUT must be defined."
	#define ELM_TIMEOUT 9000
#endif

#ifndef ELM_BAUD_RATE
	#warning "ELM_BAUD_RATE must be defined"
	#define ELM_BAUD_RATE 38400
#endif

#ifndef ELM_MAC
	#error "ELM_MAC must be defined prior to ELM327 library"
#endif

#ifndef DEBUG_BAUD_RATE
	#define DEBUG_BAUD_RATE 38400
#endif

#ifdef DEBUG
	#define DEBUG_SERIAL Serial
#endif

#ifndef TX_PIN
	#error "TX_PIN for software serial must be defined"
#endif

#ifndef RX_PIN
	#error "RX_PIN for software serial must be defined"
#endif

#define ELM_SUCCESS 0
#define ELM_NO_RESPONSE 1
#define ELM_BUFFER_OVERFLOW 2
#define ELM_GARBAGE 3
#define ELM_UNABLE_TO_CONNECT 4
#define ELM_NO_DATA 5
#define ELM_PROTOCOL 6

#define BLUETOOTH_SUCCESS 7
#define BLUETOOTH_NOPING 8
#define BLUETOOTH_INIT_FAILED 9
#define BLUETOOTH_BIND_FAILED 10
#define BLUETOOTH_PAIR_FAILED 11
#define BLUETOOTH_LINK_FAILED 12


class Elm327
{
	public:

		byte begin();
		byte getVersion(String &rev);
		byte getIgnMon(bool &powered);
		byte getVoltage(float &voltage);
		byte engineLoad(byte &load);


		/**
		 * Gets the Coolant Temperature.  Reads PID 05 from the OBD interface and sets
		 * temp to the value returned after conversion.
		 * @param[out]	temp	Signed integer value is set to the coolant temperature.
		 * - Minimum: -40
		 * - Maximum Value: 215
		 * - Units: °C
		 */
		byte coolantTemperature(int &temp);


		/**
		 * Gets the fuel trim for bank 1 in the short term.  Reads PID 06 from the OBD 
		 * interface and sets percent to the value returned after conversion.
		 * @param[out]	percent	- Signed integer is set to the percent fuel trim.
		 * - Minimum Value: -100
		 * - Maximum Value: 99.2
		 * - Units: %
		 */
		byte fuelTrimBank1ShortTerm(int &percent);


		/**
		 * Gets the fuel trim for bank 2 in the short term.  Reads PID 07 from the OBD 
		 * interface and sets percent to the value returned after conversion.
		 * @param[out]	percent	- Signed integer is set to the percent fuel trim.
		 * - Minimum Value: -100
		 * - Maximum Value: 99.2
		 * - Units: %
		 */
		byte fuelTrimBank2ShortTerm(int &percent);


		/**
		 * Gets the fuel trim for bank 1 in the long term.  Reads PID 08 from the OBD 
		 * interface and sets percent to the value returned after conversion.
		 * @param[out]	percent	- Signed integer is set to the percent fuel trim.
		 * - Minimum Value: -100
		 * - Maximum Value: 99.2
		 * - Units: %
		 */
		byte fuelTrimBank1LongTerm(int &percent);


		/**
		 * Gets the fuel trim for bank 2 in the long term.  Reads PID 09 from the OBD 
		 * interface and sets percent to the value returned after conversion.
		 * @param[out]	percent	- Signed integer is set to the percent fuel trim.
		 * - Minimum Value: -100
		 * - Maximum Value: 99.2
		 * - Units: %
		 */
		byte fuelTrimBank2LongTerm(int &percent);


		/**
		 * Gets the fuel pressure.  Reads PID 0A from the OBD interface and sets pressure
		 * to the value returned after conversion.
		 * @param[out]	pressure	- Signed integer is set to the fuel pressure.
		 * - Minimum Value: 0
		 * - Maximum Value: 765
		 * - Units: kPa (Absolute)
		 */
		byte fuelPressure(int &pressure);


		/**
		 * Gets the Intake Manifold Absolute Pressure.  Reads PID 0B from the OBD 
		 * inteface and sets pressure to the value returned after conversion.
		 *@param[out]	pressure	Byte set to the manifold pressure
		 * - Minimum Value: 0
		 * - Maximum Value: 255
		 * - Units: kPa (Absolute)
		 */
		byte intakeManifoldAbsolutePressure(byte &pressure);


		/**
		 * Gets the current engine RPM.  Reads PID 0C from the OBD Interface and
		 * sets rpm to the value returned after conversion.
		 * @param[out]	rpm	Unsigned integer is set to the current engine rpm.
		 * - Minimum Value: 0
		 * - Maximum Value: 16,383
		 * - Units: RPM
		 */
		byte engineRPM(int &rpm);


		/**
		 * Gets the current speed of the vehicle in km/h.  Reads PID 0D form the OBD 
		 * interface and sets speed to the value returned after conversion.
		 * @param[out]	speed	Byte is set to the current speed of the vehicle.
		 * - Minimum Value: 0
		 * - Maximum Value: 255
		 * - Units: km/h
		 */
		byte vehicleSpeed(byte &speed);


		/**
		 * Gets the timing advance of the vehicle relative to TDC on the number one cylinder.
		 * Reads PID 0E from the OBD interface and sets advance to the value returned after 
		 * conversion.
		 * @param[out]	advance	Integer set to the timing advance value.
		 * - Minimum Value: -64
		 * - Maximum Value: 63.5
		 * - Units: ° from TDC
		 */
		byte timingAdvance(int &advance);


		/**
		 * Gets the intake air temperature.  Reads PID 0F from the OBD interface and sets
		 * temperature to the value returned after conversion.
		 * @param[out]	temperature	Integer set to the intake air temperature
		 * - Minimum Value: -40
		 * - Maximum Value: 215
		 * - °C
		 */
		byte intakeAirTemperature(int &temperature);


		/**
		 * Gets the Manifold Absolute Flow (MAF) rate.  Reads PID 10 from the OBD interface
		 * and sets rate to the value returned after conversion.
		 * @param[out]	rate	Integer value set to the flow rate.
		 * - Minimum Value: -40
		 * - Maximum Value: 215
		 * - °C
		 */
		byte MAFAirFlowRate(unsigned int &rate);


		/**
		 * Gets the current throttle position. Reads PID 11 from the OBD interface
		 * and sets position to the value returned after conversion.
		 * @param[out] position Byte containing throttle position.
		 * - Minimum Value: 0
		 * - Maximum Value: 100
		 * - %
		 */
		byte throttlePosition(byte &position);
		
		byte o2SensorBank1Sensor1(byte &voltage, byte &trim);
		byte o2SensorBank1Sensor2(byte &voltage, byte &trim);
		byte o2SensorBank1Sensor3(byte &voltage, byte &trim);
		byte o2SensorBank1Sensor4(byte &voltage, byte &trim);
		byte o2SensorBank2Sensor1(byte &voltage, byte &trim);
		byte o2SensorBank2Sensor2(byte &voltage, byte &trim);
		byte o2SensorBank2Sensor3(byte &voltage, byte &trim);
		byte o2SensorBank2Sensor4(byte &voltage, byte &trim);
		byte o2sensorRead(const char *bank, byte &voltage, byte &trim);
		byte auxiliaryInputStatus(bool &auxStatus);
		byte engineRunTime(unsigned int &runTime);
		byte distanceMIL(unsigned int &distance);
		byte relativeFuelRailPressure(unsigned int &pressure);
		byte absoluteFuelRailPressure(unsigned int &pressure);
		byte o2S1WRVoltage(unsigned int &equivRatio, unsigned int &voltage);
		byte o2S2WRVoltage(unsigned int &equivRatio, unsigned int &voltage);
		byte o2S3WRVoltage(unsigned int &equivRatio, unsigned int &voltage);
		byte o2S4WRVoltage(unsigned int &equivRatio, unsigned int &voltage);
		byte o2S5WRVoltage(unsigned int &equivRatio, unsigned int &voltage);
		byte o2S6WRVoltage(unsigned int &equivRatio, unsigned int &voltage);
		byte o2S7WRVoltage(unsigned int &equivRatio, unsigned int &voltage);
		byte o2S8WRVoltage(unsigned int &equivRatio, unsigned int &voltage);
		byte commandedEGR(byte &egr);
		byte EGRError(int &error);
		byte commandedEvaporativePurge(byte &purge);
		byte fuelLevel(byte &level);
		byte warmUpsSinceLastCleared(byte &warmUps);
		byte distanceSinceLastCleared(unsigned int &distance);
		byte evapPressure(int &pressure);
		byte barometricPressure(byte  &pressure);
		byte o2S1WRCurrent(unsigned int &equivRatio, int &current);
		byte o2S2WRCurrent(unsigned int &equivRatio, int &current);
		byte o2S3WRCurrent(unsigned int &equivRatio, int &current);
		byte o2S4WRCurrent(unsigned int &equivRatio, int &current);
		byte o2S5WRCurrent(unsigned int &equivRatio, int &current);
		byte o2S6WRCurrent(unsigned int &equivRatio, int &current);
		byte o2S7WRCurrent(unsigned int &equivRatio, int &current);
		byte o2S8WRCurrent(unsigned int &equivRatio, int &current);
		byte catalystTemperatureBank1Sensor1( int &temperature);
		byte catalystTemperatureBank2Sensor1( int &temperature);
		byte catalystTemperatureBank1Sensor2( int &temperature);
		byte catalystTemperatureBank2Sensor2( int &temperature);
		byte controlModuleVoltage(unsigned int &voltage);
		byte absoluteLoadValue(unsigned int &load);
		byte commandEquivalenceRatio(float &ratio);
		byte relativeThrottlePosition(byte &position);
		byte ambientAirTemperature(int &temperature);
		byte absoluteThrottlePositionB(byte &position);
		byte absoluteThrottlePositionC(byte &position);
		byte acceleratorPedalPositionD(byte &position);
		byte acceleratorPedalPositionE(byte &position);
		byte acceleratorPedalPositionF(byte &position);
		byte commandedThrottleActuator(byte &position);
	private:
	
		bool WaitOK(String Command, int Tries);
		byte connectBluetooth();
		byte o2WRVoltage(const char *sensor, unsigned int &equivRatio, unsigned int &voltage);
		byte o2WRCurrent(const char *sensor, unsigned int &equivRatio, int &current);
		byte catTemperature(const char *sensor, int &temperature);
		byte getBytes( const char *mode, const char *chkMode, const char *pid, byte *values, unsigned int numValues);
		byte runCommand(const char *cmd, char *data, unsigned int dataLength);
		bool getBit(byte b, byte p);
		byte getFuelTrim(const char *pid, int &percent);
		void flush();
};
		

#endif