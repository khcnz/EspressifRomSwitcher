extern "C" uint8_t system_upgrade_userbin_check();
extern "C" void system_upgrade_flag_set(uint8_t flag);
extern "C" void system_upgrade_reboot (void);

#define UPGRADE_FLAG_START 0x01
#define UPGRADE_FLAG_FINISH 0x02

#define DELAY 5000
#define STATUS_GPIO 13

void setup()
{
  if(STATUS_GPIO)
  {
    pinMode(STATUS_GPIO, OUTPUT);
    digitalWrite(STATUS_GPIO, LOW);
  }
  
  Serial.begin(115200);
  delay(DELAY);

  uint8_t rom = system_upgrade_userbin_check() + 1;
  Serial.printf("Current Rom: %d\n", rom);
  
  Serial.printf("Rebooting...\n"); 
  if(STATUS_GPIO)
  {
    digitalWrite(STATUS_GPIO, HIGH);
  } 
  system_upgrade_flag_set(UPGRADE_FLAG_START);
  system_upgrade_flag_set(UPGRADE_FLAG_FINISH);
  system_upgrade_reboot(); 
}

void loop()
{
  delay(100);
}
