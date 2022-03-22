// LargestArea.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>

#define MAXSIZE 100      

int isempty(int* stack, int TOP) {

    if (TOP == -1)
        return 1;
    else
        return 0;
}

int isfull(int* stack, int TOP) {

    if (TOP == MAXSIZE)
        return 1;
    else
        return 0;
}

int top(int* stack, int TOP) {
    return stack[TOP];
}

int pop(int* stack, int* TOP) {
    int data;

    if (!isempty(stack, *TOP)) {
        data = stack[*TOP];
        *TOP = *TOP - 1;
        return data;
    }
    else {
        printf("Could not retrieve data, Stack is empty.\n");
        return -1;
    }
}

void push(int* stack, int* TOP, int data) {

    if (!isfull(stack, *TOP)) {
        *TOP = *TOP + 1;
        stack[*TOP] = data;

    }
    else {
        printf("Could not insert data, Stack is full.\n");
    }
}


int getMaxArea(int hist[], int n)
{
    // Create an empty stack. The stack holds indexes
    // of hist[] array. The bars stored in stack are
    // always in increasing order of their heights.    
    int s[MAXSIZE];
    int TOP = -1;

    int max_area = 0; // Initialize max area
    int tp;  // To store top of stack
    int area_with_top; // To store area with top bar
                       // as the smallest bar

    // Run through all bars of given histogram
    int i = 0;
    while (i < n)
    {
        // If this bar is higher than the bar on top
        // stack, push it to stack
        if (isempty(s, TOP) || hist[top(s, TOP)] <= hist[i])
            push(s, &TOP, i++);

        // If this bar is lower than top of stack,
        // then calculate area of rectangle with stack
        // top as the smallest (or minimum height) bar.
        // 'i' is 'right index' for the top and element
        // before top in stack is 'left index'
        else
        {
            tp = pop(s, &TOP);  // pop the top


            // Calculate the area with hist[tp] stack
            // as smallest bar
            area_with_top = hist[tp] * (isempty(s, TOP) ? i :
                i - top(s, TOP) - 1);

            // update max area, if needed
            if (max_area < area_with_top)
                max_area = area_with_top;
        }
    }

    // Now pop the remaining bars from stack and calculate
    // area with every popped bar as the smallest bar
    while (isempty(s, TOP) == 0)
    {
        tp = pop(s, &TOP);
        area_with_top = hist[tp] * (isempty(s, TOP) ? i :
            i - top(s, TOP) - 1);

        if (max_area < area_with_top)
            max_area = area_with_top;
    }

    return max_area;
}

int main()
{
    int hist[] = { 6, 2, 5, 4, 5, 1, 6 };
    int n = sizeof(hist) / sizeof(hist[0]);
    printf("Maximum area is %d", getMaxArea(hist, n));
    return 0;
}
