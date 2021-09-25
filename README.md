# Bluetooh-control-and-avoid-obstacles-car
Bluetooh control and avoid obstacles car using Arduino
Danh sach linh kien:
- Arduino Uno
- Module Bluetooth: HC-05
- Module điều khiển động cơ L298N
- Động cơ servo SG90
- Khung xe
- Động cơ
- Day ket noi
- Pin 18650
App ket noi:
-Bluetooh RC Controller
So do ket noi:
*Nguồn
-Arduino + L298N sẽ lấy nguồn từ bộ 2 pin 18650
-Servo + SR04 sẽ lấy nguồn từ L298N
-2 động cơ sẽ lấy nguồn từ L298N
*Đấu dây tín hiệu
-Chân trig của SR-04 = 12
-Chân echo của SR-04 = 13
-Chân IN1 Module L298 = 6 // để điều chỉnh hướng
-Chân IN2 Module L298 = 9
-Chân IN3 Module L298 = 8
-Chân IN4 Module L298 = 10
-Chân ENA Module L298 = 5 // để điều chỉnh tốc độ
-Chân ENB Module L298 = 11
