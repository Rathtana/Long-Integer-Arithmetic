#include "LongInt.h"

/**
 * A constructor that takes in a string and initialize the object
 *
 * @param str
 */
LongInt::LongInt(const string str) {
    if (str[0] == '-') {
        negative = true;
    } else {
        negative = false;
    }

    for (int i = 0; i < str.length(); i++) {
        if(str[i] != 'x')
            digits.addBack(str[i]);
    }
    remove0s();
}

/**
 * A default constructor
 */
LongInt::LongInt() {
    negative = false;
}

/**
 * A copy constructor that perform a deep copy
 * on a LongInt object
 *
 * @param rhs
 */
LongInt::LongInt(const LongInt &rhs) {
    digits = rhs.digits;
    negative = rhs.negative;
}

/**
 * A desturctor that free/clear the list
 */
LongInt::~LongInt() {
    digits.clear();
}

/**
 * A method that remove any leading 0s from LongInt
 */
void LongInt::remove0s() {
    int size = digits.size();
    if(negative) {
       digits.removeFront();
    }
    for(int i = 0; i < size-1; i++) {
        if(digits.getFront() - '0' != 0) {
            if(negative && digits.size() != 0) {
                digits.addFront('-');
            }
            break;
        }
        digits.removeFront();
    }

}
/**
 * An = method that perform a deep copy of rhs LongInt
 *
 * @param rhs
 * @return result from copying the list
 */
const LongInt &LongInt::operator=(const LongInt &rhs) {
    digits = rhs.digits;
    negative = rhs.negative;

    return *this;
}
/**
 * Assignment < operator that check wheather the LHS LongInt is
 * less than the RHS
 *
 * @param rhs
 * @return true if LHS < RHS and false otherwise
 */
bool LongInt::operator<(const LongInt &rhs) const {

    Deque<char> lhsList = digits;
    Deque<char> rhsList = rhs.digits;

    int lhsValue;
    int rhsValue;

    int sameSize = lhsList.size();

    if (negative && !(rhs.negative)) {
        return true;
    } else if (!negative && rhs.negative) {
        return false;
    }
        //both negative
    else if (negative && rhs.negative) {

        if (digits.size() > rhs.digits.size()) {
            return true;
        } else if (digits.size() < rhs.digits.size()) {
            return false;
        } else { //both negative and have the same length
            //get ride of '-' sign
            lhsValue = lhsList.removeFront();
            rhsValue = rhsList.removeFront();
            sameSize--;


            for (int i = 0; i < sameSize; i++) {
                lhsValue = lhsList.removeFront() - '0';
                rhsValue = rhsList.removeFront() - '0';

                if (lhsValue < rhsValue) {
                    return false;
                } else if (lhsValue > rhsValue) {
                    return true;
                }
            }
        }
    }
        //for both positive value
    else {
        if (digits.size() > rhs.digits.size()) {
            return false;
        } else if (digits.size() < rhs.digits.size()) {
            return true;
        }
            //same length
        else {
            for (int i = 0; i < sameSize; i++) {
                lhsValue = lhsList.removeFront() - '0';
                rhsValue = rhsList.removeFront() - '0';

                if (lhsValue < rhsValue) {
                    return true;
                } else if (lhsValue > rhsValue) {
                    return false;
                }
            }

        }
    }
    return false;

}
/**
 * Assignment > operator that check if the RHS > LHS.
 *
 * @param rhs
 * @return true if RHS > LHS and false otherwise
 */
bool LongInt::operator>(const LongInt &rhs) const {
    if (*this == rhs) {
        return false;
    }

    return !(*this < rhs);
}
/**
 * Assignment == that check wheather the RHS is equal to LHS
 *
 * @param rhs
 * @return true if RHS == LHS and false otherwise
 */
