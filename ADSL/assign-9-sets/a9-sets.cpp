#include <iostream>

using namespace std;

class Node
{
    char data;
    Node *next;

public:
    Node(char d = 0)
    {
        data = d;
        next = NULL;
    }
    Node operator++()
    {
        return (this->next == NULL) ? Node(0) : *(this->next);
    }
    char operator*()
    {
        return data;
    }

    friend class Set;
};

class Set
{
    Node *head;
    int count;

public:
    Set()
    {
        head = NULL;
        count = 0;
    }
    bool contains(char val);
    void insert(char val);
    void remove(char val);
    void clear();
    int size();
    Set Intersect(Set B);
    Set Union(Set B);
    Set Difference(Set B);
    Set Subset(int start, int length);
    Node iterator()
    {
        if (head)
            return *head;
        else
            return Node(0);
    }
};

bool Set::contains(char val)
{
    Node *p = head;
    while (p)
    {
        if (p->data == val)
            return true;
        p = p->next;
    }
    return false;
}

void Set::insert(char val)
{
    Node *p = head;
    Node *t = p;
    Node *n = new Node(val);
    if (!head)
    {
        head = n;
        count++;
    }
    else
    {
        while (val > p->data)
        {
            t = p;
            p = p->next;
            if (!p)
                break;
        }

        if (p == head)
        {
            n->next = head;
            head = n;
        }
        else
        {
            t->next = n;
            n->next = p;
        }
        count++;
    }
}

void Set::remove(char val)
{
    Node *p = head;
    Node *t = p;
    while (p != NULL)
    {
        if (p->data == val)
            break;
        t = p;
        p = p->next;
    }
    if (p)
    {
        if (p == head)
            head = head->next;
        else
        {
            t->next = p->next;
        }
        cout << p->data << " removed\n";
        delete p;
        count--;
    }
    else
    {
        cout << val << " not found\n";
    }
}

void Set::clear()
{
    Node *p = head;
    Node *t = p;
    while (p)
    {
        p = p->next;
        delete t;
        t = p;
    }
}

int Set::size()
{
    return count;
}

Set Set::Union(Set B)
{
    Set C;
    Node *p = head;
    while (p)
    {
        C.insert(p->data);
        p = p->next;
    }
    p = B.head;
    while (p)
    {
        if (!C.contains(p->data))
            C.insert(p->data);
        p = p->next;
    }
    return C;
}

Set Set::Intersect(Set B)
{
    Set C;
    Node *p = head;
    while (p)
    {
        if (B.contains(p->data))
            C.insert(p->data);
        p = p->next;
    }
    return C;
}

Set Set::Difference(Set B)
{
    Set C;
    Node *p = head;
    while (p)
    {
        if (!B.contains(p->data))
            C.insert(p->data);
        p = p->next;
    }
    return C;
}

Set Set::Subset(int start, int length)
{
    Set A;
    Node *p = head;
    for (int i = 0; i < start && i < count; i++)
        p = p->next;
    for (int i = 0; i < length && i < count; i++)
    {
        A.insert(p->data);
        p = p->next;
    }
    return A;
}

void display(Set A)
{
    Node it = A.iterator();
    int i = 0;
    int n = A.size();
    while (i < n)
    {
        cout << *it << " ";
        it = ++it;
        i++;
    }
    cout << endl;
}

int main()
{
    Set A, B, C, D;
    int op, start, length;
    char val;
    do
    {
        cout << "1. Insert\n";
        cout << "2. Remove\n";
        cout << "3. Check if element is available\n";
        cout << "4. Display\n";
        cout << "0. Exit\n";
        cout << "  Option : ";
        cin >> op;
        cout << endl;
        switch (op)
        {
        case 1:
            cout << "    1. Into Set A\n";
            cout << "    2. Into Set B\n";
            cout << "      Option : ";
            cin >> op;
            switch (op)
            {
            case 1:
                cout << "Value : ";
                cin >> val;
                if (!A.contains(val))
                    A.insert(val);
                break;
            case 2:
                cout << "Value : ";
                cin >> val;
                if (!B.contains(val))
                    B.insert(val);
            }
            op = 1;
            break;

        case 2:
            cout << "    1. From Set A\n";
            cout << "    2. From Set B\n";
            cout << "      Option : ";
            cin >> op;
            switch (op)
            {
            case 1:
                cout << "Value : ";
                cin >> val;
                A.remove(val);
                break;
            case 2:
                cout << "Value : ";
                cin >> val;
                B.remove(val);
            }
            op = 1;
            break;

        case 3:
            cout << "    1. In Set A\n";
            cout << "    2. In Set B\n";
            cout << "      Option : ";
            cin >> op;
            switch (op)
            {
            case 1:
                cout << "Value : ";
                cin >> val;
                if (A.contains(val))
                    cout << val << " is present in Set A\n";
                else
                    cout << val << " is not present in Set A\n";
                break;
            case 2:
                cout << "Value : ";
                cin >> val;
                if (B.contains(val))
                    cout << val << " is present in Set B\n";
                else
                    cout << val << " is not present in Set B\n";
                break;
            }
            op = 1;
            break;

        case 4:
            cout << "    1. Set A\n";
            cout << "    2. Set B\n";
            cout << "    3. Intersection Set\n";
            cout << "    4. Union Set\n";
            cout << "    5. Difference Set\n";
            cout << "    6. Subset\n";
            cout << "      Option : ";
            cin >> op;
            cout << endl;
            switch (op)
            {
            case 1:
                display(A);
                break;
            case 2:
                display(B);
                break;
            case 3:
                C = A.Intersect(B);
                display(C);
                break;
            case 4:
                D = A.Union(B);
                display(D);
                break;
            case 5:
                D = A.Difference(B);
                display(D);
                break;
            case 6:
                cout << "      1. Set A\n";
                cout << "      2. Set B\n";
                cout << "        Option : ";
                cin >> op;
                cout << endl;
                switch (op)
                {
                case 1:
                    cout << "Starting pos : ";
                    cin >> start;
                    cout << "Length : ";
                    cin >> length;
                    cout << endl;
                    D = A.Subset(start, length);
                    display(D);
                    break;
                case 2:
                    cout << "Starting pos : ";
                    cin >> start;
                    cout << "Length : ";
                    cin >> length;
                    cout << endl;
                    D = B.Subset(start, length);
                    display(D);
                }
                break;
            }
            op = 1;
            break;
        }
        cout << endl;
    } while (op);

    return 0;
}