# Smart-Room-Energy-Safety-System-iot_project

Smart Room Energy & Safety System
## Overview

This project is an IoT-based Smart Room Monitoring and Automation System built using ESP32, Flask, and multiple sensors.

The system monitors:

Room occupancy using PIR sensor
Entry detection using IR sensor
Temperature and humidity using DHT11
Automatic light control using relay
Power-saving automation
Basic intrusion alert logic

Sensor data is sent from ESP32 to a Flask backend server through HTTP requests.
The backend stores data in SQLite and displays live room status on a web dashboard with real-time updates and charts.

## Features
Real-time room monitoring
Motion detection using PIR sensor
Entry detection using IR sensor
Automatic room light control
Temperature and humidity monitoring
Power-saving light automation
Intrusion alert logic
Flask-based web dashboard
SQLite database storage
Live temperature graph using Chart.js

## Technologies Used
# Hardware
ESP32
PIR Motion Sensor
IR Sensor
DHT11 Sensor
Relay Module
# Software
Arduino Framework (C++)
Python Flask
Flask SQLAlchemy
HTML
CSS
JavaScript
Chart.js
SQLite

# Project Structure
smart-room-energy-safety-system/
│
├── src/main.cpp
├── app.py
├── templates/
│   └── index.html
├── room.db
└── README.md

# Hardware Connections

Component	----->ESP32 Pin
PIR Sensor----->GPIO 27
IR Sensor	------>GPIO 26
Relay Module---->GPIO 23
DHT11 Data Pin--->GPIO 4
all components  vcc--->vcc
all components gnd---->gnd

# How to Run

## 1. Setup ESP32
Connect all sensors to ESP32
Update WiFi credentials
Update Flask server IP address
Upload code using Arduino IDE or PlatformIO

## 2. Setup Flask Server

Install dependencies:

pip install flask flask_sqlalchemy

Run the Flask server:

python app.py

Server will start at:

http://0.0.0.0:5000

## 3. Run the System

Power the ESP32
Ensure ESP32 and PC are connected to the same WiFi network
Open browser:
http://localhost:5000
Monitor:
Room occupancy
Motion status
Entry status
Temperature
Humidity
Live graph

## System Workflow

1.ESP32 reads sensor values
2.PIR detects room occupancy
3.IR sensor detects entry
4.DHT11 measures temperature and humidity
5.Relay automatically controls room light
6.ESP32 sends data to Flask server
7.Flask stores data in SQLite database
8.Dashboard displays live updates and graph

## Automation Logic

## Automatic Light Control
Motion detected → Light ON
No motion for 5 minutes → Light OFF
## Intrusion Detection
If motion is detected during night hours:
Intrusion alert is triggered
## Environmental Monitoring
Live temperature and humidity monitoring

## API Endpoints
POST /data

Receives sensor data from ESP32

GET /data

Returns stored sensor data for dashboard

## Dashboard Features
Live room status
Motion detection status
Entry detection status
Temperature display
Humidity display
Real-time temperature graph

## Future Improvements
Add email or Telegram alerts
Add OLED/LCD display
Add cloud deployment
Add energy consumption analysis
Add mobile app integration
Add WebSocket real-time communication
Add multiple room support

# Author
Harsha G
Learning:
Embedded Systems
IoT Systems
Python Flask
ESP32 Development
Backend Development
