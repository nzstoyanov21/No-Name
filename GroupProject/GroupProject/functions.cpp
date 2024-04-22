#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <string>
#include <random>
#include "../StaticLibrary/functions.h"
#include "../StaticLibrary/front-end.h"

using namespace std;

string currentUser;

// Function to save accounts to a file
void saveAccounts(const map<std::string, Account>& accounts) {
    ofstream outFile("accounts.txt");
    for (const auto& pair : accounts) {
        outFile << pair.first << " " << pair.second.password << " " << pair.second.highScore << endl;
    }
    outFile.close();
}

void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Function to load accounts from a file
void loadAccounts(map<string, Account>& accounts) {
    ifstream inFile("accounts.txt");
    string username, password;
    int number;

    while (inFile >> username >> password >> number) {
        accounts[username] = { password, number };
    }
    inFile.close();
}

void accountScreen() {
    string address = "../TextFiles(Front-end)/quizPort.txt";
    map<string, Account> accounts;
    loadAccounts(accounts); // Load existing accounts

    string username, password;
    int highScore = 0;
    char choice;

    cout << setw(120) << "1. Create Account\n";
    cout << setw(114) << "2. Login\n";
    cout << setw(113) << "3. Exit\n";
    cout << setw(117) << "Enter choice: ";
    cin >> choice;

    switch (choice) {
    case '1': // Create an account
        clear();
        print(address);
        cout << setw(119) << "Enter username: ";
        cin >> username;
        if (accounts.find(username) != accounts.end()) {
            clear();
            print(address);
            cout << setw(135) << "Error: Account with this username already exists!\n";
            accountScreen();
            break;
        }
        else {
            cout << setw(119) << "Enter password: ";
            cin >> password;

            accounts[username] = { password, highScore };
            saveAccounts(accounts); // Save accounts whenever a new account is created
            clear();
            print(address);
            cout << setw(127) << "Account created successfully!\n";
            accountScreen();
            break;
        }

    case '2': // Login
        clear();
        print(address);
        cout << setw(119) << "Enter username: ";
        cin >> username;
        if (accounts.find(username) == accounts.end()) {
            clear();
            print(address);
            cout << setw(135) << "Error: No account found with this username!\n";
            accountScreen();
            break;
        }
        else {
            cout << setw(119) << "Enter password: ";
            cin >> password;
            if (accounts[username].password == password) {
                clear();
                print(address);
                cout << setw(119) << "Login successful!\n";
                currentUser = username;
            }
            else {
                clear();
                print(address);
                cout << setw(125) << "Error: Incorrect password!\n";
                accountScreen();
                break;
            }
        }
        break;

    case '3': // Exit
        clear();
        cout << "Exiting program...\n";
        exit(0);

    default:
        clear();
        print(address);
        cout << setw(135) << "Invalid choice. Please enter a valid option.\n";
        accountScreen();
        break;
    }
}

int random(int min, int max) {
    static random_device rd;
    static mt19937 rng(rd());
    uniform_int_distribution<int> uni(min, max);
    return uni(rng);
}

void shuffle(char arr[], string array[][3], int arrsize) {
    for (int i = 0; i < arrsize; i += 3) {
        int a = random(0, arrsize), b = random(0, arrsize);
        for (int i = 0; i < arrsize; i++) {
            int swapIndex = random(0, arrsize);

            // Swap the questions
            for (int j = 0; j < 3; j++) {
                string temp = array[i][j];
                array[i][j] = array[swapIndex][j];
                array[swapIndex][j] = temp;
            }

            // Swap the corresponding answers to maintain alignment
            char tempChar = arr[i];
            arr[i] = arr[swapIndex];
            arr[swapIndex] = tempChar;
        }
    }
}

void questions(string questions[][3], char answers[], int& score, int numberOfQuestions, int points) {
    string address = "../TextFiles(Front-end)/question.txt";

    for (int i = 0; i < numberOfQuestions; i++) { 
        print(address);
        cout << "   " << questions[i][0] << endl;
        cout << "   " << questions[i][1] << endl;
        cout << "   " << questions[i][2] << endl;
        char userAnswer;
        cout << "  _______________________________________________" << endl;
        cout << " |_______________________________________________|" << endl;
        cout << "   Your answer: ";
        cin >> userAnswer;
        clear();
        if (tolower(userAnswer) == answers[i]) {
            score += points;
        }
    }
}

