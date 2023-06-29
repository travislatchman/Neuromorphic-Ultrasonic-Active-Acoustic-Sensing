#include <TensorFlowLite.h>
#include "tensorflow/lite/experimental/micro/kernels/all_ops_resolver.h"
#include "tensorflow/lite/experimental/micro/micro_error_reporter.h"
#include "tensorflow/lite/experimental/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
#include <arduinoFFT.h>

// Define the sensor pin
const int sensorPin = A0;

// Constants for normalization (replace with your own values)
const float normalization_min = 0.0;
const float normalization_max = 1.0;

// Constants for preprocessing
const int num_samples = 50000; // 0.5s of data at 100kHz sampling rate

// The TensorFlow Lite model
extern const unsigned char moth_lstm_model_tflite[];

// The model's size in bytes
extern const unsigned int moth_lstm_model_tflite_len;

// Create an area of memory to use for input, output, and intermediate arrays.
const int tensor_arena_size = 50 * 1024;
uint8_t tensor_arena[tensor_arena_size];

// Define the error reporter
tfl::MicroErrorReporter error_reporter;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Configure the sensor pin
  pinMode(sensorPin, INPUT);

  // Set up logging
  Serial.println("Setting up...");

  // Map the model into a usable data structure
  const tflite::Model* model = tflite::GetModel(moth_lstm_model_tflite);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    error_reporter.Report("Model schema mismatch!");
    while (1);
  }

  // Instantiate an AllOpsResolver which loads all available operations
  tfl::ops::micro::AllOpsResolver resolver;

  // Build an interpreter to run the model
  tfl::MicroInterpreter interpreter(model, resolver, tensor_arena, tensor_arena_size, &error_reporter);
  interpreter.AllocateTensors();

  // Get information about the memory area to use for the model's input
  TfLiteTensor* input = interpreter.input(0);

  // Preprocess the data and run inference
  preprocess_and_run_inference(input, &interpreter);

  Serial.println("Setup complete.");
}

void loop() {
  // perform continuous inference  preprocess_and_run_inference() in the loop
}


void preprocess_and_run_inference(TfLiteTensor* input, tfl::MicroInterpreter* interpreter) {
  // Read sensor data
  float sensor_data[num_samples];
  for (int i = 0; i < num_samples; i++) {
    sensor_data[i] = analogRead(sensorPin);
    delayMicroseconds(10); // Sample every 10 microseconds for 100kHz sampling rate
  }

  // Normalize the sensor data
  normalize_data(sensor_data, num_samples);

  // Preprocess the data (apply FFT)
  uint16_t fft_size = num_samples / 2; // Choose an appropriate FFT size based on the data
  double vReal[fft_size];
  double vImag[fft_size];

  // Copy the sensor data to the real part of the FFT input and set the imaginary part to 0
  for (uint16_t i = 0; i < fft_size; i++) {
    vReal[i] = sensor_data[i * 2];
    vImag[i] = 0;
  }

  // Create an FFT object
  arduinoFFT FFT = arduinoFFT(vReal, vImag, fft_size, 100000);

  // Perform the FFT
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();

  // Square the magnitudes to get the energy
  for (uint16_t i = 0; i < fft_size; i++) {
    vReal[i] = vReal[i] * vReal[i];
  }

  // Copy the processed data to the input tensor
  for (int i = 0; i < input->dims->data[1]; i++) {
    input->data.f[i] = vReal[i];
  }

  // Run inference
  TfLiteStatus invoke_status = interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
    error_reporter.Report("Invoke failed!");
    return;
  }

  // Get the output tensor
  TfLiteTensor* output = interpreter->output(0);

  // Process the output (e.g., find the label with the highest probability)
  int highest_probability_label = 0;
  float highest_probability = output->data.f[0];
  for (int i = 1; i < output->dims->data[1]; i++) {
    if (output->data.f[i] > highest_probability) {
      highest_probability = output->data.f[i];
      highest_probability_label = i;
    }
  }

  // Print the result
  Serial.print("Predicted label: ");
  Serial.println(highest_probability_label);
}
