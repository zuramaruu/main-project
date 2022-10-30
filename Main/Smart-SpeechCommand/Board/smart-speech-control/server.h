#pragma once

struct Serv {
    void Init();
    bool send(int data);
    String read(uint8_t indx);

  private:
    String parseStr(String data,
                    char separator[],
                    int index);
    void initWifi();
    uint8_t wifiStatus;
    uint32_t srvTMr;
    void errMsg();
};

extern Serv server;
