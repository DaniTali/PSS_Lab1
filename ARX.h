#pragma once
#include "SISO.h"
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <functional>

class ARX :
    public SISO
{

public:
    ARX();
    ARX(int nk, int nA, int nB);
    double symuluj(double u) override;
    int ustawStopnie(int nk, int nA, int nB);
    void wypiszStopnie();
    void wpiszParametry();
    void wypiszWielomiany();
    ~ARX() override;
    int wpiszParametry( std::vector<double>* wektorA, std::vector<double>* wektorB);
    std::vector<std::vector<double>> wypiszParametry();


private:
    int nk, nA, nB;
    std::vector<double>* paramA, * paramB;
    std::vector<double>* pamiecU, * pamiecY;


};

