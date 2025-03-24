#include <iostream>
#include <iomanip>

using namespace std;

double calculateBMI(double weight, double height){
    return weight / (height * height);
}

string getBMICategory(double bmi){
    if(bmi < 18.5){
        return "Underweight";
    }
    else if(bmi < 24.9){
        return "Normal weight";
    }
    else if(bmi < 29.9){
        return "Overweight";
    }
    else {
        return "Obese";
    }
}

int main(){
    double weight;
    double height;

    cout << "Enter weight: " << endl;
    cin >> weight;
    cout << "Enter height: " << endl;
    cin >> height;

    if(weight <= 0 || height <= 0){
        cout << "Invalid" << endl;
        return 1;
    }

    double bmi = calculateBMI(weight, height);

    cout << fixed << setprecision(2);
    cout << "BMI is: " << bmi << endl;
    cout << "Category is: " << getBMICategory(bmi) << endl;

    return 0;
}
