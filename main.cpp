// Project UID db1f506d06d84ab787baf250c265e24e

#include <iostream>
#include <set>
#include <utility>
#include <sstream>
#include <cstring>
#include <cmath>
#include "csvstream.h"
using namespace std;

class Piazza {
public:

    //Constructor
    Piazza() {};

    void check() {
        cout << "classes:" << endl;

        for (auto i = names.begin(); i != names.end(); ++i) {
            int labels = c[*i];
            cout << "  " << *i << ", " << labels << " examples, log-prior = "
                << log((double)labels / posts) << endl;
        }

        cout << "classifier parameters:" << endl;

        for (auto i = names.begin(); i != names.end(); ++i) {
            for (auto j = total.begin(); j != total.end(); ++j) {
                int num = cw[pair<string, string>(*i, *j)];
                if (0 != num) {
                    int justC = c[*i];
                    double numLog = log((double)num / justC);
                    cout << "  " << *i << ":" << *j << ", count = "
                        << num << ", log-likelihood = " << numLog
                        << endl;
                }
            }
        }
        cout << "\n";
    }

    void proccesing(string& file, bool& check) {
        int x = 0;
        map<string, string> row;

        ifstream i(file);
        if (!(i.is_open())) {
            cout << "Error opening file: " << file << endl;
        }

        csvstream name(i);
        if (check) {
            cout << "training data:" << endl;
        }

        while (name >> row) {
            string name = row["tag"];
            set<string> words = differentWords(row["content"]);

            if (check) {
                cout << "  " << "label = " << name << ", content = " << row["content"]
                    << endl;
            }

            c.insert({ name, 0 });
            c[name]++;
            names.insert(name);

            for (auto i = words.begin(); i != words.end(); i++) {
                total.insert(*i);
                cw.insert({ pair<string, string>(name, *i), 0 });
                cw[pair<string, string>(name, *i)]++;
                w.insert({ *i, 0 });
                w[*i]++;
            }
            x++;
        }

        posts = x;
        words = total.size();
        cout << "trained on " << posts << " examples" << endl;

        if (check) {
            cout << "vocabulary size = " << words
                << "\n" << endl;
        }

        if (!(check)) {
            cout << "\n" << endl;
        }
        else {
            cout << endl;
        }
        row.clear();
    }

    pair<double, string> prediction(string post) {
        vector<pair<double, string>> guess;

        ifstream i(post);
        if (!(i.is_open())) {
            cout << "Error opening file: " << post << endl;
        }

        set<string> check = differentWords(i);
        for (auto i = names.begin(); i != names.end(); i++) {
            double final = 0.0;
            string name = *i;
            int justC = c[name];
            final += log((double)justC / posts);
            for (auto j = check.begin(); j != check.end(); j++) {
                int both = cw
                [pair<string, string>(name, *j)];
                int justW = w[*j];
                if ((0 == both) && (0 == justW)) {
                    final += log(1.0 / posts);
                }
                else if ((0 == both) && (0 != justW)) {
                        final += log((double)justW / posts);
                }
                if (0 != both) {
                    final += log((double)both / justC);
                }
            }
            pair<double, string> prediction(final, name);
            guess.push_back(prediction);
        }
        int max = findNum(guess);
        return guess.at(max);
    }

    set<string> differentWords(const string& str) {
        string choice;
        set<string> words;
        istringstream stream(str);

        while (stream >> choice) {
            words.insert(choice);
        }
        return words;
    }

    void predictFile(string file) {
        int final = 0;
        int right = 0;
        csvstream name(file);
        map<string, string> row;

        cout << "test data:" << endl;

        while (name >> row) {
            string label = row["tag"];
            string str = row["content"];
            pair<double, string> input = prediction(str);
            cout << "  correct = " << label << ", predicted = " << input.second <<
                ", log-probability score = " << input.first << endl <<
                "  content = " << str << "\n" << endl;
            final++;

            if (input.second == label) {
                right++;
            }
        }
        cout << "performance: " << right << " / " <<
            final << " posts predicted correctly" << endl;

        row.clear();
    }

private:

    map<string, int> c;
    map<string, int> w;
    set<string> total;
    set<string> names;
    map<pair<string, string>, int> cw;
    int posts = 0;
    int words = 0;

    int findNum(vector<pair<double, string>>& num) const {
        int max = 0;
        double num2 = num[0].first;
        for (size_t i = 0; i < num.size(); i++) {
            if (num[i].first > num2) {
                num2 = num[i].first;
                max = i;
            }
        }
        return max;
    }
};

int main(int argc, char* argv[]) {

    cout.precision(3);

    bool check = false;
    if (4 == argc) {
        string x = argv[3];
        if ("--debug" != x) {
            cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
            return -1;
        }
        check = true;
    }
    if ((4 != argc) && (3 != argc)) {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return -1;
    }

    Piazza p;
    string training(argv[1]);
    p.proccesing(training, check);

    if (check) {
        p.check();
    }

    string predicting(argv[2]);
    p.predictFile(predicting);
    return 0;
}
