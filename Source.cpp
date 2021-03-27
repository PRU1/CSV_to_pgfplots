#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::getline;
using std::stringstream;
void printAll(vector<vector<string>> label, vector<string> coordinatesA, vector<string> coordinatesB) {

    cout << "PRINTING LABELLLLLLLLLLLL:" << endl;
    for (int i = 0; i < label.size(); ++i){
        for (int j = 0; j < label[i].size(); ++j){
            cout << label[i][j];
            cout << " ";
        }
        cout << endl;
    }

    cout << "Printing COOOORDINATESSSSSSS:" << endl;
    for (auto i : coordinatesA) {
        cout << i << " ";
    }
    for (auto i : coordinatesB) {
        cout << i << " ";
    }
        cout << endl << endl << endl;
}
void simpPutParseV3(string& lineParse, vector<string>& lineParseString) { // Separate each line into numbers
    string str = lineParse;

    for (int i = 0, len = str.size(); i < len; i++)
    {
        // check whether parsing character is punctuation or not 
        if (ispunct(str[i]))
        {
            str.erase(i--, 1);
            str.insert(++i, " ");
            len = str.size();
        }
    }

    // print string without punctuation 

        std::string s = str;
        std::istringstream iss(s);
        for (std::string s; iss >> s; ) {
            lineParseString.push_back(s);
        }
}
void vecOfvecAppend(vector<string>& lineParseString, vector<vector<string>>& label){
    label.push_back(lineParseString);
    lineParseString.clear();
}
void axisTitles(string& IV, string& DV, string& title, unsigned int& interval) {
    cout << "Enter the independent variable" << endl;
    cin >> IV;
    cout << "Enter the dependent variable" << endl;
    cin >> DV;
    title = DV + " vs. " + IV;
    cout << "Enter the interval" << endl;
    cin >> interval;
}
void AllCoordinates(vector<vector<string>>& label, vector<string>& coordinatesA, vector<string>& coordinatesB)
{
    //string temp;
    //    temp = "(" + label[0][y] + "," + label[t][y] + ")";
    //    coordinates.push_back(temp);
    //    temp = "";
    string temp;
    for (int i = 0; i < label.size(); ++i){
       temp = "(" + label[i][0] + "," + label[i][1] + ")";
       coordinatesA.push_back(temp);
       temp = "(" + label[i][0] + "," + label[i][2] + ")";
       coordinatesB.push_back(temp);
       temp = "";
    }
}
void leTHING(vector<string>& coordinatesA, vector<string>& coordinatesB, string DV, string IV, unsigned int interval, string title) {
    cout << "\\documentclass{article} \n";
    cout << " \\usepackage[margin = 0.5in]{geometry} \n \\usepackage[utf8]{inputenc} \n \\usepackage{textcomp} \n \\usepackage{pgfplots} \n \\pgfplotsset{width = 10cm,compat = 1.9} \n % \\usepgfplotslibrary{external} \n % \\tikzexternalize \n \n \\begin{document}\n\\begin{tikzpicture}" << endl;
    string AXIS = " \\begin{axis} [ \ntitle = {" + title +"}, \n xlabel = {" + DV + " }, \nylabel = {" + IV + "},\n xmin = 0, xmax = 45,\nymin = 0, ymax = 1000, \nxtick ={ 0,15,30,45 }, \nytick = { 0,200,400,600,800,1000 }, \nlegend pos = north west, \nymajorgrids = true, \ngrid style = dashed, \n]";
    cout << AXIS << endl;
    string addPlot = "\\addplot[ \ncolor = red,\nmark = square,\n] \ncoordinates{\n";
    cout << addPlot;
    for (auto i : coordinatesA) {
        if (i == coordinatesA.back()) {
            cout << " ";
        }
        else {
            cout << i;
        }
    }
    cout << "}; \n \\end{axis}\n\\end{tikzpicture}\n\\end{document}\n ";
}
int main() {
    string IV, DV, title;
    unsigned int interval{};
    vector<string> lineParseString;
    vector<vector<string>> label;
    vector<string> coordinatesA;
    vector<string> coordinatesB;
    string fileName;
    string file = "C:/Users/pranav/Desktop/";
    string lineParse;
    cout << "Enter the file name, excluding .CSV. Make sure it's on desktop \n";
    cin >> fileName;
    file += fileName;
    file += ".csv";
    ifstream csvFile(file);
    if (csvFile.fail()) {
        while (csvFile.fail()) {
            cout << "File not found. Enter the file name again:" << endl;
            cin >> fileName;
        }
    }
    else {
    axisTitles(IV, DV, title, interval);
        if (csvFile.is_open()) {
            while (getline(csvFile, lineParse)) {
                //simpPutParse(lineParse, lineParseString);
                simpPutParseV3(lineParse, lineParseString);
                vecOfvecAppend(lineParseString, label);
            }
            csvFile.close();
        }
        AllCoordinates(label, coordinatesA, coordinatesB);
        printAll(label, coordinatesA, coordinatesB);
        leTHING(coordinatesA, coordinatesB, DV, IV, interval, title);
    }
    cin.get();
    cin.get();
    return 0;
}
