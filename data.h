class data
{
private:
    float temperature;
public:
    data();
    void setTemperature(float _temperature);
    void setTemperature(int _temperature);
    float getTemperature();
    char* toCharTemprature();
    ~data();
};

data::data()
{
}

data::~data()
{
}

data::setTemperature(float _temperature){
    temperature = _temperature;
}

data::setTemperature(int _temperature){
    temperature = (float)_temperature;
}

float data::getTemperature(){
    return temperature;
}

