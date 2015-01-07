#include "StructPatte.h"

    StructPatte::StructPatte() {
        StructPatte temp = Patte.getPointMiddle();
        angleCoxa = temp.getAngleCoxa();
        angleFemur = temp.getAngleFemur();
        angleTibia = temp.getAngleTibia();
    }


    StructPatte::StructPatte(StructPatte copy) {
        angleCoxa = copy.getAngleCoxa();
        angleFemur = copy.getAngleFemur();
        angleTibia = copy.getAngleTibia();
    }


    StructPatte::StructPatte(char AngleCoxa, char AngleFemur, char AngleTibia) {
        angleCoxa = AngleCoxa;
        angleFemur = AngleFemur;
        angleTibia = AngleTibia;
    }


    char StructPatte::getAngleCoxa() {
        return angleCoxa;
    }


    char StructPatte::getAngleFemur() {
        return angleFemur;
    }


    char StructPatte::getAngleTibia() {
        return angleTibia;
    }


    void StructPatte::setAngleCoxa(char AngleCoxa) {
        angleCoxa = AngleCoxa;
    }


    void StructPatte::setAngleFemur(char AngleFemur) {
        angleFemur = AngleFemur;
    }


    void StructPatte::setAngleTibia(char AngleTibia) {
        angleTibia = AngleTibia;
    }

