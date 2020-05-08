/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represent communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
/* finished. do not touch. */
    head = NULL;
}


/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty()
{
/* finished. do not touch. */
    return (head == NULL);
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName) {
    
    // if we are passed an empty list, just create a new head node, and return
    if (head == NULL)
    {
        cout << "adding: " << countryName << " (HEAD)" << endl;
        head = new Country;
        head->name = countryName;
        head->numberMessages = 0;
        head->next = NULL;
    }
    // if it's not empty, we need to search for previous and append our node there.
    else if(previous == NULL )
    {
        //case where it's a new head Country
        cout << "adding: " << countryName << " (HEAD)" << endl;
        Country *c = new Country;
        c->name = countryName;
        c->numberMessages = 0;
        c->next = head;
        head = c;
    }else{
        cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;
        Country *newCountry = new Country;
        newCountry->name = countryName;
        newCountry->numberMessages = 0;
        newCountry->next = previous->next;
        previous->next = newCountry;
    }
}


/*
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
void CountryNetwork::deleteCountry(string countryName) {
        Country * del;
    del = searchNetwork(countryName);
    if(!del) {
        cout << "Country does not exist." << endl;
        return;
    }
    Country * prev = head;
    if(del == head) {
        prev = head->next;
        delete head;
        head = prev;
        return;
    }
    while(prev->next != del) prev = prev->next;
    prev->next = del->next;
    delete del;
    return;
}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup()
{
    int num_countries = 6;
    string countries[] = {"United States", "Canada", "Brazil", "India", "China", "Australia"};
    // deleteEntireNetwork();
    Country* prev = NULL;
    for(int i = 0; i < num_countries; i++)
    {
        insertCountry(prev, countries[i]);
        prev = searchNetwork(countries[i]);
    }
}


/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 * @see insertCountry, deletecountry
 */
Country* CountryNetwork::searchNetwork(string countryName)
{
// Search until the head is NULL, or we find the country
    Country* ptr = head;
    while (ptr != NULL && ptr->name != countryName)
    {
        ptr = ptr->next;
    }
    // Return the node, or NULL
    return ptr;
}

/*
* Purpose: Creates a loop from last node to the country specified.
* @param countryName name of the country to loop back
* returns pointer to last node before loop creation (to break the loop)
*/
Country* CountryNetwork::createLoop(string countryName)
{
    Country * tail = head, * loop;
    while(tail->next != NULL) tail = tail->next;
    loop = searchNetwork(countryName);
    if(!loop) return tail;
    tail->next = loop;
    return tail;
}

/*
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
void CountryNetwork::deleteEntireNetwork()
{
    Country * del;
    while(head != NULL){
        del = head->next;
        cout << "deleting: " << head->name << endl;
        delete head;
        head = del;
    }
    cout << "Deleted network" << endl;
}

/*
*Purpose: to detect loop in the linkedlist
* @param
* returns true if loop is detected. Otherwise return false.
*/
bool CountryNetwork::detectLoop() {
    if (head == NULL) return false;
    Country * fast = head->next, * slow = head;
    while(fast && slow && fast->next) {
        if(fast == slow) return true;
        fast = fast->next->next;
        slow = slow->next;
    }
    return false;
}

/*
* Purpose: Take the chunk of nodes from start index to end index
*          Move that chunk at the end of the List
*@param: start index
*@param: end index
* return none
*/
void CountryNetwork:: readjustNetwork(int start_index, int end_index)
{
    if(head == NULL) {
        cout << "Linked List is Empty" << endl;
        return;
    }
    if(startIndex > endIndex) {
        cout << "Invalid indices" << endl;
        return;
    }
    if(startIndex < 0) {
        cout << "Invalid start index" << endl;
        return;
    }
    if(endIndex < 0){
        cout << "Invalid end index" << endl;
        return;
    }
    Country * start = head, * end = head, * tail = head, * prev = head;
    if(startIndex == 0) {
        int temp = endIndex;
        while(temp--) head = head->next;
        head = head->next;
    }
    while(startIndex-- && start) {
        prev = start;
        start = start->next;
    }
    while(endIndex-- && end) {
        end = end->next;
    }
    while(tail->next) tail = tail->next;
    if(!start){
        cout << "Invalid start index" << endl;
        return;
    }
    if(!end){
        cout << "Invalid end index" << endl;
        return;
    }
    Country * next = end->next;
    if(prev != start) prev->next = next;
    tail->next = start;
    end->next = NULL;
    return;
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath() {
    cout << "== CURRENT PATH ==" << endl;
    // If the head is NULL
    Country* ptr = head;
    if (ptr == NULL)
        cout << "nothing in path" << endl;

    // Otherwise print each node, and then a NULL
    else
    {
        while (ptr->next != NULL)
        {
            cout << ptr->name << " -> ";
            ptr = ptr->next;
        }
        cout << ptr->name << " -> ";
        cout << "NULL" << endl;
    }
    cout << "===" << endl;
}
