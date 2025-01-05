#include "esphome.h"

class JSNSensor : public PollingComponent, public Sensor {
 public:
  JSNSensor() : PollingComponent(1000) {}  // Poll every second

  void setup() override {
    // Set up UART or any other required initialization
  }

  void update() override {
    if (Serial.available()) {
      String response = Serial.readStringUntil('\n');  // Read until newline
      float distance = response.toFloat();            // Convert to float
      if (distance > 0) {                             // Validate response
        publish_state(distance);                     // Publish the valid distance
      } else {
        ESP_LOGW("custom", "Invalid sensor reading: %s", response.c_str());
      }
    }
  }
};
