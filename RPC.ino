// M7 Core: Load the TensorFlow Lite model, run inference, and store the results in shared memory.
#ifdef CORE_CM7

#include "RPC.h"
#include "SDRAM.h"

uint32_t *shared_data;

void setup() {
  bootM4();
  RPC.begin();
  Serial.begin(115200);

  SDRAM.begin();
  shared_data = (uint32_t *)SDRAM.malloc(3 * sizeof(float)); // Allocate space for three float values
}

void loop() {
  // Simulate the output probabilities of the three moth classes.
  float probabilities[3] = {0.2, 0.5, 0.3};

  // Copy the probabilities to the shared memory.
  memcpy(shared_data, probabilities, 3 * sizeof(float));

  // Notify the M4 core that new data is available.
  RPC.call("setData", (uint32_t)shared_data);

  delay(1000); // Adjust the delay according to your requirements.
}

#endif // CORE_CM7

// M4 Core: Receive the shared memory address, read the inference results, and make decisions.
#ifdef CORE_CM4

#include "RPC.h"
#include "SDRAM.h"

uint32_t *received_data = nullptr;

bool setData(uint32_t address) {
  received_data = (uint32_t *)address;
  return true;
}

void setup() {
  RPC.begin();
  SDRAM.begin();
  RPC.bind("setData", setData);
}

void loop() {
  if (received_data != nullptr) {
    // Read the output probabilities from the shared memory.
    float probabilities[3];
    memcpy(probabilities, received_data, 3 * sizeof(float));

    // Make decisions based on the probabilities.
    // Replace this code with your actual decision-making logic.
    int max_index = 0;
    float max_prob = probabilities[0];
    for (int i = 1; i < 3; ++i) {
      if (probabilities[i] > max_prob) {
        max_prob = probabilities[i];
        max_index = i;
      }
    }

    // Do something based on the highest probability class.
    // For example, control actuators or print the result.
    Serial.printf("Highest probability class: %d with probability: %f\n", max_index, max_prob);
  }

  delay(100); // Adjust the delay according to your requirements.
}

#endif // CORE_CM4
