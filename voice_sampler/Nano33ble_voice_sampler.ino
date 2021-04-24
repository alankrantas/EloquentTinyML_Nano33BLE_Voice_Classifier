/*
 * Voice sampler for Arduino Nano 33 BLE Sense by Alan Wang
 */

#include <math.h>
#include <PDM.h>


#define SERIAL_PLOT_MODE  false  // set to true to test sampler in serial plotter
#define PDM_SOUND_GAIN    255    // sound gain of PDM mic
#define PDM_BUFFER_SIZE   256    // buffer size of PDM mic

#define SAMPLE_THRESHOLD  900    // RMS threshold to trigger sampling
#define FEATURE_SIZE      32     // sampling size of one voice instance
#define SAMPLE_DELAY      20     // delay time (ms) between sampling

#define TOTAL_SAMPLE      50     // total number of voice instance


double feature_data[FEATURE_SIZE];
volatile double rms;
unsigned int total_counter = 0;


// callback function for PDM mic
void onPDMdata() {

  rms = -1;

  short sample_buffer[PDM_BUFFER_SIZE];
  int bytes_available = PDM.available();
  PDM.read(sample_buffer, bytes_available);

  // calculate RMS (root mean square) from sample_buffer
  unsigned int sum = 0;
  for (unsigned short i = 0; i < (bytes_available / 2); i++) sum += pow(sample_buffer[i], 2);
  rms = sqrt(double(sum) / (double(bytes_available) / 2.0));
}


void setup() {

  Serial.begin(115200);
  while (!Serial);

  PDM.onReceive(onPDMdata);
  PDM.setBufferSize(PDM_BUFFER_SIZE);
  PDM.setGain(PDM_SOUND_GAIN);

  if (!PDM.begin(1, 16000)) {  // start PDM mic and sampling at 16 KHz
    Serial.println("Failed to start PDM!");
    while (1);
  }

  pinMode(LED_BUILTIN, OUTPUT);

  // wait 1 second to avoid initial PDM reading
  delay(900);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);

  if (!SERIAL_PLOT_MODE) Serial.println("# === Voice data start ===");
}


void loop() {

  // waiting until sampling triggered
  while (rms < SAMPLE_THRESHOLD);

  digitalWrite(LED_BUILTIN, HIGH);
  for (unsigned short i = 0; i < FEATURE_SIZE; i++) {  // sampling
    while (rms < 0);
    feature_data[i] = rms;
    delay(SAMPLE_DELAY);
  }
  digitalWrite(LED_BUILTIN, LOW);

  // pring out sampling data
  if (!SERIAL_PLOT_MODE) Serial.print("[");
  for (unsigned short i = 0; i < FEATURE_SIZE; i++) {
    if (!SERIAL_PLOT_MODE) {
      Serial.print(feature_data[i]);
      Serial.print(", ");
    } else {
      Serial.println(feature_data[i]);
    }
  }
  if (!SERIAL_PLOT_MODE) {
    Serial.println("],");
  } else {
    for (unsigned short i = 0; i < (FEATURE_SIZE / 2); i++) Serial.println(0);
  }

  // stop sampling when enough samples are collected
  if (!SERIAL_PLOT_MODE) {
    total_counter++;
    if (total_counter >= TOTAL_SAMPLE) {
      Serial.println("# === Voice data end ===");
      PDM.end();
      while (1) {
        delay(100);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
      }
    }
  }

  // wait for 1 second after one sampling
  delay(900);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
}
