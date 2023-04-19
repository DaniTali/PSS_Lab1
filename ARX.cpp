#include "ARX.h"

ARX::ARX() :nA(0), nB(0), nk(0) {
    pamiecU = nullptr;
    pamiecY = nullptr;
    paramA = nullptr;
    paramB = nullptr;
}

ARX::ARX(int nk, int nA, int nB)
{
    this->nA = nA;
    this->nB = nB;
    this->nk = nk;

    if (pamiecU == nullptr)
        pamiecU = new std::vector<double>(nB + nk);
    if (pamiecY == nullptr)
        pamiecY = new std::vector<double>(nA);
    if (paramA == nullptr)
        paramA = new std::vector<double>(nA + 1);
    if (paramB == nullptr)
        paramB = new std::vector<double>(nB + 1);

}

double ARX::symuluj(double u)
{
    
    std::vector<double> wektorY = *pamiecY;
    std::transform(wektorY.begin(), wektorY.end(), wektorY.begin(),
        std::bind1st(std::multiplies<double>(), (-1)));

    double y = std::inner_product(pamiecU->begin(), pamiecU->end(), paramB->begin(), 0.0);
    y = y + std::inner_product(wektorY.begin(), wektorY.end(), paramA->begin() + 1, 0.0);

    pamiecY->emplace(pamiecY->begin(), y);
    pamiecY->pop_back();
    //std::cout << "y = " << y << std::endl;
    pamiecU->emplace(pamiecU->begin(), u);
    pamiecU->pop_back();

    return *pamiecY->begin();
}

int ARX::ustawStopnie(int nk, int nA, int nB)
{
    this->nA = nA;
    this->nB = nB;
    this->nk = nk;
    return 0;
}

void ARX::wypiszStopnie()
{
    std::cout << "Stopnie wielomianow: nk = " << nk <<
        ", nA = " << nA << ", nB = " << nB << std::endl;

}

void ARX::wpiszParametry()
{
    if (nA > 0) {
        std::vector<double>& wielomianA = *paramA;
        std::cout << "Wpisz parametry wielomianu A" << std::endl;
        //paramA->operator[](1) = 1;
        wielomianA[0] = 1;
        std::cout << "a(0) = " << wielomianA[0] << std::endl;
        for (auto i = 1; i <= nA; i++) {
            std::cout << "a(" << i << ") = ";
            std::cin >> wielomianA[i];

        }

    }

    if (nB > 0) {
        std::vector<double>& wielomianB = *paramB;
        std::cout << "Wpisz parametry wielomianu B" << std::endl;

        for (auto i = 0; i <= nB; i++) {
            std::cout << "b(" << i << ") = ";
            std::cin >> wielomianB[i];

        }

    }


}

void ARX::wypiszWielomiany()
{
    if (nA > 0) {
        std::cout << "Wielomian A:\n";
        for (auto i = paramA->begin(); i != paramA->end(); i++) {
            std::cout << "a(" << i - paramA->begin() <<
                ") = " << *i;
            if (i != paramA->end())
                std::cout << "; ";
        }
    }

    std::cout << std::endl;
    if (nB > 0) {
        std::cout << "Wielomian B:\n";
        for (auto i = paramB->begin(); i != paramB->end(); i++) {
            std::cout << "b(" << i - paramB->begin() <<
                ") = " << *i;
            if (i != paramB->end())
                std::cout << "; ";
        }
    }
    std::cout << std::endl;

}

ARX::~ARX()
{
    if (paramA != nullptr) {
        delete paramA;
        //std::cout << "Zwolniona pamiec paramA\n";
    }

    if (paramB != nullptr) {
        delete paramB;
        //std::cout << "Zwolniona pamiec paramB\n";
    }

    if (pamiecU != nullptr) {
        delete pamiecU;
        //std::cout << "Zwolniona pamiec pamiecU\n";
    }

    if (pamiecY != nullptr) {
        delete pamiecY;
        //std::cout << "Zwolniona pamiec pamiecY\n";
    }


}

int ARX::wpiszParametry( std::vector<double>* wektorA, std::vector<double>* wektorB)
{
    
    if (paramA == nullptr) {
        paramA = new std::vector<double>;
    }
    *paramA = *wektorA;
    nA = paramA->size() - 1;

    if (paramB == nullptr) {
        paramB = new std::vector<double>;
    }
    *paramB = *wektorB;
    nB = paramB->size() - 1;

    return 0;
}

std::vector<std::vector<double>> ARX::wypiszParametry()
{
    std::vector<std::vector<double>> wektorParametrow;
    wektorParametrow.push_back(*paramA);
    wektorParametrow.push_back(*paramB);
    return wektorParametrow;

}



