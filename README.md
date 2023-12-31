# Neuromorphic-Ultrasonic-Active-Acoustic-Sensing

Description: This project aimed to create a simulated sensing system modeled after the highly efficient echolocation of the horseshoe bat. The system implemented a real-time insect classification system using an LSTM network on a dual-core H7 Portenta microcontroller. Developed an approach to classify different moth categories using a deep learning model implemented on a dual-core H7 Portenta microcontroller. The solution applies signal processing techniques to acoustic microDoppler data and utilizes an LSTM network for the classification task. The model is deployed on the M7 core while the M4 core handles data acquisition and preprocessing, demonstrating efficient inter-core communication. The system’s robust design accommodates real-time requirements, error handling, model updates, power management, and comprehensive debugging, making it a significant advancement in real-time insect classification using portable acoustic micro-Doppler systems.

### Implementation:
* Designed a real-time insect classification system based on LSTM network.
* Implemented the system on a dual-core H7 Portenta microcontroller.
* Applied signal processing techniques to acoustic microDoppler data.
* Utilized the M7 core for model deployment and the M4 core for data acquisition and preprocessing, demonstrating efficient inter-core communication.

![image](https://github.com/travislatchman/Neuromorphic-Ultrasonic-Active-Acoustic-Sensing/assets/32372013/14897be5-13fd-43aa-9798-7fb2aab514b3)

# Code Snippets and Files

Ensure you have Python 3.6 or later installed on your machine, along with the necessary libraries such as TensorFlow, NumPy, and SciPy. To run all Jupyter notebooks, you can run each cell individually.

To upload and run the Arduino code, open the Arduino IDE and load the file of interest. Connect your Arduino Portenta H7 board to your computer, select the correct port and board type in the IDE, and then click the upload button.


1. `Preprocess_initial.ipynb` – This code snippet preprocesses raw time-domain signals using Short-Time Fourier Transform (STFT) and creates input-output sequences for training a machine learning model. The `preprocess_signal` function applies STFT to the raw signal and returns the spectrogram. The `create_input_output_sequences` function creates input-output pairs of sequences from the preprocessed signals and their corresponding labels. Finally, the code splits the data into training and testing sets and reshapes the input data for training a machine learning model using LSTM.

2. `lstm_initial.ipynb` - Builds, trains, and converts a TensorFlow Lite model. The model is a Long Short-Term Memory (LSTM) neural network with two LSTM layers, each with 64 units, and a dense output layer with one unit and sigmoid activation. The model is compiled with binary cross-entropy loss and accuracy metric, and trained for 100 epochs with a batch size of 32 and 20% validation split. Finally, the trained model is converted to TensorFlow Lite format and saved as a file named 'lstm_model.tflite'.

3. `lstm_csv.ipyb` - Contains code for an LSTM model built using TensorFlow and Keras to process and make predictions on time-series data. The code starts by normalizing the data by applying the MinMaxScaler function and reshaping it to have the format (samples, time_steps, features). The model is then converted to a TensorFlow Lite model for deployment on mobile devices. 

4. `Final_lstm.ipynb` – Final model to build and train an LSTM model using TensorFlow and Keras. The model is compiled with binary cross-entropy loss and accuracy metrics, and is converted to TensorFlow Lite format and saved to a file.

5. `Lstm_mat.ipynb` - Loads and preprocesses data from a .mat file, trains a LSTM model, and makes predictions on a test set. It also includes functions for normalizing data, reshaping data, and one-hot encoding labels.

6. `Trained_Model_Inferencing_H7.ino` - This is an Arduino code for running a TensorFlow Lite model on sensor data. The code reads sensor data, normalizes it, applies a Fast Fourier Transform, and feeds it into the model for inference. The output is processed to find the label with the highest probability and printed to the serial monitor. The code is designed to run continuously in the loop() function.

7. `DSP_Block.ino` - The code snippet is an example of how to use an Arduino board to read sensor data, preprocess it using a Hamming window and FFT, and then send it to another core for processing using an LSTM model. The program uses ARM's CMSIS DSP library, which provides a suite of optimized functions for digital signal processing, and an RPC library for communication between cores.

8. `M4_DSP_BLOCK.ino` - The code snippet provided include defining shared memory and a mutex for inter-core communication, setting up a DSP block, and copying preprocessed data to shared memory using the mutex to ensure safe access.

9. `Deep_Learning_Block.ino` - This code snippet shows how to use TensorFlow Lite library for microcontrollers to run inference on preprocessed data. The code initializes the interpreter, sets the input tensor, runs the interpreter, gets the output tensor, and processes the classifier output. The output is printed to the serial console.

10. `M7_DeepLearning_Block.ino` - Run inference on preprocessed data. The code is designed to work on an M7 microcontroller that has dual-core processing capabilities. The code defines shared memory and a mutex for inter-core communication, which is essential for multi-core programming.

11. `Dual_Cores_M4_M7.ino` - This code snippet includes inter-core communication using shared memory and mutex for efficient processing of sensor data on a microcontroller. DSP block setup and processing, and deep learning block setup and inference using TensorFlow Lite.

12. `RPC.ino` - Demonstrates how to load a TensorFlow Lite model, run inference, and store the results in shared memory using two cores on an M7 microcontroller. The M7 core simulates the output probabilities of three moth classes and copies the probabilities to shared memory, while the M4 core receives the shared memory address, reads the inference results, and makes decisions based on the probabilities.

