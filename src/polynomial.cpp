#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

/**
 * Polynomial class ¡X represent a polynomial like:
 * P(x) = a0 + a1*x + a2*x^2 + ... + an*x^n
 */
class Polynomial {
private:
    int degree;      // Highest exponent
    double* coef;    // Coefficient array

public:
    // Default constructor
    Polynomial(int deg = 0) {
        degree = deg;
        coef = new double[degree + 1];
        for (int i = 0; i <= degree; ++i)
            coef[i] = 0;
    }

    // Copy constructor
    Polynomial(const Polynomial& rhs) {
        degree = rhs.degree;
        coef = new double[degree + 1];
        for (int i = 0; i <= degree; ++i)
            coef[i] = rhs.coef[i];
    }

    // Destructor
    ~Polynomial() {
        delete[] coef;
    }

    // Assignment operator
    Polynomial& operator=(const Polynomial& rhs) {
        if (this == &rhs) return *this;
        delete[] coef;
        degree = rhs.degree;
        coef = new double[degree + 1];
        for (int i = 0; i <= degree; ++i)
            coef[i] = rhs.coef[i];
        return *this;
    }

    // Input operator >>
    friend istream& operator>>(istream& in, Polynomial& p) {
        cout << "Enter degree: ";
        in >> p.degree;
        delete[] p.coef;
        p.coef = new double[p.degree + 1];
        cout << "Enter coefficients (from x^0 to x^" << p.degree << "):\n";
        for (int i = 0; i <= p.degree; ++i)
            in >> p.coef[i];
        return in;
    }

    // Output operator <<
    friend ostream& operator<<(ostream& out, const Polynomial& p) {
        for (int i = p.degree; i >= 0; --i) {
            if (fabs(p.coef[i]) < 1e-9) continue; // Skip zero coefficients
            if (i != p.degree && p.coef[i] > 0) out << "+";
            out << p.coef[i];
            if (i > 0) out << "x";
            if (i > 1) out << "^" << i;
        }
        return out;
    }

    // Polynomial addition
    Polynomial operator+(const Polynomial& rhs) const {
        int maxDeg = max(degree, rhs.degree);
        Polynomial sum(maxDeg);
        for (int i = 0; i <= maxDeg; ++i) {
            double a = (i <= degree) ? coef[i] : 0;
            double b = (i <= rhs.degree) ? rhs.coef[i] : 0;
            sum.coef[i] = a + b;
        }
        return sum;
    }

    // Polynomial subtraction
    Polynomial operator-(const Polynomial& rhs) const {
        int maxDeg = max(degree, rhs.degree);
        Polynomial diff(maxDeg);
        for (int i = 0; i <= maxDeg; ++i) {
            double a = (i <= degree) ? coef[i] : 0;
            double b = (i <= rhs.degree) ? rhs.coef[i] : 0;
            diff.coef[i] = a - b;
        }
        return diff;
    }

    // Polynomial multiplication
    Polynomial operator*(const Polynomial& rhs) const {
        Polynomial prod(degree + rhs.degree);
        for (int i = 0; i <= degree; ++i)
            for (int j = 0; j <= rhs.degree; ++j)
                prod.coef[i + j] += coef[i] * rhs.coef[j];
        return prod;
    }

    // Evaluate polynomial at a given x
    double evaluate(double x) const {
        double result = 0;
        for (int i = degree; i >= 0; --i)
            result = result * x + coef[i];
        return result;
    }
};

// === Testing Main Program ===
int main() {
    Polynomial p1, p2;

    cout << "Input Polynomial P1:\n";
    cin >> p1;
    cout << "Input Polynomial P2:\n";
    cin >> p2;

    cout << "\nP1(x) = " << p1 << endl;
    cout << "P2(x) = " << p2 << endl;

    Polynomial sum = p1 + p2;
    Polynomial diff = p1 - p2;
    Polynomial prod = p1 * p2;

    cout << "\n[Results]\n";
    cout << "P1 + P2 = " << sum << endl;
    cout << "P1 - P2 = " << diff << endl;
    cout << "P1 * P2 = " << prod << endl;

    double x;
    cout << "\nEnter value of x to evaluate P1(x): ";
    cin >> x;
    cout << "P1(" << x << ") = " << p1.evaluate(x) << endl;

    return 0;
}
