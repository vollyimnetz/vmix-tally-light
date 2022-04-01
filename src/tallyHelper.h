int hexcolorToInt(char upper, char lower) {
    int uVal = (int) upper;
    int lVal = (int) lower;
    uVal = uVal > 64 ? uVal - 55 : uVal - 48;
    lVal = lVal > 64 ? lVal - 55 : lVal - 48;
    uVal = uVal << 4;
    return uVal + lVal;
}