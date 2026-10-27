#include <GUVA-S12SD.h>


GUVAS12SD uv(A0);

void setup(){
  Serial.begin(9600);
}

void loop()
{
  float mV = uv.read();
  float uv_index = uv.index(mV);
  Serial.println(uv_index);
}