#include <iostream>
#include <forward_list>

enum TYPE {
    DOG,
    CAT
};

class Animal {

public:
    TYPE typeOf() {return type;}
    virtual void print() = 0;
protected:
    TYPE type;
    int num;
};

class Dog : public Animal {
public:
    Dog(int n) {
        type = DOG;
        num = n;
        print();
    }
    void print() { std::cout << "DOG "<< num << "\n";}
};

class Cat : public Animal {
public:
    Cat(int n) {
        type = CAT;
        num = n;
        print();
    }
    void print() { std::cout << "CAT " << num << "\n";}
};

class Shelf {
public:
    Shelf(std::shared_ptr<Animal> a) : animal(a) {}
    std::shared_ptr<Animal> animal;
    std::shared_ptr<Shelf> next;
};

class Shelter {
public:
    void enqueue(std::shared_ptr<Animal> animal) {
        std::shared_ptr<Shelf> shelf = std::shared_ptr<Shelf>(new Shelf(animal));

        if(!dogOldest && animal->typeOf() == DOG)
            dogOldest = shelf;

        if (!catOldest && animal->typeOf() == CAT)
            catOldest = shelf;

        if(!shelves) {
            animalOldest = shelf;
        } else {
            shelves->next = shelf;
        }
        shelves = shelf;
    }

    void update(std::shared_ptr<Shelf> &shelf, TYPE type) {

        std::shared_ptr<Shelf> newOld = shelf->next;
        while(newOld && newOld->animal->typeOf() != type)
            newOld = newOld->next;

        shelf = newOld;
    }


    std::shared_ptr<Animal> dequeueAny() {
        if (!animalOldest)
            return nullptr;

        if (animalOldest == dogOldest) {
            update(dogOldest, DOG);
        }
        else if (animalOldest == catOldest) {
            update(catOldest, CAT);
        }

        std::cout << "DEQUEUE ANIMAL ";
        std::shared_ptr<Animal> animal = animalOldest->animal;
        animal->print();

        animalOldest = animalOldest->next;
        return animal;
    }

    void updatePre(std::shared_ptr<Shelf> shelf) {

        std::shared_ptr<Shelf> oldestPre = animalOldest;
        while(oldestPre->next && oldestPre->next != shelf)
            oldestPre = oldestPre->next;

        oldestPre->next = shelf->next;
    }

    std::shared_ptr<Animal> dequeueCat() {
        if(!catOldest)
            return nullptr;

        if(catOldest == animalOldest)
            return dequeueAny();

        std::cout << "DEQUEUE ANIMAL ";
        std::shared_ptr<Animal> animal = catOldest->animal;
        animal->print();
        std::shared_ptr<Shelf> cat = catOldest;
        update(catOldest, CAT);
        updatePre(cat);
        return animal;
    }

    std::shared_ptr<Animal> dequeueDog() {
        if(!dogOldest)
            return nullptr;

        if(dogOldest == animalOldest)
            return dequeueAny();


        std::cout << "DEQUEUE ANIMAL ";
        std::shared_ptr<Animal> animal = dogOldest->animal;
        animal->print();
        auto dog = dogOldest;
        update(dogOldest, DOG);
        updatePre(dog);
        return animal;
    }

private:
    std::shared_ptr<Shelf> shelves, dogOldest, catOldest, animalOldest;
};

int main() {

    Shelter shelter;
    shelter.enqueue(std::shared_ptr<Cat>(new Cat(1)));
    shelter.enqueue(std::shared_ptr<Cat>(new Cat(2)));
    shelter.enqueue(std::shared_ptr<Cat>(new Cat(3)));
    shelter.enqueue(std::shared_ptr<Dog>(new Dog(1)));
    shelter.enqueue(std::shared_ptr<Cat>(new Cat(4)));
    shelter.enqueue(std::shared_ptr<Dog>(new Dog(2)));
    shelter.enqueue(std::shared_ptr<Cat>(new Cat(5)));

    std::cout << "DEQUEUE \n";
    shelter.dequeueDog();
    shelter.dequeueAny();
    shelter.dequeueCat();
    shelter.dequeueAny();
    shelter.dequeueAny();
    shelter.dequeueAny();
    shelter.dequeueAny();
    shelter.dequeueAny();
    shelter.dequeueAny();
    shelter.dequeueAny();
    shelter.dequeueAny();
    shelter.dequeueAny();

    return 0;
}