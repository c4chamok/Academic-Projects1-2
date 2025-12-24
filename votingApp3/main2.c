#include "dArray.h"

typedef struct {
    char name[50];
    int age;
} Person;

int main()
{
    DynamicArray personsList;
    da_init(&personsList, sizeof(Person));
    Person p1 = {"John", 28};
    da_push(&personsList, &p1);
    da_push(&personsList, &(Person){"Alice", 30});
    da_push(&personsList, &(Person){"Bob", 25});
    for (size_t i = 0; i < personsList.size; i++) {
        Person *p = (Person *) da_get(&personsList, i);
        printf("Name: %s, Age: %d\n", p->name, p->age);
    }
    return 0;
}
