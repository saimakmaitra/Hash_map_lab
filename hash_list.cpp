#include "hash_list.h"

hash_list::hash_list() : head(nullptr), size(0), iter_ptr(nullptr) {}

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/

void hash_list::insert(int key, float value)
{
    node* curr = head;
    
    while (curr) 
    {
        if (curr->key == key) 
        {
            curr->value = value;
            return;
        }
        curr = curr->next;
    }

    node* newN = new node;
    newN->key = key;
    newN->value = value;
    newN->next = head;
    head = newN;
    size++;
}

std::optional<float> hash_list::get_value(int key) const 
{ 
    node* curr = head;
    
    while (curr) 
    {
        if (curr->key == key) 
        {
            return curr->value;
        }
        curr = curr->next;
    }

    return std::nullopt;
}

bool hash_list::remove(int key) 
{
    if (!head) 
    {
        return false; 
    }

    if (head->key == key) 
    {
        node* temp = head;
        head = head->next;
        delete temp;
        size--;
        return true;
    }
    
    node* curr = head;
    while (curr->next) {
        if (curr->next->key == key) 
        {
            node* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
            size--;
            return true;
        }
        curr = curr->next;
    }

    return false;
}

size_t hash_list::get_size() const 
{ 
    return size;
}

hash_list::~hash_list()
{
    node* curr = head;
    while (curr) 
    {
        node* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

/**-----------------------------------------------------------------------------------
 * END Part 1
 *------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------
 * START Part 2
 *------------------------------------------------------------------------------------*/

hash_list::hash_list(const hash_list &other) : head(nullptr), size(0), iter_ptr(nullptr) 
{
    node *curr = other.head;
    node **newN = &head;

    while (curr) 
    {
        *newN = new node{curr->key, curr->value, nullptr};
        newN = &((*newN)->next);
        curr = curr->next;
        size++;
    }
}


hash_list &hash_list::operator=(const hash_list &other) 
{ 
    if (this == &other) return *this;

    node* curr = head;
    while (curr) 
    {
        node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    head = nullptr;
    size = 0;
    iter_ptr = nullptr;
    
    node* curr_other = other.head;
    node** last_ptr = &head;

    while (curr_other) 
    {
        *last_ptr = new node{curr_other->key, curr_other->value, nullptr};
        last_ptr = &((*last_ptr)->next);
        curr_other = curr_other->next;
        size++;
    }

    return *this;
}

void hash_list::reset_iter() 
{
    iter_ptr = head;
}


void hash_list::increment_iter() 
{
    if (iter_ptr) {
        iter_ptr = iter_ptr->next;
    }
}


std::optional<std::pair<const int *, float *>> hash_list::get_iter_value() 
{ 
    if (iter_ptr) 
    {
        return std::make_optional(std::pair<const int *, float *>(&iter_ptr->key, &iter_ptr->value));
    }
    return std::nullopt; 
}


bool hash_list::iter_at_end() 
{ 
    return iter_ptr == nullptr;
}
/**-----------------------------------------------------------------------------------
 * END Part 2
 *------------------------------------------------------------------------------------*/
