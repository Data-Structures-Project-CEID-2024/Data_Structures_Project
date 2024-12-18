#ifndef DATA_STRUCTURES_PROJECT_MENU_H
#define DATA_STRUCTURES_PROJECT_MENU_H

#include "Input.h"
#include "Struct.h"
#include "Trees.h"
#include "Hashing.h"

#include <vector>
#include <iostream>
#include <limits>

using namespace std;

class Menu {
public:

    Node* rootA = NULL;
    Node* rootB = NULL;
    vector<list<Node*>> buckets; 
    Hashing hash;

    Input input;

    vector<string> mainMenu;
    vector<string> aMenu;
    vector<string> bMenu;
    vector<string> cMenu;

    Menu(Input entry)
    {
        this->input = entry;

        readInterfaces();
        int selection;
        do{
            system("clear"); // Change to "cls" for Windows machines.
            for (const auto& stored_line : mainMenu) {
                cout << stored_line << endl;
            }
            cout << "-> ";

            cin >> selection;
            if (selection < 0 || selection > 3 || cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input.\nPress ENTER to continue." << endl;
                cin.get(); // Wait for enter
                selection = -1; // Setting selection to -1 to restart loop
            }
            switch (selection){

                case 1:
                                        
                    taskA();
                    break;

                case 2:

                    taskB();
                    break;

                case 3:

                    taskC();
                    break;

            }

        }while(selection != 0);
        system("clear"); // Change to "cls" for Windows machines.
        exit(0);
    }

    void readInterfaces(){ // Reading formats from respective txts -> PATH: formats/example.txt

        string line;

        // Main menu
        ifstream format0("formats/mainMenu.txt");
        if (!format0.is_open()) {
            cerr << "Error: Could not open the Main menu interface file " << endl;
            exit(0);
        }
        while (getline(format0, line)) {
            mainMenu.push_back(line);
        }
        format0.close();

        // Menu for task A
        ifstream format1("formats/aMenu.txt");
        if (!format1.is_open()) {
            cerr << "Error: Could not open the A's Menu interface file " << endl;
            exit(0);
        }
        while (getline(format1, line)) {
            aMenu.push_back(line);
        }
        format1.close();

        // Menu for task B
        ifstream format2("formats/bMenu.txt");
        if (!format2.is_open()) {
            cerr << "Error: Could not open the Main menu interface file " << endl;
            exit(0);
        }
        while (getline(format2, line)) {
            bMenu.push_back(line);
        }
        format2.close();

        // Menu for task C
        ifstream format3("formats/cMenu.txt");
        if (!format3.is_open()) {
            cerr << "Error: Could not open the Main menu interface file " << endl;
            exit(0);
        }
        while (getline(format3, line)) {
            cMenu.push_back(line);
        }
        format3.close();



    }
    
