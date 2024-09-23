class Time {
    public:
        Time();
        Time(int Hour , int Minute, int second);
        int getHour()const;
        int getMinute()const;
        int getSecond()const;

        void setHour( int aHour);
        void setMinute(int aMinute);
        void setSecond(int asecond);
        void PrintAMPM() const;

    private:
        int hour;
        int minute;
        int second;


};