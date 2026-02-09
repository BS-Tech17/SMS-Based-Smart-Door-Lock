𝗜𝗼𝗧-𝗘𝗻𝗮𝗯𝗹𝗲𝗱 𝗘𝗺𝗯𝗲𝗱𝗱𝗲𝗱 𝗔𝗰𝗰𝗲𝘀𝘀 𝗖𝗼𝗻𝘁𝗿𝗼𝗹 𝗦𝘆𝘀𝘁𝗲𝗺

𝗣𝗿𝗼𝗯𝗹𝗲𝗺 𝗠𝗼𝘁𝗶𝘃𝗮𝘁𝗶𝗼𝗻

 Conventional door locks provide no intelligence, accountability, or real-time response to unauthorized access. This project explores how embedded systems and IoT technologies can be combined to build a secure, user-specific access control mechanism for residential environments.
 

𝗦𝘆𝘀𝘁𝗲𝗺 𝗢𝘃𝗲𝗿𝘃𝗶𝗲𝘄

 This is an Arduino-based embedded access control system designed to authenticate individual residents using unique passwords and actively monitor entry behavior using sensors and GSM-based alerts.

 
𝗛𝗮𝗿𝗱𝘄𝗮𝗿𝗲 𝗥𝗲𝗾𝘂𝗶𝗿𝗲𝗺𝗲𝗻𝘁𝘀

- Arduino Uno (ATmega328P)

- 16x2 LCD display with I2C interface

- 4x4 matrix keypad

- GSM module (SIM800/SIM900 compatible)

- Ultrasonic distance sensor (HC-SR04)

- Servo motor

- Buzzer

- Breadboard

- Jumper wires

- External power supply for GSM module

  
𝗔𝘂𝘁𝗵𝗲𝗻𝘁𝗶𝗰𝗮𝘁𝗶𝗼𝗻 𝗮𝗻𝗱 𝗔𝘂𝘁𝗵𝗼𝗿𝗶𝘇𝗮𝘁𝗶𝗼𝗻 𝗟𝗼𝗴𝗶𝗰

 A. Each resident is assigned a unique password (for example: A-1234, B-5678, C-9012).

 B. The door lock opens only when a valid credential from the authorized set is entered.

 C. Upon successful authentication, the system identifies the user and displays a personalized message such as “Welcome A” before unlocking the latch.
 

𝗦𝗲𝗰𝘂𝗿𝗶𝘁𝘆 𝗮𝗻𝗱 𝗜𝗻𝘁𝗿𝘂𝘀𝗶𝗼𝗻 𝗗𝗲𝘁𝗲𝗰𝘁𝗶𝗼𝗻

 A. If an incorrect password is entered three consecutive times, the system triggers a security response.

 B. A call and SMS alert are sent via the GSM module to the homeowner and a designated neighbor, indicating a possible unauthorized access attempt.
 

𝗢𝗰𝗰𝘂𝗽𝗮𝗻𝗰𝘆 𝗠𝗼𝗻𝗶𝘁𝗼𝗿𝗶𝗻𝗴 𝗮𝗻𝗱 𝗔𝗻𝗼𝗺𝗮𝗹𝘆 𝗗𝗲𝘁𝗲𝗰𝘁𝗶𝗼𝗻

 A. An ultrasonic sensor performs real-time people counting at the entry point.

 B. Each authorized user is assigned a maximum number of allowed accompanying individuals (User A: 2, User B: 3, User C: 4).

 C. If the detected number of people exceeds the predefined limit for the authenticated user, the event is flagged as a security anomaly.

 D. Alert calls and messages are immediately sent to the homeowner and the neighbor indicating excessive occupancy.
 

𝗞𝗲𝘆 𝗧𝗮𝗸𝗲𝗮𝘄𝗮𝘆𝘀

 A. Demonstrates multi-layered physical security using low-cost embedded hardware.

 B. Combines authentication, head count, and automated alerting in constrained environments.

 C. Highlights practical challenges in embedded security system design.
 

𝗙𝘂𝘁𝘂𝗿𝗲 𝗦𝗰𝗼𝗽𝗲

 A. A system to verify that the right person is entering the right password

 B. OTP-based verification system can be integrated into it.

 C. IoT-based access analytics and remote monitoring dashboards.

 