bool LongInt::operator==(const LongInt &rhs) const {

    if (digits.size() == rhs.digits.size() && negative == rhs.negative) {
        Deque<char> lhsList = digits;
        Deque<char> rhsList = rhs.digits;

        int lhsValue;
        int rhsValue;

        int lhsSize = lhsList.size();

        //for both negative
        if (negative) {
            //get rid of the '-' sign
            lhsValue = lhsList.removeFront();
            rhsValue = rhsList.removeFront();
            lhsSize--;
        }

        for (int i = 0; i < lhsSize; i++) {
            lhsValue = lhsList.removeFront() - '0';
            rhsValue = rhsList.removeFront() - '0';

            if (lhsValue > rhsValue || lhsValue < rhsValue) {
                return false;
            }
        }
        return true;
    }
    return false;

}
/**
 * Assignment != operator that check to see if RHS does not
 * equal LHS
 *
 * @param rhs
 * @return true if RHS != LHS and false otherwise
 */
bool LongInt::operator!=(const LongInt &rhs) const {
    return !(*this == rhs);
}
/**
 * Assignment <= operator that check to see if RHS is less
 * than or equal to  LHS
 *
 * @param rhs
 * @return true f RHS <= LHS and false otherwise
 */
bool LongInt::operator<=(const LongInt &rhs) const {

    if (*this == rhs) {
        return true;
    }
    return (*this < rhs);
}
/**
 * Assignment >= operator that check to see if RHS is greater than
 * or equal to the LHS
 *
 * @param rhs
 * @return true if RHS >= LHS and false otherwise
 */
bool LongInt::operator>=(const LongInt &rhs) const {

    if (*this == rhs) {
        return true;
    }
    return (*this > rhs);
}
/**
 * Arithmetic binary operator for adding two LongInt object.
 * This can add POS with POS, NEG with NEG, NEG with POS, and
 * POS with NEG.
 * Leading 0s will also be removed in the final result
 *
 * @param rhs
 * @return result from the addition
 */
LongInt LongInt::operator+(const LongInt &rhs) const {

    LongInt lhsList(*this);
    LongInt rhsList(rhs);
    LongInt result;

    // lhs is negative and rhs is positive
    if(this->negative && !(rhs.negative)) {

        //remove the negative sign
        lhsList.digits.removeFront();
        lhsList.negative = false;

        if(lhsList > rhsList) {
            result = lhsList - rhsList;
            result.digits.addFront('-');
            result.negative = true;


            return result;
        }
        else {
            //when rhs => lhs (after removing the negative sign)
            result = rhsList - lhsList;
            return result;
        }
    }
    //lhs is positive and lhs is negative
    else if(!(this->negative) && rhs.negative) {

        //remove the negative sign
        rhsList.digits.removeFront();
        rhsList.negative = false;

        if(rhsList > lhsList) {
            result = rhsList - lhsList;
            result.digits.addFront('-');
            result.negative = true;
            result.remove0s();
            return result;
        }
            //lhs >= lhs (after removing the negative sign)
        else {
            result = lhsList - rhsList;
            result.remove0s();
            return result;
        }
    }

    int carrier = 0;
    int lhsVal;
    int rhsVal;
    int value;

    bool bothNegative = false;

    int lhsSize = lhsList.digits.size();
    int rhsSize = rhsList.digits.size();

    int maxDigLength = max(lhsSize, rhsSize);

    if (lhsList.negative && rhsList.negative) {
        maxDigLength = max(lhsList.digits.size() - 1, rhsList.digits.size() - 1);
        bothNegative = true;

        lhsSize--;
        rhsSize--;
    }

    for (int i = 0; i < maxDigLength; i++) {
        if (lhsSize > 0 && rhsSize > 0) {

            lhsSize--, rhsSize--;

            //remove and retrieve value as integer
            lhsVal = lhsList.digits.removeBack() - '0';
            rhsVal = rhsList.digits.removeBack() - '0';
            value = lhsVal + rhsVal + carrier;

        } else {
            if (lhsSize > 0) {
                lhsSize--;
                lhsVal = lhsList.digits.removeBack() - '0';

                value = lhsVal + carrier;

            } else {
                rhsSize--;
                rhsVal = rhsList.digits.removeBack() - '0';
                value = rhsVal + carrier;

            }
        }
        if (value > 9) {
            //conver back to ASSCi code
            result.digits.addFront(value % 10 + '0');
            carrier = value / 10;
        } else {
            //convert back to assci code
            result.digits.addFront(value + '0');
            carrier = 0;
        }
    }
    if (carrier != 0)
        result.digits.addFront(carrier + '0');

    if (bothNegative) {
        result.digits.addFront('-');
        result.negative = true;
    }

    result.remove0s();
    return result;
}
/**
 * Arithmetic binary operator for subtracting two LongInt Oojects.
 * This allows you to subtract from POS - POS, POS - NEG, NEG - POS,
 * and NEG - NEG.
 * Final result will also remove any leading 0s
 *
 * @param rhs
 * @return result from the subtraction
 */
