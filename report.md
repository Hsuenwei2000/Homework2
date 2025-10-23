# 41343126

作業二

## Problem : Polynomial

### 解題思路與策略

#### 問題分析:

| 項目                        | 說明                                    |
| ------------------------- | ------------------------------------- |
| **1. 建立 Polynomial 類別**   | 必須符合 ADT（抽象資料型態）的定義，具有操作多項式的基本功能。     |
| **2. 定義資料結構（Figure 2）**   | 使用 `degree` 表示最高次方，用 `coef[]` 陣列儲存係數。 |
| **3. 撰寫輸入/輸出函式，並使用運算子多載** | 必須重載 `>>` 與 `<<` 讓多項式能以自然語法進行輸入輸出。    |


**多項式（Polynomial）是一種以多個係數表示的數學結構，例如：**

$𝑃(𝑥)=3𝑥^3+2𝑥^2−5$

**思考電腦如何儲存:**

| 指數 i    | 0  | 1  | 2  | 3  | … | n  |
| ------- | -- | -- | -- | -- | - | -- |
| coef[i] | a₀ | a₁ | a₂ | a₃ | … | aₙ |

可以儲存為一個動態陣列 **coef[]**：

| 指數 i       | 3 | 2 | 1 | 0  |
| ---------- | - | - | - | -- |
| 係數 coef[i] | 3 | 2 | 0 | -5 |

Example Output:

*degree = 3;*

*coef = [ -5, 0, 2, 3 ];*

*這對應到 Figure 2 的內容：*

```cpp
private:
    int degree;
    double *coef;
```

#### 定義類別行為（Figure 1 的 ADT）

根據 ADT 概念，Polynomial 類別應支援以下操作：

| 操作            | 數學意義  | 實作            |
| ------------- | -------- | --------------- |
| 建構子 / 解構子     | 建立與釋放多項式 | 配置與釋放動態記憶體      |
| `operator >>` | 輸入多項式    | 讀入 degree 與各項係數 |
| `operator <<` | 輸出多項式    | 依照數學格式印出        |
| `operator +`  | 多項式加法    | 對應指數相同的係數相加     |
| `operator -`  | 多項式減法    | 對應指數相同的係數相減     |
| `operator *`  | 多項式乘法    | 每一項兩兩相乘並加總      |
| `evaluate(x)` | 計算 P(x)  | Horner’s method |

#### 設計與規劃階段

在撰寫程式前，先列出邏輯與設計要點：

(1) 資料結構規劃

使用 double* coef 儲存係數。

動態配置陣列大小為 degree + 1。

若多項式重新輸入，先 delete[] coef 再重新配置。

(2) 運算子多載策略

輸入 (>>) 與輸出 (<<) 需設為 friend 函式，因為它們不是類別成員，但要存取私有資料。

加、減、乘運算子可設為 const 成員函式，回傳新的 Polynomial。

(3) 記憶體安全

Copy constructor（防止淺拷貝錯誤）

Assignment operator（深拷貝）

Destructor（釋放記憶體）

(4) 效能思考

evaluate() 採用 Horner’s Method：
時間複雜度 O(n)，比逐項乘法更快。

#### 思考脈絡總結圖

題目要求

   ↓
   
分析 Figure 1 (ADT)

   ↓
   
決定要有哪些操作 (輸入 / 輸出 / 加減乘 / 求值)

   ↓
   
分析 Figure 2 (data members)

   ↓
   
設計類別結構 (degree, coef[])

   ↓
   
實作記憶體管理與多載運算子

   ↓
   
驗證運算正確性與效能分析


### C++ 程式碼

