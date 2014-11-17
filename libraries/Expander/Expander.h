#ifndef Expander_h
#define Expander_h

class Expander {
  public:
    Expander(int address);
    void init();
    void test();
    void send();
    void clearOutputs();
    void setSingleOutput(int index, bool signal);

  private:
    const static int _outputs_size = 16;
    int _address;
    bool _outputs[16]; // 0-7 - port A, 8-15 - port B
};

#endif
