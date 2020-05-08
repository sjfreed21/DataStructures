/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork() {
    head = NULL;
}


void CountryNetwork::insertCountry(Country* previous, string countryName)
{
    Country *add = new Country;
    add->name = countryName;
    if(previous) {
        add->next = previous->next;
        previous->next = add;
        cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;
        return;
    }
    if(!previous){
        add->next = head;
        head = add;
        cout << "adding: " << countryName << " (HEAD)" << endl;
        return;
    }
}


void CountryNetwork::loadDefaultSetup() 
{
    Country * temp = new Country;
    insertCountry(NULL, "United States");
    temp = searchNetwork("United States");
    insertCountry(temp, "Canada");
    temp = searchNetwork("Canada");
    insertCountry(temp, "Brazil");
    temp = searchNetwork("Brazil");
    insertCountry(temp, "India");
    temp = searchNetwork("India");
    insertCountry(temp, "China");
    temp = searchNetwork("China");
    insertCountry(temp, "Australia");
}


Country* CountryNetwork::searchNetwork(string countryName)
{
    Country *scan = head;
    while(scan != NULL){
        if(scan->name == countryName) return scan;
        scan = scan->next;
    }
    return NULL;
}


void CountryNetwork::transmitMsg(string receiver, string message)
{
    if(head == NULL) {
        cout << "Empty List" << endl;
        return;
    }
    Country *receive = new Country;
    receive = searchNetwork(receiver);
    if(receive == NULL) {
        cout << "Country not found" << endl;
        return;
    }
    Country* node = head;
    while(node != receive){
        node->message = message;
        node->numberMessages++;
        cout << node->name << " [# messages received: " << node->numberMessages << "] received: " << node->message << endl;
        node = node->next;
    }
    if(node == receive){
        receive->message = message;
        receive->numberMessages++;
        cout << receive->name << " [# messages received: " << receive->numberMessages << "] received: " << receive->message << endl;
        return;
    }
}


void CountryNetwork::printPath()
{
    cout << "== CURRENT PATH ==" << endl;
    if(head == NULL) {
        cout << "nothing in path" << endl << "===" << endl;
        return;
    }
    Country *scan = head;
    while(scan != NULL) {
        cout << scan->name << " -> ";
        scan = scan->next;
    }
    cout << "NULL" << endl << "===" << endl;
}