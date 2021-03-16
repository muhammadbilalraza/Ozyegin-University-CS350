/*
    Program name: What2Eat.c 
    Description: The program simulates a small game and has two rounds.
    In the first round, the program shortlists based upon threshold value
    and ask players to choose from the shortlist. It then adds the item with the 
    highest weight to the order.
    Copyright (C) 2021  Bilal Raza (bilal.raza@ozu.edu.tr)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see https://www.gnu.org/licenses.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum item
{
    Kebab,
    Burger,
    Pasta,
    Lahmacun,
    Salad
};

//getItem
int getItem(int i)
{
    if (i == Kebab)
    {
        return Kebab;
    }
    else if (i == Burger)
    {
        return Burger;
    }
    else if (i == Pasta)
    {
        return Pasta;
    }
    else if (i == Lahmacun)
    {
        return Lahmacun;
    }
    else if (i == Salad)
    {
        return Salad;
    }
}

//print menu items comparing enum
void printItem(int i)
{
    if (i == Kebab)
        printf("Kebab\n");
    else if (i == Burger)
        printf("Burger\n");
    else if (i == Pasta)
        printf("Pasta\n");
    else if (i == Lahmacun)
        printf("Lahmacun\n");
    else if (i == Salad)
        printf("Salad\n");
}

const int menuSize = 5;
const int THRESHOLD = 10;

//print menu for the first round
void printMenu()
{
    printf("Choose from the following (Enter the number):\n");
    printf("1- Kebab\n");
    printf("2- Burger\n");
    printf("3- Pasta\n");
    printf("4- Lahmacun\n");
    printf("5- Salad\n");
}

//short list funciton for the first round
int shortlist(int firstOrderList[])
{
    int temp = 0;
    bool flag = true;
    for (int i = 0; i < menuSize; ++i)
    {
        if (firstOrderList[i] > THRESHOLD)
        {
            if (flag)
            {
                printf("Shortlit:\n");
                flag = false;
            }
            ++temp;
            printf("%d- ", i + 1);
            printItem(i);
        }
    }
    return temp;
}

//get list to choose from for second round
void getRecordListItems(int secondOrderList[], int size, int firstOrderList[])
{
    int j = 0;
    for (int i = 0; i < menuSize; ++i)
    {
        if (firstOrderList[i] > THRESHOLD)
        {
            secondOrderList[j] = getItem(i);
            ++j;
        }
    }
}

void order(int list[], int *ppl, int *choices, int *maxChoices)
{
    int i = 0;
    int preference = 0;
    while (i < *ppl)
    {
        *choices = *maxChoices;
        printf("Person %d\n", i + 1);
        while (*choices != 0)
        {
            int choose = 0;
            printf("%d preference: ", ++preference);
            scanf("%d", &choose);
            if (choose <= *maxChoices && choose >= 0)
            {
                list[choose - 1] += *choices;
                --*choices;
            }
            else
            {
                printf("Invalid option!\nTry running again!\n");
                exit(0);
            }
        }
        preference = 0;
        ++i;
    }
}

int main()
{

    int ppl = 0;
    int choices = 0;

    int *firstOrderList = (int *)calloc(menuSize, sizeof(int));

    printf("No. of people: ");
    scanf("%d", &ppl);

    int maxChoices = 5;
    printMenu();
    printf("\n--- First round ---\n");
    printf("--- Choose from the menu ---\n");

    order(firstOrderList, &ppl, &choices, &maxChoices);

    //shortlisting using the Threshold and getting the size for the new array
    int newListSize = shortlist(firstOrderList);

    //second round if no new list size is zero, means no item passed the threshold in the first round
    if (newListSize != 0)
    {
        int *newList = (int *)calloc(newListSize, sizeof(int));
        int *secondOrderList = (int *)calloc(newListSize, sizeof(int));
        getRecordListItems(secondOrderList, newListSize, firstOrderList);

        maxChoices = newListSize;

        printf("\n--- Second round ---\n");
        printf("--- Choose from the shortlist ---\n");

        choices = 0;
        order(newList, &ppl, &choices, &maxChoices);

        int max = newList[0];
        int maxIndex = 0;
        for (int i = 1; i < maxChoices; ++i)
        {
            if (newList[i] > max)
            {
                max = newList[i];
                maxIndex = i;
            }
        }

        printf("Include the following in the shortlisted order: ");
        printItem(maxIndex);
    }
    else
    {
        printf("You are eating at home/dorm today!\n");
    }

    return 0;
}

