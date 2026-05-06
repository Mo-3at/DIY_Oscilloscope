//ESP-32 code uploaded using the arduino ide


/*
 * ESP32 Dual Channel Oscilloscope - Serial Plotter Version
 * CH1: GPIO 34 (Yellow in Plotter)
 * CH2: GPIO 35 (Blue in Plotter)
 */

// --- Configuration Pins ---
#define CH1_PIN    34 
#define CH2_PIN    35 

// --- Filter Settings ---
// Alpha value between 0.0 and 1.0. 
// 1.0 = No filtering (raw signal). 
// 0.1 = Heavy filtering (very smooth, but might introduce slight lag).
float filterAlpha = 0.17; 
float filteredCH1 = 0;
float filteredCH2 = 0;

// --- Oscilloscope Settings ---
const int BUFFER_SIZE = 200; // حجم البيانات المرسلة في كل دفعة
int ch1Buffer[BUFFER_SIZE];
int ch2Buffer[BUFFER_SIZE];

// Trigger settings
int triggerLevel = 2048; 
int timebaseDelay = 100; // تأخير ميكروثانية للتحكم في سرعة العرض (يمكنك تعديله)

void setup() {
  // سرعة عالية جداً لضمان عدم تأخير الرسم
  Serial.begin(115200);
  
  pinMode(CH1_PIN, INPUT);
  pinMode(CH2_PIN, INPUT);

  // تعريف أسماء القنوات للـ Serial Plotter
  // سيظهر CH1 و CH2 في أعلى نافذة الـ Plotter
  Serial.println("CH1,CH2");
}

void loop() {
  // 1. نظام القدح (Trigger) - المزامنة بناءً على القناة الأولى
  long timeout = millis();
  int prevVal = analogRead(CH1_PIN);
  bool triggered = false;

  while (millis() - timeout < 50) { 
    int currVal = analogRead(CH1_PIN);
    if (currVal >= triggerLevel && prevVal < triggerLevel) {
      triggered = true;
      break; 
    }
    prevVal = currVal;
  }

  // 2. جمع البيانات (Sampling) with Software Low-Pass Filter
  for (int i = 0; i < BUFFER_SIZE; i++) {
    int rawCH1 = analogRead(CH1_PIN);
    int rawCH2 = analogRead(CH2_PIN);

    // Apply the Exponential Moving Average formula
    filteredCH1 = (filterAlpha * rawCH1) + ((1.0 - filterAlpha) * filteredCH1);
    filteredCH2 = (filterAlpha * rawCH2) + ((1.0 - filterAlpha) * filteredCH2);

    // Store the filtered values in the buffer
    ch1Buffer[i] = (int)filteredCH1;
    ch2Buffer[i] = (int)filteredCH2;

    // تأخير بسيط لجعل الموجة أوضح 
    if(timebaseDelay > 0) delayMicroseconds(timebaseDelay);
  }

  // 3. إرسال البيانات للـ Serial Plotter
  // يتم إرسال القيمتين بجانب بعضهما ليرسمهما الـ Plotter كخطين منفصلين
  for (int i = 0; i < BUFFER_SIZE; i++) {
    Serial.print(22*((ch1Buffer[i] * 3.3/4096.0)-1.5)/1.41);
    Serial.print(","); // فاصل بين القناتين
    Serial.println(22*((ch2Buffer[i] * 3.3/4096.0)-1.5)/1.41);
  }

  // إرسال قيم ثابتة لعمل "فراغ" أو علامة نهاية الدفعة (اختياري)
  // Serial.println("0,0"); 
}
