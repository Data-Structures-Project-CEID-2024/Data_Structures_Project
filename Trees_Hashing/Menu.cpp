// // #include "Menu.h"

// Menu::Menu()
// {

//     readInterfaces();
//     int selection;

//     do{
//         system("clear"); // Change to "cls" for Windows machines.
//         for (const auto& stored_line : mainMenu) {
//             cout << stored_line << endl;
//         }
//         cout << "-> ";

//         cin >> selection;
//         if (selection < 0 || selection > 3 || cin.fail()) {
//             cin.clear();
//             cin.ignore(numeric_limits<streamsize>::max(), '\n');
//             cout << "Invalid input.\nPress ENTER to continue." << endl;
//             cin.get(); // Wait for enter
//             selection = -1; // Setting selection to -1 to restart loop
//         }
//         switch (selection){

//             case 1:
//                 taskA(reg, root);
//                 break;

//             case 2:

//                 taskB();
//                 break;

//             case 3:

//                 taskC();
//                 break;

//         }

//     }while(selection != 0);
//     system("clear"); // Change to "cls" for Windows machines.
//     exit(0);
// }

// void Menu::readInterfaces(){ // Reading formats from respective txts -> PATH: formats/example.txt

//     string line;

//     // Main menu
//     ifstream format0("formats/mainMenu.txt");
//     if (!format0.is_open()) {
//         cerr << "Error: Could not open the Main menu interface file " << endl;
//         exit(0);
//     }
//     while (getline(format0, line)) {
//         mainMenu.push_back(line);
//     }
//     format0.close();

//     // Menu for task A
//     ifstream format1("formats/aMenu.txt");
//     if (!format1.is_open()) {
//         cerr << "Error: Could not open the A's Menu interface file " << endl;
//         exit(0);
//     }
//     while (getline(format1, line)) {
//         aMenu.push_back(line);
//     }
//     format1.close();

//     // Menu for task B
//     ifstream format2("formats/bMenu.txt");
//     if (!format2.is_open()) {
//         cerr << "Error: Could not open the Main menu interface file " << endl;
//         exit(0);
//     }
//     while (getline(format2, line)) {
//         bMenu.push_back(line);
//     }
//     format2.close();

//     // Menu for task C
//     ifstream format3("formats/cMenu.txt");
//     if (!format3.is_open()) {
//         cerr << "Error: Could not open the Main menu interface file " << endl;
//         exit(0);
//     }
//     while (getline(format3, line)) {
//         cMenu.push_back(line);
//     }
//     format3.close();



// }

// void Menu::taskA(REG reg, Node* root)
// {
    
//     string search_string;
//     int search_int;
//     int select;
//     do{

//         system("clear"); // Change to "cls" for Windows machines.
//         for (const auto& stored_line : aMenu) 
//             cout << stored_line << endl;
        
//         cout << "-> ";
//         cin >> select;
//         if(select > 5 || select < 0 || cin.fail()) {
//             cin.clear();
//             cin.ignore(numeric_limits<streamsize>::max(), '\n');
//             cout << "Invalid input.\nPress ENTER to continue." << endl;
//             cin.get(); // Wait for enter
//             select = -1; // Setting selection to -1 to restart loop
//         }
//         switch (select) 
//         {

//             case 0:
//                 system("clear"); // Change to "cls" for Windows machines.
//                 exit(0);

//             case 1:
//                 reg.InOrder(root);
//                 reg.printLevelOrder(root);
//                 cout << endl;

//                 break;

//             case 2:
//                 NumericalAVL prd;
//                 prd.printLevelOrder(root->node_data_births);
//                 Node* node_search = NULL;
                
//                 search_string = "A";
//                 search_int = 2000;

//                 node_search = reg.search(root, search_string, search_int);

//                 if (node_search == NULL)
//                 {
//                     cout << "Node not found\n";
//                 }
//                 else
//                 {
//                     cout << "Node found\n";
//                     cout << "Region: " << node_search->key << endl;
//                     cout << "Period: " << node_search->intKey << endl;
//                     cout << "Count: " << node_search->data_count << endl;
//                 }
//                 cout << endl;

//                 break;

//             // case 3:

//             //     break;

//             // case 4:

//             //     break;


//         }

//     }while(select != 5);
// }

// void Menu::taskB(){

//     int select;
//     do{

//         system("clear"); // Change to "cls" for Windows machines.
//         for (const auto& stored_line : bMenu) {
//             cout << stored_line << endl;
//         }
//         cout << "-> ";
//         cin >> select;
//         if(select > 5 || select < 0 || cin.fail()) {
//             cin.clear();
//             cin.ignore(numeric_limits<streamsize>::max(), '\n');
//             cout << "Invalid input.\nPress ENTER to continue." << endl;
//             cin.get(); // Wait for enter
//             select = -1; // Setting selection to -1 to restart loop
//         }
//         switch (select) {

//             case 0:
//                 system("clear"); // Change to "cls" for Windows machines.
//                 exit(0);

//             case 1:

//                 break;

//             case 2:

//                 break;

//             case 3:

//                 break;

//             case 4:

//                 break;


//         }

//     }while(select != 5);
// }

// void Menu::taskC(){

//     int select;
//     do{

//         system("clear"); // Change to "cls" for Windows machines.
//         for (const auto& stored_line : cMenu) {
//             cout << stored_line << endl;
//         }
//         cout << "-> ";
//         cin >> select;
//         if(select > 5 || select < 0 || cin.fail()) {
//             cin.clear();
//             cin.ignore(numeric_limits<streamsize>::max(), '\n');
//             cout << "Invalid input.\nPress ENTER to continue." << endl;
//             cin.get(); // Wait for enter
//             select = -1; // Setting selection to -1 to restart loop
//         }
//         switch (select) {

//             case 0:
//                 system("clear"); // Change to "cls" for Windows machines.
//                 exit(0);

//             case 1:

//                 break;

//             case 2:

//                 break;

//             case 3:

//                 break;

//             case 4:

//                 break;


//         }

//     }while(select != 5);
// }