    void taskA()
    {
        Node* node_search = NULL;
        REG reg;
        string search_string;
        int search_int;
        int select;
        int edit_count;
        do{

            system("clear"); // Change to "cls" for Windows machines.
            for (const auto& stored_line : aMenu) 
                cout << stored_line << endl;
            
            cout << "-> ";
            cin >> select;
            if(select > 6 || select < 0 || cin.fail()) 
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input.\nPress ENTER to continue." << endl;
                cin.get(); // Wait for enter
                select = -1; // Setting selection to -1 to restart loop
            }
            switch (select) 
            {

                case 0:
                    system("clear"); // Change to "cls" for Windows machines.
                    exit(0);

                case 1:
                    {
                        if (rootA != NULL)
                        {
                            reg.InOrder(rootA);
                            reg.printLevelOrder(rootA);
                            cout << endl;
                        }
                        else
                        {
                            cout << "Tree not initialized\n";
                            cout << "Select option 5 to Initialize AVL tree first\n";
                        }
                        
                        cout << "\nPress ENTER to continue." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        cin.get();
                        break;
                    }

                case 2:
                    {
                        if (rootA != NULL)
                        {
                            NumericalAVL prd;
                            prd.printLevelOrder(rootA->node_data_births);
                            
                            cout << "Enter the region to search: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            getline(cin, search_string);
                            cout << "Enter the period: ";
                            cin >> search_int;

                            node_search = reg.search(rootA, search_string, search_int);

                            if (node_search == NULL)
                            {
                                cout << "Node not found\n";
                            }
                            else
                            {
                                cout << "Node found\n";
                                cout << "Region: " << node_search->key << endl;
                                cout << "Period: " << node_search->intKey << endl;
                                cout << "Count: " << node_search->data_count << endl;
                            }
                            cout << endl;
                        }
                        else
                        {
                            cout << "Tree not initialized\n";
                            cout << "Select option 5 to Initialize AVL tree first\n";
                        }

                           cout << "\nPress ENTER to continue." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        cin.get();
                        break;
                    }
                    

                case 3:
                    {

                        if (rootA != NULL)
                        {
                            cout<<"Enter the region to edit: ";
                            
                            cout << "Enter the region to search: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            getline(cin, search_string);
                            cout << "Enter the period: ";
                            cin >> search_int;
                            cout << "Enter the new count: ";
                            cin >> edit_count;

                            reg.editSelect(rootA, search_string, search_int, edit_count);
                            node_search = reg.search(rootA, search_string, search_int);

                            if (node_search == NULL)
                            {
                                cout << "Node not found\n";
                            }
                            else
                            {
                                cout << "Node found\n";
                                cout << "Region: " << node_search->key << endl;
                                cout << "Period: " << node_search->intKey << endl;
                                cout << "Count: " << node_search->data_count << endl;
                            }
                        }
                        else
                        {
                            cout << "Tree not initialized\n";
                            cout << "Select option 5 to Initialize AVL tree first\n";
                        }

                        cout << "\nPress ENTER to continue." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        cin.get();
                        break;
                    }
                    
                case 4:
                    {
                        if(rootA != NULL)
                        {
                            cout << "Enter the region to search: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            getline(cin, search_string);
                           
                            reg.deleteNode(rootA, search_string);
                            
                            node_search = reg.search(rootA, search_string, search_int = 0);

                            if (node_search == NULL)
                                cout << "Node was successfully deleted\n";
                            else
                                cout << "Node was not deleted\n";
                        }
                        else
                        {
                            cout << "Tree not initialized\n";
                            cout << "Select option 5 to Initialize AVL tree first\n";
                        }

                        cout << "\nPress ENTER to continue." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        cin.get();
                        break;
                    }
                case 5:
                    {
                        int size = input.input.size();
                        rootA = reg.insert(NULL, input.input[0]);
                        
                        for (int i = 1; i < size; i++)
                            rootA = reg.insert(rootA , input.input[i]);
                        
                        cout << "\nAVL has been initialized in Task A: Format";

                        cout << "\nPress ENTER to continue.";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        cin.get();
                        break;
                    }

            }

        }while(select != 6);
    }

    void taskB(){

        NumericalAVL* counts = new NumericalAVL();

        int select;
        do{

            system("clear"); // Change to "cls" for Windows machines.
            for (const auto& stored_line : bMenu) {
                cout << stored_line << endl;
            }
            cout << "-> ";
            cin >> select;
            if(select > 6 || select < 0 || cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input.\nPress ENTER to continue." << endl;
                cin.get(); // Wait for enter
                select = -1; // Setting selection to -1 to restart loop
            }
            switch (select) {

                case 0:
                {
                    system("clear"); // Change to "cls" for Windows machines.
                    exit(0);
                }
                    
                case 1:
                {
                    if (rootB != NULL)
                    {
                        Node* cptr = counts->findMin(rootB);
                        cout << "\nMin key is: " << cptr->intKey;
                        for (population it : cptr->dataVector) {
                            std::cout << it.region << " ";
                        }
                        std::cout << std::endl;
                    }
                    else
                    {
                        cout << "Tree not initialized\n";
                        cout << "Select option 5 to Initialize AVL tree first\n";
                    }
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "Press ENTER to continue." << endl;
                    cin.get(); // Wait for enter       
                    break;
                }

                case 2:
                {
                    if (rootB != NULL)
                    {
                        Node* mptr = counts->findMax(rootB);
                        cout << "\nMax key is " << mptr->intKey;
                        for (population it : mptr->dataVector) {
                            std::cout << it.region << " ";
                        }
                        std::cout << std::endl; 
                    }
                    else
                    {
                        cout << "Tree not initialized\n";
                        cout << "Select option 5 to Initialize AVL tree first\n";
                    }
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "Press ENTER to continue." << endl;
                    cin.get(); // Wait for enter       
                    break;
                               
                }

                case 3:
                {
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "Invalid input.\nPress ENTER to continue." << endl;
                    cin.get(); // Wait for enter
                    break;
                }
                    

                case 4:
                {
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "Invalid input.\nPress ENTER to continue." << endl;
                    cin.get(); // Wait for enter
                    break;
                }
                    

                case 5:
                {
                    rootB = counts->insert(NULL, input.input[0].count , input.input[0]);
                    for (int i = 1; i < 20 /* temporary */; i++)
                    {
                        if(input.input[i].alive == 1){
                            rootB = counts->insert(rootB, input.input[i].count ,input.input[i]);
                        }
                    }
                    cout << "\nAVL has been initialized in Task B: Format";

                    cout << "\nPress ENTER to continue.";
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cin.get(); // Wait for enter
                    break;
                }
                    

            }

        }while(select != 6);
    }

   void taskC(){
       string Region;
       int Period;
       int newCount;
       int m = 11;
       Hashing hash = Hashing(m);

        int select;
        do{

            system("clear"); // Change to "cls" for Windows machines.
            for (const auto& stored_line : cMenu) {
                cout << stored_line << endl;
            }
            cout << "-> ";
            cin >> select;
            if(select > 6 || select < 0 || cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input.\nPress ENTER to continue." << endl;
                cin.get(); // Wait for entωer
                select = -1; // Setting selection to -1 to restart loop
            }
            switch (select) {

                case 0:
                    system("clear"); // Change to "cls" for Windows machines.
                    exit(0);

                case 1: 
                        cout<<"Enter the region to search: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, Region);
                        cout << "Enter the period: ";
                        cin >> Period;

                    if( buckets.size() != 0 ){
                      hash.searchElement(Region, Period, buckets);
                    }
                    else
                        {
                            cout << "Hash map not initialized\n";
                            cout << "Select option 5 to Initialize Hash map first\n";
                        }


                        cout << "Press ENTER to continue." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        cin.get();
                     break;

                case 2:
                    cout<<"Enter the region to edit: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, Region);
                    cout << "Enter the period: ";
                    cin >> Period;
                    cout << "Enter the new count: ";
                    cin >> newCount;

                    
                    if( buckets.size() != 0 ){
                       hash.modifyElement(Region, Period, buckets, newCount);
                    }
                    else
                        {
                            cout << "Hash map not initialized\n";
                            cout << "Select option 5 to Initialize Hash map first\n";
                        }


                        cout << "Press ENTER to continue." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        cin.get();
                    break;

                case 3:
                    cout<<"Enter the region to delete: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, Region);
                   
                    if( buckets.size() != 0 ){
                        hash.deleteElement(Region, buckets);
                    }
                    else
                        {
                            cout << "Hash map not initialized\n";
                            cout << "Select option 5 to Initialize Hash map first\n";
                        }


                        cout << "Press ENTER to continue." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        cin.get();
                   
                    break;

                case 4:
                {
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "Invalid input.\nPress ENTER to continue." << endl;
                    cin.get(); // Wait for enter
                    break;
                }

                case 5:
                    
                    list<Node*> chain;
                    for(int i=0;i<hash.m; i++){
                    buckets.push_back(chain);
                    }

                    for (auto& population : input.input)
                    {
                        //cout << "Region: " << population.region <<  "\t\t\tPeriod:  "  << population.period;
                        hash.insertElement(population, buckets);
    
                    }
                    cout << "** Hash map has been initialized in Task's C: Format **";
                    cout << "\nPress ENTER to continue.";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cin.get();

                break;


            }

        }while(select != 6);
    

    }

};


#endif //DATA_STRUCTURES_PROJECT_MENU_H
