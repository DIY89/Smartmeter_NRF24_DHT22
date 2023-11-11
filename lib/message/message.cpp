#include <message.h>

MessageSender::MessageSender(uint8_t p_nodeId, sensor_id p_sensorId, sensor_type p_sensorType){
	if(0 > p_nodeId && p_nodeId > MAX_NODE_ID){
		this->node_id = MAX_NODE_ID;
	}else{
		this->node_id = p_nodeId;
	}

	if(I_BAT > p_nodeId && p_nodeId > I_POW){
		this->s_id = I_UNKNOWN;
	}else{
		this->s_id = p_sensorId;
	}

	if(S_BAT > p_nodeId  && p_nodeId > MAX_SENSOR_TYPE){
		this->s_type = S_UNKNOWN;
	}else{
		this->s_type = p_sensorType;
	}	

	this->value = 0;
}

void MessageSender::store(double v) {
	value = v;
}

void MessageSender::send() const{
	char data[MAX_MSG_LEN];

	String value(this->value,2);
	String msg;

	// Msg format ( i=1,s=2,d=2,v=25.25	)
	sprintf(data,"i=%d,s=%d,d=%d,v=", this->node_id, this->s_id, this->s_type);

#if defined(DEBUG)
	Serial.print("NodeID: ");
	Serial.println(this->node_id);
	Serial.print("Sensor ID: ");
	Serial.println(this->s_id);
	Serial.print("Sensor Type: ");
	Serial.println(this->s_type);
	Serial.print("Value: ");
	Serial.println(value);

	Serial.print("MSG: ");
	msg = data + value;
	Serial.println(msg);

	strcpy(data,msg.c_str());

	Serial.println(data);
#endif

	Serial.print("Msg Size: ");
 	Serial.println(sizeof(data));

	char test[6] = "Hallo";

	//radioAdapter.send(&data,sizeof(data));	
	radioAdapter.send(&test,sizeof(test));	
};

/*
void MessageSender::doubleTochar(double value){
  int k;
  char aux[10];

  itoa(value*100, aux, 10);
  int n = strlen(aux);
  k = 0;
  for(int i=0;i<n;i++){
    if(i == n-1 - 1){
      msg[k++] = '.';
    }
    msg[k++] = aux[i];
  }
  msg[k++] = '\0';
}
*/