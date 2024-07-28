# PRECISION AGRICULTURAL SPRAYING: AUTONOMOUS COMPUTER VISION FOR SPRAYER NOZZLE CONTROL

Abstract— In modern agriculture, the precise application of pesticides is critical for enhancing crop yields while mitigating environmental impacts. This study presents an innovative system that leverages computer vision to control tractor-mounted sprayer nozzles for precision pesticide application. The system uses a Raspberry Pi for real-time image processing and an Arduino for controlling the sprayer nozzles, ensuring targeted spraying on crops. This minimizes pesticide wastage and environmental contamination. Key components include image segmentation algorithms, remote control mechanisms, and a user-friendly mobile interface. Evaluations demonstrate significant reductions in pesticide use and improvements in application accuracy. This research advances precision agriculture by providing a scalable, efficient, and eco-friendly solution for autonomous pesticide spraying.

**Keywords**— Precision Agriculture, Autonomous Systems, Computer Vision, Pesticide Spraying, Tractor-Mounted Sprayers, Crop Row Detection.

The autonomous nozzle control system aims to optimize pesticide application in crop fields. It consists of several interconnected components as shown in figure 1.

### Figure 1. Block Diagram of the Proposed Framework
![System Architecture of Autonomous Nozzle Control for Precision Agricultural Spraying](https://github.com/iamklevy/Precision-Agricultural-Spraying/assets/94145850/8d5f8350-cd52-4e9b-8855-9a695bf08d16)

The autonomous pesticide spraying tractor integrates both an Arduino Uno and an ESP32 microcontrollers to manage its physical components effectively. The system is structured as follows:
1)	Arduino Uno Microcontroller:
 The Arduino microcontroller manages the activation of the sprayer nozzles. It receives processed signals resulting from the nozzle mapping algorithm. The Arduino Uno ensures that the nozzles spray pesticides precisely on the targeted crop sections, minimizing waste and enhancing efficiency. ESP32 Microcontroller. Two types of actuators are used; two DC motors which drive the tractor's wheels, and four sprayer nozzles are integrated to apply pesticides accurately based on processed data and control signals.
2)	ESP32 microcontroller:
 The nozzles, controlled by the Arduino, apply pesticides accurately based on the processed data and control signal
3)	Extra equiements:
 Motor drivers (L298N), Li-ion batteries, Bluetooth module (HC-05) and ESP32.

### 3D Design Demo 
https://github.com/iamklevy/PRECISION-AGRICULTURAL-SPRAYING-AUTONOMOUS-COMPUTER-VISION-FOR-SPRAYER-NOZZLE-CONTROL/assets/94145850/5ee1b6fb-c0d2-4f5b-9983-96f7ed603564

<p>
    <video src="https://github.com/user-attachments/assets/282130e3-dc6c-42b9-a4db-16a461d7da02" />
      *Your display does not support the video tag. open browser to see the video.*
  </p>

Figure 2 shows the complete spraying hardware system with the equipment used.

### Figure 2. Complete Spraying Hardware 
![image2](https://github.com/iamklevy/Precision-Agricultural-Spraying/assets/94145850/17b053e1-b4ee-4a6d-9f46-888f14a4dc8e)
![RC car - annotated diagram](https://github.com/iamklevy/Precision-Agricultural-Spraying/assets/94145850/b68b7b82-b2e9-459d-b456-6b194a241047)

Blynk IoT platform is used for controlling the dc motors, MIT app inventor is used for controlling the pumps. The hardware is connected to the cloud via the Blynk app, designing the application to be controlled and monitored in real-time. 
Figure 3 shows the remote-control application.

### Figure 3. Control Application 
![image3](https://github.com/iamklevy/Precision-Agricultural-Spraying/assets/94145850/62ce86db-c3a3-4698-b4d5-9f0971abfa6a)

### Run-Time 
<p>
    <video src="https://github.com/iamklevy/PRECISION-AGRICULTURAL-SPRAYING-AUTONOMOUS-COMPUTER-VISION-FOR-SPRAYER-NOZZLE-CONTROL/assets/94145850/864acec9-864a-46ae-a885-4b95e1e3ffa5" />
      *Your display does not support the video tag. open browser to see the video.*
  </p>
