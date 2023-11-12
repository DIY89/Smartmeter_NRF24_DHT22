#ifndef MESSAGE_H
#define MESSAGE_H 

#include <nrf_data.h>

#define NODE_ID 1
#define MAX_NODE_ID 255
#define MAX_SENSOR_ID 4
#define MAX_SENSOR_TYPE 6
#define MAX_MSG_LEN 32

typedef enum {
		I_UNKNOWN = 0,
		I_BAT 		= 1,
		I_DHT 		= 2,
		I_POW 		= 3,
 } sensor_id;

typedef enum {
		S_UNKNOWN 	= 0,
		S_BAT 					= 1,
  S_TEMP  			= 2,    
  S_HUM   			= 3,    
  S_POW_CUR		= 4,
		S_POW_SUM		= 5,
 } sensor_type;

class MessageSender{
public:
	MessageSender(uint8_t nodeId, sensor_id sensorId, sensor_type sensorType);
	bool send();
	void store(const double value);

private:
	uint8_t node_id;
	sensor_id s_id;
	sensor_type s_type;
	double value;
};



#endif // MESSAGE_H 
