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


1. `Preprocess_initial.ipynb`: Preprocesses raw time-domain signals using Short-Time Fourier Transform (STFT) and creates input-output sequences for training a machine learning model.

2. `lstm_initial.ipynb`: Builds, trains, and converts a TensorFlow Lite model. The model is a Long Short-Term Memory (LSTM) neural network.

3. `lstm_mat.py`: Loads and preprocesses data from a .mat file, trains a LSTM model, and makes predictions on a test set.

4. `lstm_csv.ipyb`: Contains code for an LSTM model built using TensorFlow and Keras to process and make predictions on time-series data.

5. `Final_lstm.ipynb`: Builds and trains an LSTM model using TensorFlow and Keras. The model is compiled with binary cross-entropy loss and accuracy metrics, and is converted to TensorFlow Lite format and saved to a file.

6. `Lstm_mat.ipynb`: Loads and preprocesses data from a .mat file, trains a LSTM model, and makes predictions on a test set.

7. `Trained_Model_Inferencing_H7.ino`: An Arduino code for running a TensorFlow Lite model on sensor data.

8. `DSP_Block.ino`: An example of how to use an Arduino board to read sensor data, preprocess it using a Hamming window and FFT, and then send it to another core for processing using an LSTM model.

9. `M4_DSP_BLOCK.ino`: Includes defining shared memory and a mutex for inter-core communication, setting up a DSP block, and copying preprocessed data to shared memory using the mutex to ensure safe access.

10. `Deep_Learning_Block.ino`: Shows how to use TensorFlow Lite library for microcontrollers to run inference on preprocessed data.

11. `M7_DeepLearning_Block.ino.ino`: Run inference on preprocessed data. The code is designed to work on an M7 microcontroller that has dual-core processing capabilities.

12. `Dual_Cores_M4_M7.ino`: Includes inter-core communication using shared memory and mutex for efficient processing of sensor data on a microcontroller. 

13. `RPC.ino`: Demonstrates how to load a TensorFlow Lite model, run inference, and store the results in shared memory using two cores on an M7 microcontroller. 

