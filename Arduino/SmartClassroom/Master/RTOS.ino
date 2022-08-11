void RTOS_Init() {
  xTaskCreatePinnedToCore(
    SerialTask_callback,   /* Task function. */
    "SerialTask",     /* name of task. */
    20000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &SerialTask,      /* Task handle to keep track of created task */
    1);       /* pin task to core 0 */
}
