#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <ros.h>
#include <geometry_msgs/Twist.h>
// Pin variables for motors.
const int right_back = 13;
const int right_front = 12;
const int left_back = 10;
const int left_front = 11;
const int right_pwm = 6; //8;
const int left_pwm = 9;
int pwm = 62;

ros::NodeHandle nh;

void MoveFwd() {
     digitalWrite(right_back, HIGH);
     digitalWrite(left_back, HIGH);
     digitalWrite(right_front,LOW);
     digitalWrite(left_front, LOW);
     // digitalWrite(right_pwm, pwm);
    // digitalWrite(left_pwm, pwm);
     analogWrite(right_pwm, pwm);
     analogWrite(left_pwm, pwm);
}

void MoveStop() {
     digitalWrite(right_back, LOW);
     digitalWrite(left_back, LOW);
     digitalWrite(right_front,LOW);
     digitalWrite(left_front, LOW);
     analogWrite(right_pwm, pwm);
     analogWrite(left_pwm, pwm);
}

void MoveLeft() {
     digitalWrite(right_back, HIGH);
     digitalWrite(left_back, LOW);
     digitalWrite(right_front,LOW);
     digitalWrite(left_front, HIGH);
     analogWrite(right_pwm, pwm);
     analogWrite(left_pwm, pwm);
}

void MoveRight() {
     analogWrite(right_pwm, pwm);
     analogWrite(left_pwm, pwm);
     digitalWrite(right_back, LOW);
     digitalWrite(left_back, HIGH);
     digitalWrite(right_front,HIGH);
     digitalWrite(left_front, LOW);
}

void MoveBack() {
     analogWrite(right_pwm, pwm);
     analogWrite(left_pwm, pwm);
     digitalWrite(right_back, LOW);
     digitalWrite(left_back, LOW);
     digitalWrite(right_front,HIGH);
     digitalWrite(left_front, HIGH);
}

void cmd_vel_cb(const geometry_msgs::Twist & msg) {
     // Read the message. Act accordingly.
     // We only care about the linear x, and the rotational z.
     const float x = msg.linear.x;
     const float z_rotation = msg.angular.z;
    // pwm = int(msg.linea/r.y);
     // Decide on the morot state we need, according to command.
     if (x > 0 && z_rotation == 0) {
         MoveFwd();
     }
    else if (x == 0 && z_rotation == 1) {
        MoveRight();
    }
    else if (x == 0 && z_rotation < 0) {
        MoveLeft();
    }
     else if (x < 0 && z_rotation == 0) {
        MoveBack();
    }
    else{
        MoveStop();
     }
}

ros::Subscriber sub("cmd_vel", cmd_vel_cb);

void setup() {
     pinMode(right_back, OUTPUT);
     pinMode(left_back, OUTPUT);
     pinMode(right_front, OUTPUT);
     pinMode(left_front, OUTPUT);
     pinMode(right_pwm, OUTPUT);
     pinMode(left_pwm, OUTPUT);

     nh.initNode();
     nh.subscribe(sub);
}

void loop() {
nh.spinOnce();
delay(1);
}
