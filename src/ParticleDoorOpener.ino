/*
 * Project ParticleDoorOpener
 * Description: A IOT door lock controlled by Google Assistant 
 * Author: Brian Nelson
 * Date: 12/23/19
 */

// setup() runs once, when the device is first turned on.

Servo servo;
IPAddress iphone(10, 0, 1, 41);

int position = 0;

void setup()
{
  servo.attach(D0);

  Particle.function("control", control);
}

int control(String command)
{
  if (command == "unlock")
  {
    position = 180;
    servo.write(position);
    return 0;
  }
  else if (command == "lock")
  {
    position = 0;
    servo.write(position);

    return 0;
  }
}

int ping()
{
  // if no packets are returned lock the door.
  // This works because I assigned a specific phone to a static IP by its mac address.
  if (WiFi.ping(iphone) == 0)
  {
    control("lock");
  };
  delay(10000); // wait 10 seconds
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  ping();
};