```cpp
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

/*
 * Polynomial class — represent a polynomial like:
 * P(x) = a0 + a1*x + a2*x^2 + ... + an*x^n
 *
 * 功能重點：
 *  支援運算子多載：
 *      >> ：輸入多項式
 *      << ：輸出多項式
 *      +, -, * ：多項式的四則運算
 *  使用動態記憶體儲存係數陣列
 */
class Polynomial {
private:
    int degree;      // Highest exponent（最高次方數）
    double *coef;    // Coefficient array（係數陣列）

public:
    // Constructor 建構子：初始化係數為0
    Polynomial(int deg = 0) {
        degree = deg;
        coef = new double[degree + 1];
        for (int i = 0; i <= degree; ++i)
            coef[i] = 0;
    }

    // Copy constructor 複製建構子
    Polynomial(const Polynomial &rhs) {
        degree = rhs.degree;
        coef = new double[degree + 1];
        for (int i = 0; i <= degree; ++i)
            coef[i] = rhs.coef[i];
    }

    // Destructor 解構子：(釋放記憶體)
    ~Polynomial() {
        delete[] coef;
    }

    //Assignment operator 多載 = 運算子

    Polynomial &operator=(const Polynomial &rhs) {
        if (this == &rhs) return *this;  // 避免自我指派
        delete[] coef;
        degree = rhs.degree;
        coef = new double[degree + 1];
        for (int i = 0; i <= degree; ++i)
            coef[i] = rhs.coef[i];
        return *this;
    }

    //Input operator >> 多載：輸入多項式
    //讀入 degree 與各次方的係數

    friend istream &operator>>(istream &in, Polynomial &p) {
        cout << "Enter degree: ";
        in >> p.degree;
        delete[] p.coef;                     // 清除舊資料
        p.coef = new double[p.degree + 1];   // 重新配置記憶體

        cout << "Enter coefficients (from x^0 to x^" << p.degree << "):\n";
        for (int i = 0; i <= p.degree; ++i)
            in >> p.coef[i];
        return in;
    }

    //Output operator << 多載：輸出多項式
    //將多項式以可讀格式輸出，例如 3x^2+2x-5

    friend ostream &operator<<(ostream &out, const Polynomial &p) {
        bool firstTerm = true;
        for (int i = p.degree; i >= 0; --i) {
            if (fabs(p.coef[i]) < 1e-9) continue; // 跳過係數為0的項

            // 正號處理：若非第一項且係數為正，需加 "+"
            if (!firstTerm && p.coef[i] > 0)
                out << "+";
            firstTerm = false;

            out << p.coef[i];          // 輸出係數
            if (i > 0) out << "x";     // 若不是常數項，印出 x
            if (i > 1) out << "^" << i; // 若次方大於1，加上指數
        }
        if (firstTerm) out << "0";     // 若所有項都是0
        return out;
    }

    //Polynomial addition (+)

    Polynomial operator+(const Polynomial &rhs) const {
        int maxDeg = max(degree, rhs.degree);
        Polynomial sum(maxDeg);
        for (int i = 0; i <= maxDeg; ++i) {
            double a = (i <= degree) ? coef[i] : 0;
            double b = (i <= rhs.degree) ? rhs.coef[i] : 0;
            sum.coef[i] = a + b;
        }
        return sum;
    }

    //Polynomial subtraction (-)

    Polynomial operator-(const Polynomial &rhs) const {
        int maxDeg = max(degree, rhs.degree);
        Polynomial diff(maxDeg);
        for (int i = 0; i <= maxDeg; ++i) {
            double a = (i <= degree) ? coef[i] : 0;
            double b = (i <= rhs.degree) ? rhs.coef[i] : 0;
            diff.coef[i] = a - b;
        }
        return diff;
    }

    //Polynomial multiplication (*)

    Polynomial operator*(const Polynomial &rhs) const {
        Polynomial prod(degree + rhs.degree);
        for (int i = 0; i <= degree; ++i)
            for (int j = 0; j <= rhs.degree; ++j)
                prod.coef[i + j] += coef[i] * rhs.coef[j];
        return prod;
    }

    //Evaluate polynomial at a given x

    double evaluate(double x) const {
        double result = 0;
        for (int i = degree; i >= 0; --i)
            result = result * x + coef[i];
        return result;
    }
};

int main() {
    Polynomial p1, p2;

    cout << "Input Polynomial P1:\n";
    cin >> p1;  //使用多載 >> 進行輸入

    cout << "Input Polynomial P2:\n";
    cin >> p2;  //使用多載 >> 進行輸入

    cout << "\nP1(x) = " << p1 << endl;  //使用多載 << 輸出
    cout << "P2(x) = " << p2 << endl;    //使用多載 << 輸出

    Polynomial sum = p1 + p2;   //使用多載 + 運算子
    Polynomial diff = p1 - p2;  //使用多載 - 運算子
    Polynomial prod = p1 * p2;  //使用多載 * 運算子

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
```

### 效能分析

| 操作       | 時間複雜度        | 空間複雜度        | 說明              |
| -------- | ------------ | ------------ | --------------- |
| 輸入 / 輸出  | O(n)         | O(n)         | 需輸入所有係數         |
| 加法 / 減法  | O(max(n, m)) | O(max(n, m)) | 遍歷所有次方          |
| 乘法       | O(n × m)     | O(n + m)     | 雙重迴圈乘法          |
| Evaluate | O(n)         | O(1)         | Horner’s Method |

	![範例輸出入](https://lurl.cc/Pstzz)