LongInt LongInt::operator-(const LongInt &rhs) const {

    LongInt result;
    LongInt lhsList;
    LongInt rhsList;

    int lhsVal;
    int rhsVal;
    int barrowedVal = 0;
    int value;

    bool addMinusSignFront = false;
    bool bothNegative = false;

    //for both positive where lhs < rhs
    if (this->digits.size() <= rhs.digits.size() && *this < rhs
        && !(this->negative) && !(rhs.negative)) {

        lhsList = rhs;
        rhsList = *this;
        addMinusSignFront = true;

    }
        //for both negative
    else if (this->negative && rhs.negative) {
        //lsh > rhs
        if (*this > rhs) {
            lhsList = rhs;
            rhsList = *this;
        }
            //lsh < rhs
        else {
            lhsList = *this;
            rhsList = rhs;

            addMinusSignFront = true;
        }
        //remove both minus sign
        lhsList.digits.removeFront();
        rhsList.digits.removeFront();
    }

        //if lhs is negative and rhs is positive
    else if (this->negative && !(rhs.negative)) {
        //add minus sign to front
        lhsList = *this;
        rhsList = rhs;

        //get rid of the negative sign
        lhsList.digits.removeFront();
        lhsList.negative = false;

        result = lhsList + rhsList;

        result.digits.addFront('-');
        result.negative = true;

        result.remove0s();

        return result;

    }
        //if lhs is positive and rhs is negative
    else if (!(this->negative) && rhs.negative) {
        lhsList = *this;
        rhsList = rhs;

        //get rid of the negative sign
        rhsList.digits.removeFront();
        rhsList.negative = false;

        result = lhsList + rhsList;
        result.remove0s();

        return result;
    } else {
        lhsList = *this;
        rhsList = rhs;
    }

    int lhsSize = lhsList.digits.size();
    int rhsSize = rhsList.digits.size();

    int maxSize = lhsSize;

    //lsh will always be longer size
    for (int i = 0; i < maxSize; i++) {
        if (lhsSize > 0 && rhsSize > 0) {
            lhsSize--;
            rhsSize--;

            lhsVal = lhsList.digits.removeBack() - '0' - barrowedVal;
            rhsVal = rhsList.digits.removeBack() - '0';

            barrowedVal = 0;


            if (lhsVal < rhsVal) {
                lhsVal += 10;
                barrowedVal = 1;
            }

            value = lhsVal - rhsVal;

            result.digits.addFront(value + '0');
        } else {
            lhsVal = lhsList.digits.removeBack() - '0' - barrowedVal;
            barrowedVal = 0;
            if (lhsVal < 0) {
                lhsVal += 10;
                barrowedVal = 1;
            }
            value = lhsVal;
            result.digits.addFront(value + '0');
        }
    }
    if(addMinusSignFront) {
        result.digits.addFront('-');
        result.negative = true;
    }
    result.remove0s();

    return result;
}
/**
 * Overloading the << operator for LongInt to be able
 * to display it's characteristic
 *
 * @param out
 * @param rhs
 * @return out
 */
ostream &operator<<(ostream &out, const LongInt &rhs) {
    int i = 0;
    int value;
    if(rhs.digits.isEmpty())
        return out << 0;

    LongInt result(rhs);
    int size = rhs.digits.size();

    if(result.negative) {
        out << result.digits.removeFront();
        i = 1;
    }
    for(i; i < size; i++) {
        value = result.digits.removeFront() - '0';
        out << value;
    }
    return out;
}
/**
 * Overloading the >> operator for LongInt to be able
 * to take in use input and store it in a LongInt object
 *
 * @param in
 * @param rhs
 * @return in
 */
istream &operator>>(istream &in, LongInt &rhs) {
    string s;
    in >> s;

    LongInt result(s);
    rhs = result;

    return in;
}