void test() {
    string easyQuestions[45][3] = {
   {
       "What is H2O commonly known as?",
       "A) Water B) Hydrogen peroxide",
       "C) Helium D) Hydrogen"
   },
   {
       "What does the sum of 45 and 55 equal?",
       "A) 95 B) 100",
       "C) 110 D) 90"
   },
   {
       "What is the default port number for HTTP?",
       "A) 8080 B) 443",
       "C) 80 D) 23"
   },
   {
       "What element is represented by the symbol O?",
       "A) Zinc B) Gold",
       "C) Osmium D) Oxygen"
   },
   {
       "Multiply 10 by 15.",
       "A) 200 B) 100",
       "C) 50 D) 150"
   },
   {
       "Which device is used to store data permanently?",
       "A) RAM B) SSD",
       "C) CPU D) GPU"
   },
   {
       "What is the atomic number of hydrogen?",
       "A) 2 B) 1",
       "C) 3 D) 4"
   },
   {
       "What is 25% of 200?",
       "A) 25 B) 50",
       "C) 75 D) 100"
   },
   {
       "What does RAM stand for in computer terminology?",
       "A) Random Access Memory B) Read Access Memory",
       "C) Run Access Memory D) Rapid Access Module"
   },
   {
       "What is the chemical formula for table salt?",
       "A) NaCl B) KCl",
       "C) LiCl D) BeCl2"
   },
   {
       "Subtract 100 from 450.",
       "A) 350 B) 300",
       "C) 400 D) 250"
   },
   {
       "What is the main component of the Sun?",
       "A) Oxygen B) Helium",
       "C) Hydrogen D) Carbon"
   },
   {
       "Who is known as the father of computers?",
       "A) Charles Babbage B) Alan Turing",
       "C) Thomas Edison D) Nikola Tesla"
   },
   {
       "What do you call a substance made of only one type of atom?",
       "A) Compound B) Molecule",
       "C) Element D) Mixture"
   },
   {
       "What does 'www' stand for in a website address?",
       "A) World Wide Web B) Wide Web World",
       "C) Web World Wide D) Web Wide World"
   },
   {
       "Add 243 and 642.",
       "A) 885 B) 895",
       "C) 775 D) 805"
   },
   {
       "What gas do plants absorb from the atmosphere?",
       "A) Carbon dioxide B) Oxygen",
       "C) Nitrogen D) Hydrogen"
   },
   {
       "What type of device is a mouse?",
       "A) Output B) Input",
       "C) Storage D) Network"
   },
   {
       "What is the periodic table?",
       "A) A list of elements B) A scientific theory",
       "C) A type of data structure D) A mathematical model"
   },
   {
       "Divide 1200 by 40.",
       "A) 30 B) 20",
       "C) 40 D) 50"
   },
   {
       "What is the pH of pure water?",
       "A) 7 B) 5",
       "C) 9 D) 11"
   },
   {
       "What is the name of the process by which plants make their food?",
       "A) Respiration B) Photosynthesis",
       "C) Fermentation D) Digestion"
   },
   {
       "What does USB stand for?",
       "A) Universal Serial Bus B) Unified System Bridge",
       "C) Universal System Bus D) Unified Serial Bridge"
   },
   {
       "What is the hardest natural substance on Earth?",
       "A) Gold B) Iron",
       "C) Diamond D) Quartz"
   },
   {
       "What element is represented by the symbol Na?",
       "A) Sodium B) Neon",
       "C) Nitrogen D) Nickel"
   },
   {
       "Calculate the area of a rectangle with sides 5 meters and 10 meters.",
       "A) 50 m^2 B) 15 m^2",
       "C) 25 m^2 D) 75 m^2"
   },
   {
       "What is the most common gas in the Earth's atmosphere?",
       "A) Oxygen B) Hydrogen",
       "C) Nitrogen D) Carbon dioxide"
   },
   {
       "What is the speed of light, approximately?",
       "A) 300,000 km/s B) 150,000 km/s",
       "C) 450,000 km/s D) 600,000 km/s"
   },
   {
       "What is the primary function of the ESC key?",
       "A) Save the document B) Open settings",
       "C) Exit the program D) Delete the file"
   },
   {
       "What is a byte?",
       "A) 8 bits B) 16 bits",
       "C) 32 bits D) 64 bits"
   },
   {
       "What metal has the chemical symbol Fe?",
       "A) Lead B) Iron",
       "C) Gold D) Silver"
   },
   {
       "What is the chemical formula for carbon dioxide?",
       "A) CO2 B) CO",
       "C) CH4 D) C2H6"
   },
   {
       "What protocol is used to send emails?",
       "A) HTTP B) SMTP",
       "C) FTP D) TCP"
   },
   {
       "Who invented the periodic table?",
       "A) Dmitri Mendeleev B) Albert Einstein",
       "C) Isaac Newton D) Michael Faraday"
   },
   {
       "What is the freezing point of water?",
       "A) 0 degrees Celsius B) 32 degrees Fahrenheit",
       "C) 100 degrees Celsius D) 212 degrees Fahrenheit"
   },
   {
       "What do you call the smallest particle of a chemical element?",
       "A) Molecule B) Atom",
       "C) Ion D) Electron"
   },
   {
       "What do you call a network of networks?",
       "A) The Internet B) Intranet",
       "C) LAN D) WAN"
   },
   {
       "How many bytes are in a kilobyte?",
       "A) 1000 B) 1024",
       "C) 2048 D) 500"
   },
   {
       "What is used to measure the acidity or alkalinity of a solution?",
       "A) Thermometer B) Barometer",
       "C) pH meter D) Hygrometer"
   },
   {
       "What element is necessary for combustion?",
       "A) Hydrogen B) Oxygen",
       "C) Nitrogen D) Carbon"
   },
   {
       "Who proposed the law of universal gravitation?",
       "A) Albert Einstein B) Isaac Newton",
       "C) Galileo Galilei D) Johannes Kepler"
   },
   {
       "What is a software program that supports basic functions like managing files?",
       "A) Spreadsheet B) Database system",
       "C) Operating system D) Word processor"
   },
   {
       "What is the boiling point of water?",
       "A) 90 degrees Celsius B) 212 degrees Fahrenheit",
       "C) 100 degrees Celsius D) 200 degrees Fahrenheit"
   },
   {
       "What is the symbol for potassium?",
       "A) Pt B) P",
       "C) Po D) K"
   },
   {
       "What is malware short for?",
       "A) Malfunctioning software B) Malformed software",
       "C) Managed software D) Malicious software"
   }
    };


    char easyQuestionsAnswers[45] = {
    'a', 'b', 'c', 'd', 'd', 'b', 'b', 'b', 'a', 'a', 'a', 'c', 'a', 'c', 'a',
    'a', 'a', 'b', 'a', 'a', 'a', 'b', 'a', 'c', 'a', 'a', 'c', 'a', 'c', 'a',
    'b', 'a', 'b', 'a', 'a', 'b', 'a', 'b', 'c', 'b', 'b', 'c', 'c', 'd', 'd'
    };


    string mediumQuestions[29][3] = {
    {
        "What is the molar mass of water?",
        "A) 22 g/mol B) 20 g/mol",
        "C) 18 g/mol D) 16 g/mol"
    },
    {
        "Calculate the circumference of a circle with a diameter of 10 cm.",
        "A) 25.6 cm B) 28.5 cm",
        "C) 31.4 cm D) 35.3 cm"
    },
    {
        "What protocol ensures secure data transfer over the internet?",
        "A) SMTP B) FTP",
        "C) HTTPS D) TCP"
    },
    {
        "Who discovered penicillin?",
        "A) Marie Curie B) Louis Pasteur",
        "C) Alexander Fleming D) Isaac Newton"
    },
    {
        "What is the function of a router in a network?",
        "A) Store data B) Connect multiple networks",
        "C) Provide user interface D) Manage print jobs"
    },
    {
        "Solve the equation 2x - 3 = 11.",
        "A) 8 B) 7",
        "C) 6 D) 5"
    },
    {
        "What does SQL stand for in databases?",
        "A) Standard Query Language B) Structured Query Language",
        "C) Simple Query Language D) Sequential Query Language"
    },
    {
        "Who discovered the electron?",
        "A) Niels Bohr B) J.J. Thomson ",
        "C) James Chadwick D) Ernest Rutherford"
    },
    {
        "What technology is used to make telephone calls over the Internet?",
        "A) Modem B) VoIP",
        "C) Router D) Switch"
    },
    {
        "Who formulated the theory of relativity?",
        "A) Albert Einstein B) Isaac Newton",
        "C) Niels Bohr D) Stephen Hawking"
    },
    {
        "What is the standard unit of electrical resistance?",
        "A) Ohm B) Ampere",
        "C) Coulomb D) Watt"
    },
    {
        "What is the common name for dihydrogen monoxide?",
        "A) Water B) Hydrogen peroxide",
        "C) Ammonia D) Methane"
    },
    {
        "What enzyme breaks down sugars in the human body?",
        "A) Amylase B) Lactase",
        "C) Sucrase D) Pepsin"
    },
    {
        "What is the primary language used for Android app development?",
        "A) Java B) C++",
        "C) Python D) Swift"
    },
    {
        "What is the main ingredient in glass?",
        "A) Sand B) Clay",
        "C) Lime D) Soda ash"
    },
    {
        "What is the common term for sodium chloride?",
        "A) Baking soda B) Table salt",
        "C) Sugar D) Bleach"
    },
    {
        "What is the sum of the interior angles of a pentagon?",
        "A) 540 degrees B) 360 degrees",
        "C) 720 degrees D) 180 degrees"
    },
    {
        "What is a supernova?",
        "A) A type of star B) An explosion of a star",
        "C) A black hole forming D) A galaxy"
    },
    {
        "What is the charge of a proton?",
        "A) Positive B) Negative",
        "C) Neutral D) Variable"
    },
    {
        "What is the most abundant metal in the Earth's crust?",
        "A) Iron B) Aluminum",
        "C) Silver D) Copper"
    },
    {
        "What is the symbol for gold?",
        "A) Au B) Ag",
        "C) Ga D) Ge"
    },
    {
        "What is the binary representation of the decimal number 10?",
        "A) 1010 B) 1001",
        "C) 1100 D) 1111"
    },
    {
        "What is the chemical formula for ozone?",
        "A) O3 B) O2",
        "C) O4 D) O5"
    },
    {
        "What is the main function of the CPU?",
        "A) Execute instructions B) Store data",
        "C) Manage power D) Connect peripherals"
    },
    {
        "What is the pH of stomach acid?",
        "A) 2 B) 7",
        "C) 10 D) 14"
    },
    {
        "What are valence electrons?",
        "A) Electrons in the outermost shell B) Electrons in the innermost shell",
        "C) Electrons that are shared D) Electrons that are lost"
    },
    {
        "What is the atomic number of gold?",
        "A) 79 B) 80",
        "C) 81 D) 78"
    },
    {
        "What is the boiling point of ethanol?",
        "A) 78 degrees Celsius B) 100 degrees Celsius",
        "C) 150 degrees Celsius D) 95 degrees Celsius"
    },
    {
        "What is the hexadecimal equivalent of the binary number 1111?",
        "A) F B) E",
        "C) E D) A"
    }
    };

    char mediumQuestionsAnswers[29] = { 'c', 'c', 'c', 'c', 'b', 'b', 'b', 'b', 'b', 'a', 'a', 'a', 'a', 'a', 'a', 'b', 'a', 'b', 'a', 'b', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a' };


    string hardQuestions[31][3] = {
    {
        "What is the Schrödinger equation used for?",
        "A) Solving classical physics problems B) Calculating chemical reaction rates",
        "C) Predicting quantum particle behaviors D) Predicting planetary motion"
    },
    {
        "Explain the concept of quantum entanglement.",
        "A) Particles remain interconnected B) Electrons bind together",
        "C) Atoms share protons D) Molecules split"
    },
    {
        "What is the significance of the Turing Machine?",
        "A) It can simulate any algorithm's logic B) It was the first computer",
        "C) It decrypts secure data D) It is a simple calculator"
    },
    {
        "Calculate the work done when a force of 10 N moves an object 3 meters.",
        "A) 30 Joules B) 20 Joules",
        "C) 10 Joules D) 40 Joules"
    },
    {
        "What is the role of the hypervisor in virtualization?",
        "A) To manage virtual machines B) To increase processing power",
        "A) To connect different OS D) To store data"
    },
    {
        "Explain the Pauli exclusion principle.",
        "A) Energy levels fuse under pressure B) Electrons repel each other",
        "C) Atoms attract each other D) No two electrons can have the same set of quantum numbers"
    },
    {
        "What is a semiconductor?",
        "A) An insulating material B) A pure metal",
        "C) A superconductor D) A material with conductivity between an insulator and most metals"
    },
    {
        "What is the Chandrasekhar limit?",
        "A) Brightness of a supernova B) Minimum size of a black hole",
        "C) Energy level for fusion in stars D) Maximum mass of a stable white dwarf star"
    },
    {
        "What is the primary function of the transport layer in the OSI model?",
        "A) To provide end-to-end communication B) To route packets",
        "C) To manage data flow D) To provide physical network connections"
    },
    {
        "Explain the process of nuclear fission.",
        "A) Nucleus splits into smaller parts releasing energy B) Nucleus combines with another nucleus",
        "C) Electrons are transferred between atoms D) Atoms gain neutrons"
    },
    {
        "What is the time complexity of binary search?",
        "A) O(n) B) O(log n)",
        "C) O(n^2) D) O(1)"
    },
    {
        "What is the significance of the Higgs boson?",
        "A) It explains the origin of mass B) It confirms the existence of electric charge",
        "C) It structures atomic nuclei D) It accelerates particles"
    },
    {
        "What is the function of the L1 cache in a computer?",
        "A) To store frequently accessed data close to the processor B) To increase storage capacity",
        "C) To manage power usage D) To enhance graphics"
    },
    {
        "What is the triple point of water?",
        "A) The temperature and pressure where water can exist in all three states B) The boiling point of water",
        "C) The freezing point of water D) The maximum density of water"
    },
    {
        "Explain the mechanism of the sodium-potassium pump.",
        "A) It exchanges sodium and potassium across the cell membrane B) It filters potassium out of the body",
        "C) It decreases sodium levels D) It generates ATP"
    },
    {
        "What is the principle behind fiber optic communication?",
        "A) Electrical impulses transmit data B) Light waves carry data",
        "C) Sound waves transfer information D) Radio waves send messages"
    },
    {
        "What is the main challenge in developing quantum computers?",
        "A) Data storage B) Error rates",
        "C) Power consumption D) Algorithm development"
    },
    {
        "What is the Planck constant?",
        "A) It relates the energy of a photon to its frequency B) It defines the gravitational force",
        "C) It measures the speed of light D) It determines electron orbitals"
    },
    {
        "Explain the concept of dark matter.",
        "A) It is matter that does not emit light B) It is a type of energy",
        "C) It is visible matter D) It is antimatter"
    },
    {
        "What is a Turing complete system?",
        "A) A system that can simulate any Turing machine B) A perfectly efficient machine",
        "C) A system without errors D) A self-learning AI"
    },
    {
        "What is the Fourier transform used for?",
        "A) To analyze the frequencies in a signal B) To calculate gravitational forces",
        "C) To measure speed D) To assess chemical compositions"
    },
    {
        "Explain the working principle of a laser.",
        "A) It emits light through optical amplification B) It reflects light off surfaces",
        "C) It focuses light through lenses D) It scatters light particles"
    },
    {
        "What are genetic algorithms?",
        "A) They are used for gene editing B) They simulate evolution to solve problems",
        "C) They map genetic diseases D) They clone biological traits"
    },
    {
        "What is the significance of Bell's theorem?",
        "A) It supports the theory of quantum mechanics B) It disproves general relativity",
        "C) It establishes classical physics D) It confirms the Big Bang theory"
    },
    {
        "What is the role of the kernel in an operating system?",
        "A) It manages system resources and allows hardware and software to communicate B) It is the user interface",
        "C) It stores data D) It enhances graphics"
    },
    {
        "What is the function of antioxidants in the human body?",
        "A) They prevent cellular damage by free radicals B) They promote cell division",
        "C) They decrease oxygen supply D) They increase carbon dioxide levels"
    },
    {
        "What is the Riemann hypothesis?",
        "A) It proposes a distribution pattern for prime numbers B) It is a theory of probability",
        "C) It defines algebraic structures D) It is a model for economic forecasting"
    },
    {
        "What is the structure of DNA?",
        "A) Double helix B) Single strand",
        "C) Triple helix D) Quadruple helix"
    },
    {
        "What are the main features of the IPv6 protocol?",
        "A) It provides more IP addresses B) It speeds up the internet",
        "C) It reduces data usage D) It encrypts data more securely"
    },
    {
        "What is a quantum computer?",
        "A) A theoretical type of computer B) A computer that uses quantum mechanics principles",
        "C) A computer that uses classical mechanics D) An advanced type of supercomputer"
    },
    {
        "What is the role of the mitochondria in cellular respiration?",
        "A) They synthesize proteins B) They store genetic information",
        "C) They produce energy in the form of ATP D) They detoxify chemicals"
    }
    };

    char hardQuestionsAnswers[31] = { 'c', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'a', 'a', 'b', 'a', 'a', 'a', 'a', 'b', 'b', 'a', 'a', 'a', 'a', 'a', 'b', 'a', 'a', 'a', 'a', 'a', 'a', 'b', 'c' };
    map<string, Account> accounts;
    loadAccounts(accounts);
    int score = 0;
    shuffle(easyQuestionsAnswers, easyQuestions, 44);
    shuffle(mediumQuestionsAnswers, mediumQuestions, 28);
    shuffle(hardQuestionsAnswers, hardQuestions, 30);

    questions(easyQuestions, easyQuestionsAnswers, score, 10, 4);
    questions(mediumQuestions, mediumQuestionsAnswers, score, 5, 5);
    questions(hardQuestions, hardQuestionsAnswers, score, 5, 7);

    cout << "Your Grade is: ";
    switch (score / 10) {
    case 5:cout << "D"; break;
    case 6:cout << "C"; break;
    case 7:cout << "B"; break;
    case 9:cout << "A"; break;
    case 10:cout << "A+"; break;
    default:cout << "F"; break;
    }
    cout << endl << "Your score is: " << score << "/100\n\n";
    cout << "Press Any button To Go Back\n";
    if (score > accounts[currentUser].highScore) {
        accounts[currentUser].highScore = score;
        saveAccounts(accounts);
    }
    char userInput;
    cin >> userInput;
    clear();
    loggedIn();

}
bool compare(const Account& a, const Account& b) {
    return a.highScore > b.highScore;
}

void sortAccounts(const map<string, Account>& accounts, vector<Account>& sortedAccounts) {
    for (const auto& pair : accounts) {
        sortedAccounts.push_back(pair.second);
    }
    sort(sortedAccounts.begin(), sortedAccounts.end(), compare);
}

void statistics() {
    map<string, Account> accounts;
    loadAccounts(accounts);
    vector<Account> sortedAccounts;
    sortAccounts(accounts, sortedAccounts);

    string address = "../TextFiles(Front-end)/statistics.txt";

    if (!sortedAccounts.empty()) {
        const Account& highestTestScore = sortedAccounts.front();
        const Account& lowestTestScore = sortedAccounts.back();
        string highestTestScoreName = highestTestScore.username, lowestTestScoreName = lowestTestScore.username;
        print(address);
        cout << setw(123) << endl << "Account With Highest Score: " << highestTestScoreName << " " << highestTestScore.highScore << endl;
        cout << setw(125) << "Account With The Lowest Score: " << lowestTestScoreName << " " << lowestTestScore.highScore << endl << endl;
        cout << setw(125) << "Press Any Button To Go Back\n";
        cout << setw(149) << "======================================================================\n\n";
        char userInput;
        cin >> userInput;
        clear();
        loggedIn();
    }
}
void loggedIn() {
    system("cls");
    string address = "../TextFiles(Front-end)/quizPort.txt";
    print(address);


    cout << setw(137) << endl << "1. Test Your Knowledge   2. Statistics   3. Exit\n";
    cout << setw(119) << endl << "Choose an option: ";
    char userInput;
    cin >> userInput;
    switch (userInput) {
    case '1': {
        clear();
        test();
        break;
    }
    case '2': {
        clear();
        statistics();
    } break;
    case '3': {
        exit(0);
    }
    default: loggedIn(); break;
    }
}