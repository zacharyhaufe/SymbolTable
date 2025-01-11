/**
 * @file hw1_wvuep.c
 * @brief File with code written for CS 350 Homework #1: WVU Enrollment Problem
 * @author Zachary Haufe
 *
 *
 */

// Include statements
#include "hw1_wvuep.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

// Function prototypes
const char* get_programmer_name(void);
int prompt_target_enrollment(int target_year);
double calculate_growth_rate(int initial_enrollment, int target_enrollment, int initial_year, int target_year);
const char* get_growth_rate_description(double growth_rate);
void print_growth_rate(double growth_rate);
int calculate_enrollment_estimate(int initial_enrollment, double growth_rate, int initial_year, int estimate_year);
void print_enrollment_estimates(int initial_enrollment, double growth_rate, int initial_year, int end_year);


const char* get_programmer_name(void)
{
    return "Zachary Haufe";
}


int prompt_target_enrollment(int target_year)
{
    char input[100]; // Allocate enough memory for input, assuming it won't exceed 100 characters
    int target_enrollment = 0; // Variable to store the target enrollment
    
    do
    {
        // Prompt the user for the enrollment target
        printf("Enter the enrollment target for the year %d: ", target_year);
        
        // Get user input
        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            int valid = 1; // Flag to check if the input contains only digits
            
            // Iterate over each character to ensure it is a digit or newline
            for (int i = 0; input[i] != '\0' && input[i] != '\n'; i++)
            {
                if (!isdigit(input[i])) // Check if character is not a digit
                {
                    valid = 0; // Set to 0 if an invalid character is found
                    break; // Stop checking if the input is invalid
                }
            }
            
            if (valid)
            {
                target_enrollment = atoi(input); // Converts input string to an integer
                if (target_enrollment > 0) // Ensure the target enrollment is positive.
                {
                    return target_enrollment;
                }
            }
                     
            }
        // If input is invalid, display error message prompting user to try again
        printf("Invalid input. Please enter a positive integer: ");
    }
    while (1); // Continue looping until valid input is recieved
}


double calculate_growth_rate(int initial_enrollment, int target_enrollment, int initial_year, int target_year)
{
    // Calculate the number of years for equation
    int years = target_year - initial_year;

    // If years is 0 or initial enrollment is 0, return 0 to avoid division by zero or invalid growth
    if (years == 0 || initial_enrollment == 0)
    {
        return 0;
    }

    // Calculate the growth rate using the formula
    double growth_rate = pow((double)target_enrollment / initial_enrollment, 1.0 / years) - 1;

    // Return growth rate
    return growth_rate;
}


const char* get_growth_rate_description(double growth_rate)
{
  
    // Create the description based on the growth rate
    if (growth_rate < 0.0)
    {
        return("negative");
    }
    else if (growth_rate < .01)
    {
        return("reasonable");
    }
    else if (growth_rate < .02)
    {
        return("ambitious");
    }
    else if (growth_rate < .04)
    {
        return("high");
    }
    else
    {
        return("unreasonable");
    }
}


void print_growth_rate(double growth_rate)
{
    const char* description = get_growth_rate_description(growth_rate); // Get the description of the growth rate by calling the function
    printf("The required annual rate of growth, %.1f%%, is %s.\n", (growth_rate * 100), description);
}


int calculate_enrollment_estimate(int initial_enrollment, double growth_rate, int initial_year, int estimate_year)
{
    // Calculate years for equation
    int years = estimate_year - initial_year;

    // Calculate the estimated enrollment using equation
    double estimated_enrollment = initial_enrollment * pow(1 + growth_rate, years);

    // Return the estimated enrollment rounded to the nearest integer
    return (int)(estimated_enrollment + 0.5);
}


void print_enrollment_estimates(int initial_enrollment, double growth_rate, int initial_year, int end_year)
{
    for (int year = initial_year; year <= end_year; year++)
    {
        // Calculate the enrollment estimate for the current year
        int enrollment_estimate = calculate_enrollment_estimate(initial_enrollment, growth_rate, initial_year, year);
        
        // Print the enrollment estimate in the specified format
        printf("%d enrollment estimate: %d\n", year, enrollment_estimate);
    }
}

