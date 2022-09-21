int waktu_sebelumnya = 0;
int logika_led = 0;

void setup() {
    // put your setup code here, to run once:
    pinMode(13, OUTPUT);
}

void loop() {
    // put your main code here, to run repeatedly:
    unsigned long waktu_sekarang = millis();
    if(waktu_sekarang - waktu_sebelumnya >= 1000){
        waktu_sebelumnya = waktu_sekarang;

        if (logika_led == 0){
            logika_led = 1;
        }
        else {
            logika_led = 0;
        }

        digitalWrite(13, logika_led);
    }
}