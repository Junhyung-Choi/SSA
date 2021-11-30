#pragma config(Sensor, S1,     c1,             sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2,     gs,             sensorEV3_Gyro, modeEV3Gyro_RateAndAngle)
#pragma config(Sensor, S3,     c3,             sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S4,     ss,             sensorEV3_Ultrasonic)
#pragma config(Motor,  motorB,          lm,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rm,    tmotorEV3_Large, PIDControl, driveRight, encoder)


int calcBound2()
{
    int bound;
    int black = 0;
    int white = 0;

    for(int i =0; i < 10; i++)
    {
        black += getColorReflected(c1);
        black += getColorReflected(c3);
        sleep(10);
    }

    setMotorSpeed(lm,10);
    setMotorSpeed(rm,10);
    sleep(1000);
    setMotorSpeed(lm,0);
    setMotorSpeed(rm,0);

    for(int i = 0; i < 10;i++)
    {
        white += getColorReflected(c1);
        white += getColorReflected(c3);
        sleep(10);
    }

    bound = (white/20 + black/20)/2;

    return bound;
}


task main(){
    int gray = calcBound2();
    while(1)
    {
        int left = getColorReflected(c1);
        int right = getColorReflected(c3);

        if (left>= gray && right >= gray)
        {
            setMotorSpeed(lm,40);
            setMotorSpeed(rm,40);
        }
        else if (left >= gray && right < gray)
        {
            setMotorSpeed(lm,30);
            setMotorSpeed(rm,-20);
        }
        else if(left < gray && right >= gray)
        {
            setMotorSpeed(lm,-20);
            setMotorSpeed(rm,30);
        }
        else
        {
            setMotorSpeed(lm,10);
            setMotorSpeed(rm,-10);
        }
    }
}
//else 부분 턴 넣어봤습니다~
