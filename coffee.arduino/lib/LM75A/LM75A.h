// LM75A - Library for accessing temperature data from LM75A chips

#ifndef LM75A_h
#define LM75A_h

class LM75A {
  public:
    LM75A(int address);
    float get_temp();
  private:
    int _address;
};

#endif
