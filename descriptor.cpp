#include "Table.h"
#include "Descriptor.h"

int Descriptor::byObject(int x, bool who) {
    if (who) {
        if (numMyMoney >= x) {
            numMyMoney -= x;
            return 1;
        }
        else
            return 0;
    }
    else
        if (numOponentMoney >= x) {
            numOponentMoney -= x;
            return 1;
        }
        else
            return 0;
};


void Descriptor::whoFinish(int x, bool who) {
    if (who)
        countMyFinish += x;
    else
        countOponentFinish += x;

}

void Descriptor::damage(int x, bool who) {
    if (who)
        Mydamage += x;
    else
        Oponentdamage += x;

}

int Descriptor::win() {
    if (countMyFinish >= MaxFinishVessel || Mydamage >= MaxDamage) {
        std::cout << "you wine" << std::endl;
        return 1;
    }
    if (countOponentFinish >= MaxFinishVessel || Oponentdamage >= MaxDamage) {
        std::cout << "you lose" << std::endl;
        return 1;
    }
    return 0;
};

Table* Descriptor::getDesk() {
    return X;
}
void Descriptor::setDesk(Table* table) {
    X = table;

}
int Descriptor::getMyMoney() {
    return numMyMoney;
}
int Descriptor::getOponentMoney() {
    return numOponentMoney;
}
int Descriptor::getMyDamage() {
    return Mydamage;
}

int Descriptor::getOponentDamage() {
    return Oponentdamage;
}

int Descriptor::getMyVessel() {
    return countMyFinish;
}

int Descriptor::getOponentVessel() {
    return countOponentFinish;
}
