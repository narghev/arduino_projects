int heater_port = 2;
int cooler_port = 3;
int temp_port = 0;
float temperature_to_maintain = 25.0;

float voltage_given_to_temp_sensor = 5.0;

float temperature_in_C(float temp){
  float voltage = temp * voltage_given_to_temp_sensor * 1000.0;
  voltage /= 1024.0;
  float temp_in_C = voltage/10;
  return temp_in_C;
}

void cooler(){
  digitalWrite(cooler_port, HIGH);
  digitalWrite(heater_port, LOW);
}

void heater(){
  digitalWrite(cooler_port, LOW);
  digitalWrite(heater_port, HIGH);
}

void shut_everything_off(){
  digitalWrite(cooler_port, LOW);
  digitalWrite(heater_port, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(heater_port, OUTPUT);
  pinMode(cooler_port, OUTPUT);
}

void loop() {
  float temp = analogRead(temp_port);
  temp = temperature_in_C(temp);
  
  Serial.print("Temperature in the room: ");
  Serial.print(temp);
  Serial.println();

  if (temp < temperature_to_maintain)
    heater();
  else if (temp > temperature_to_maintain)
    cooler();
  else
    shut_everything_off();

  delay(1000);  
}
