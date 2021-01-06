
#include <iostream>
#include "Packet.h"

typedef struct Student
{
    int age;
    int sex;
    
}Student;



int main(void)
{

    Student s1;
    s1.age = 18;
    s1.sex = 8888;
    Student s2;
    s2.age = 19;
    s2.sex = 9999;


    char buffer1[1024];
    const char buffer[1024] = {0};
    Packet::PackNum<Student>(buffer1,s1);
    Student s3;
    Packet::UnPackNum<Student>((const char*)buffer1,&s3);
    
    return 0;
}



