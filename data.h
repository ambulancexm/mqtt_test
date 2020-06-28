class Data
{
private:
    char* name;
    int pin;
    float value;
    int num;

public:
    static int nb;
    Data();
    Data(int _pin);

    char* getName();
    void setName(char* _name);
    //void setName(String _name);

    int getNum();
    void setNum(int _num);
    
    int getPin();
    void setPin(int _pin);

    float getValue();
    void setValue(float _value);
    void setValue(int _value);
    

    ~Data();
};

int Data::nb = 0;

Data::Data()
{
    nb++;
    num = nb;
}

Data::Data(int _pin)
{
    nb++;
    num = nb;
    pin = _pin;
}

Data::~Data()
{
}

// Value
void Data::setValue(float _value)
{
    value = _value;
}

void Data::setValue(int _value)
{
    value = (float)_value;
}

float Data::getValue()
{
    return value;
}
int Data::getNum()
{
    return num;
}

int Data::getPin()
{
    return pin;
}

char* Data::getName(){
    return name;
}
void Data::setName(char* _name){
    name = _name;
}
// void Data::setName(String _name){

//     name = "_name";
// }