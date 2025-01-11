/**
 * @file test_hw1_wvuep.c
 * @brief Tests source code file for CS 350 Homework #1: WVU Enrollment Problem
 * @author Brian Powell
 * @version 3.2
 *
 * Place this file in the same directory as your own source code and add it to your project.
 *
 * DO NOT MODIFY THE CONTENTS OF THIS FILE.
 */

 // Use GNU source for kill and usleep functions
#define _GNU_SOURCE

// Set timeout for forked processes
#define TIMEOUT_SECONDS 15

#include "ctest.h"
#include "unity.h"
#include "hw1_wvuep.h"
#include "test_hw1_wvuep.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <signal.h>
#include <time.h>

// Track original runner PID
pid_t runner_pid;

// Access Unity status
extern struct UNITY_STORAGE_T Unity;

// Define variables to track if functions have been implemented
static bool not_implemented_get_programmer_name = false;
static bool not_implemented_prompt_target_enrollment = false;
static bool not_implemented_calculate_growth_rate = false;
static bool not_implemented_get_growth_rate_description = false;
static bool not_implemented_print_growth_rate = false;
static bool not_implemented_calculate_enrollment_estimate = false;
static bool not_implemented_print_enrollment_estimates = false;

// Define variables to track if functions crash
static bool crashes_get_programmer_name = false;
static bool crashes_prompt_target_enrollment = false;
static bool crashes_calculate_growth_rate = false;
static bool crashes_get_growth_rate_description = false;
static bool crashes_print_growth_rate = false;
static bool crashes_calculate_enrollment_estimate = false;
static bool crashes_print_enrollment_estimates = false;

// Provide weak versions of functions from hw1_wvuep.h
// Do not modify these functions. They will be superseded by the actual functions in hw1_wvuep.c.
int __attribute__((weak)) prompt_target_enrollment(int target_year)
{
	printf("prompt_target_enrollment is not implemented\n");

	// Mark function as not implemented
	not_implemented_prompt_target_enrollment = true;

	return 0; // Do not use default
}

double __attribute__((weak)) calculate_growth_rate(int initial_enrollment, int target_enrollment, int initial_year, int target_year)
{
	printf("calculate_growth_rate is not implemented\n");

	// Mark function as not implemented
	not_implemented_calculate_growth_rate = true;

	return UNIMPLEMENTED_RETURN_INT;
}

const char* __attribute__((weak)) get_growth_rate_description(double growth_rate)
{
	printf("get_growth_rate_description is not implemented\n");

	// Mark function as not implemented
	not_implemented_get_growth_rate_description = true;

	return UNIMPLEMENTED_RETURN_POINTER;
}

void __attribute__((weak)) print_growth_rate(double growth_rate)
{
	printf("print_growth_rate is not implemented\n");

	// Mark function as not implemented
	not_implemented_print_growth_rate = true;

	// Do nothing
}

int __attribute__((weak)) calculate_enrollment_estimate(int initial_enrollment, double growth_rate, int initial_year, int estimate_year)
{
	printf("calculate_enrollment_estimate is not implemented\n");

	// Mark function as not implemented
	not_implemented_calculate_enrollment_estimate = true;

	return 0; // Do not use default
}

void __attribute__((weak)) print_enrollment_estimates(int initial_enrollment, double growth_rate, int initial_year, int end_year)
{
	printf("print_enrollment_estimates is not implemented\n");

	// Mark function as not implemented
	not_implemented_print_enrollment_estimates = true;

	// Do nothing
}

const char* __attribute__((weak)) get_programmer_name(void)
{
	printf("get_programmer_name is not implemented\n");

	// Mark function as not implemented
	not_implemented_get_programmer_name = true;

	return UNIMPLEMENTED_RETURN_POINTER;
}

void run_tests(void)
{
	// Display status
	puts("");
	puts("==========");
	puts("Running tests...");
	puts("");

	// Run tests
	UNITY_BEGIN();

	puts("Step 2c: Running get_programmer_name tests...");
	RUN_TEST(test_2c_get_programmer_name);
	puts("");

	puts("Step 2d: Running prompt_target_enrollment tests...");
	RUN_TEST(test_2d_prompt_target_enrollment_prompt);
	RUN_TEST(test_2d_prompt_target_enrollment_alphabetic);
	RUN_TEST(test_2d_prompt_target_enrollment_zero);
	RUN_TEST(test_2d_prompt_target_enrollment_negative);
	RUN_TEST(test_2d_prompt_target_enrollment_positive);
	puts("");

	puts("Step 2e: Running calculate_growth_rate tests...");
	RUN_TEST(test_2e_calculate_growth_rate_zero);
	RUN_TEST(test_2e_calculate_growth_rate_positive);
	RUN_TEST(test_2e_calculate_growth_rate_negative);
	puts("");

	puts("Step 2f: Running get_growth_rate_description tests...");
	RUN_TEST(test_2f_get_growth_rate_description_negative);
	RUN_TEST(test_2f_get_growth_rate_description_reasonable);
	RUN_TEST(test_2f_get_growth_rate_description_ambitious);
	RUN_TEST(test_2f_get_growth_rate_description_high);
	RUN_TEST(test_2f_get_growth_rate_description_unreasonable);
	puts("");

	puts("Step 2g: Running print_growth_rate tests...");
	RUN_TEST(test_2g_print_growth_rate);
	puts("");

	puts("Step 2h: Running calculate_enrollment_estimate tests...");
	RUN_TEST(test_2h_calculate_enrollment_estimate);
	puts("");

	puts("Step 2i: Running print_enrollment_estimates tests...");
	RUN_TEST(test_2i_print_enrollment_estimates_first);
	RUN_TEST(test_2i_print_enrollment_estimates_last);
	puts("");

	UNITY_END();

	// Display message about evaluating with different unit tests 
	puts("");
	puts("Your instructor may evaluate your program with different unit tests than were provided to you.");

	// Display blank lines
	puts("");
	puts("==========");
	puts("");
}

void setUp(void)
{
	// set up test environment
}

void tearDown(void)
{
	// clean up test environment
}

void test_2e_calculate_growth_rate_zero(void)
{
	TEST_ASSERT_EQUAL_DOUBLE(0.0, helper_calculate_growth_rate(30000, 30000, 2022, 2023));
}

void test_2e_calculate_growth_rate_negative(void)
{
	TEST_ASSERT_EQUAL_DOUBLE(-0.02, helper_calculate_growth_rate(25000, 24010, 2024, 2026));
}

void test_2e_calculate_growth_rate_positive(void)
{
	TEST_ASSERT_EQUAL_DOUBLE(0.1, helper_calculate_growth_rate(30000, 39930, 2030, 2033));
}

void test_2c_get_programmer_name(void)
{
	// Use helper function to get programmer name
	const char* actual = helper_get_programmer_name();

	// Check that the string is not NULL
	TEST_ASSERT_NOT_NULL_MESSAGE(actual, "The get_programmer_name function returned NULL.");

	// Check that the string is not empty
	TEST_ASSERT_NOT_EMPTY_MESSAGE(actual, "The programmer name is empty.");
}

void test_2f_get_growth_rate_description_negative(void)
{
	// Get growth rate description
	const char* actual = helper_get_growth_rate_description(-0.01);

	// Check that the string is not NULL, not empty and is equal to the appropriate value
	TEST_ASSERT_NOT_NULL(actual);
	if (actual != NULL)
	{
		TEST_ASSERT_NOT_EMPTY(actual);
		TEST_ASSERT_EQUAL_STRING("negative", actual);
	}
}

void test_2f_get_growth_rate_description_reasonable(void)
{
	// Get growth rate description
	const char* actual = helper_get_growth_rate_description(0);

	// Check that the string is not NULL, not empty and is equal to the appropriate value
	TEST_ASSERT_NOT_NULL(actual);
	if (actual != NULL)
	{
		TEST_ASSERT_NOT_EMPTY(actual);
		TEST_ASSERT_EQUAL_STRING("reasonable", actual);
	}

	// Get growth rate description
	actual = helper_get_growth_rate_description(0.005);

	// Check that the string is not NULL, not empty and is equal to the appropriate value
	TEST_ASSERT_NOT_NULL(actual);
	if (actual != NULL)
	{
		TEST_ASSERT_NOT_EMPTY(actual);
		TEST_ASSERT_EQUAL_STRING("reasonable", actual);
	}

	// Get growth rate description
	actual = helper_get_growth_rate_description(0.0099);

	// Check that the string is not NULL, not empty and is equal to the appropriate value
	TEST_ASSERT_NOT_NULL(actual);
	if (actual != NULL)
	{
		TEST_ASSERT_NOT_EMPTY(actual);
		TEST_ASSERT_EQUAL_STRING("reasonable", actual);
	}
}

void test_2f_get_growth_rate_description_ambitious(void)
{
	// Get growth rate description
	const char* actual = helper_get_growth_rate_description(0.01);

	// Check that the string is not NULL, not empty and is equal to the appropriate value
	TEST_ASSERT_NOT_NULL(actual);
	if (actual != NULL)
	{
		TEST_ASSERT_NOT_EMPTY(actual);
		TEST_ASSERT_EQUAL_STRING("ambitious", actual);
	}

	// Get growth rate description
	actual = helper_get_growth_rate_description(0.015);

	// Check that the string is not NULL, not empty and is equal to the appropriate value
	TEST_ASSERT_NOT_NULL(actual);
	if (actual != NULL)
	{
		TEST_ASSERT_NOT_EMPTY(actual);
		TEST_ASSERT_EQUAL_STRING("ambitious", actual);
	}

	// Get growth rate description
	actual = helper_get_growth_rate_description(0.0199);

	// Check that the string is not NULL, not empty and is equal to the appropriate value
	TEST_ASSERT_NOT_NULL(actual);
	if (actual != NULL)
	{
		TEST_ASSERT_NOT_EMPTY(actual);
		TEST_ASSERT_EQUAL_STRING("ambitious", actual);
	}
}

void test_2f_get_growth_rate_description_high(void)
{
	// Get growth rate description
	const char* actual = helper_get_growth_rate_description(0.02);

	// Check that the string is not NULL, not empty and is equal to the appropriate value
	TEST_ASSERT_NOT_NULL(actual);
	if (actual != NULL)
	{
		TEST_ASSERT_NOT_EMPTY(actual);
		TEST_ASSERT_EQUAL_STRING("high", actual);
	}

	// Get growth rate description
	actual = helper_get_growth_rate_description(0.03);

	// Check that the string is not NULL, not empty and is equal to the appropriate value
	TEST_ASSERT_NOT_NULL(actual);
	if (actual != NULL)
	{
		TEST_ASSERT_NOT_EMPTY(actual);
		TEST_ASSERT_EQUAL_STRING("high", actual);
	}

	// Get growth rate description
	actual = helper_get_growth_rate_description(0.0399);

	// Check that the string is not NULL, not empty and is equal to the appropriate value
	TEST_ASSERT_NOT_NULL(actual);
	if (actual != NULL)
	{
		TEST_ASSERT_NOT_EMPTY(actual);
		TEST_ASSERT_EQUAL_STRING("high", actual);
	}
}

void test_2f_get_growth_rate_description_unreasonable(void)
{
	// Get growth rate description
	const char* actual = helper_get_growth_rate_description(0.04);

	// Check that the string is not NULL, not empty and is equal to the appropriate value
	TEST_ASSERT_NOT_NULL(actual);
	if (actual != NULL)
	{
		TEST_ASSERT_NOT_EMPTY(actual);
		TEST_ASSERT_EQUAL_STRING("unreasonable", actual);
	}

	// Get growth rate description
	actual = helper_get_growth_rate_description(0.05);

	// Check that the string is not NULL, not empty and is equal to the appropriate value
	TEST_ASSERT_NOT_NULL(actual);
	if (actual != NULL)
	{
		TEST_ASSERT_NOT_EMPTY(actual);
		TEST_ASSERT_EQUAL_STRING("unreasonable", actual);
	}

	// Get growth rate description
	actual = helper_get_growth_rate_description(0.1);

	// Check that the string is not NULL, not empty and is equal to the appropriate value
	TEST_ASSERT_NOT_NULL(actual);
	if (actual != NULL)
	{
		TEST_ASSERT_NOT_EMPTY(actual);
		TEST_ASSERT_EQUAL_STRING("unreasonable", actual);
	}
}

void test_2h_calculate_enrollment_estimate(void)
{
	// Calculate various enrollment estimates
	TEST_ASSERT_EQUAL(60511, helper_calculate_enrollment_estimate(29107, 0.05, 2020, 2035));
	TEST_ASSERT_EQUAL(19432, helper_calculate_enrollment_estimate(29107, -0.02, 2020, 2040));
	TEST_ASSERT_EQUAL(29107, helper_calculate_enrollment_estimate(29107, 0.03, 2035, 2035));
	TEST_ASSERT_EQUAL(29107, helper_calculate_enrollment_estimate(29107, 0, 2020, 2035));
}

void test_2i_print_enrollment_estimates_first(void)
{
	// Define filename to use
	char* filename = "test_print_enrollment_estimates_first.txt";

	// Create file to store output
	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);

	// Redirect stdout to file
	int saved_stdout = dup(STDOUT_FILENO);
	int saved_stderr = dup(STDERR_FILENO);
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);

	// Run function directly due to stdout capture issues with helper function
	print_enrollment_estimates(29107, 0.05, 2020, 2035);

	// Flush output
	fflush(stdout);
	fflush(stderr);

	// Redirect output to original destinations
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stderr, STDERR_FILENO);

	// Close file
	close(fd);

	// Open file for reading
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		// Remove file
		unlink(filename);

		TEST_FAIL_MESSAGE("Failed to open file for reading");
	}

	// Read first line
	char buffer[100];
	fgets(buffer, 100, file);

	// Close file
	fclose(file);

	// Remove file
	unlink(filename);

	// Get trimmed string
	char* trimmedPtr = testsupport_trim(buffer);

	// Check that the unimplemented message is not returned
	if (strcmp(trimmedPtr, "print_enrollment_estimates is not implemented") == 0)
	{
		// Record as not implemented
		not_implemented_print_enrollment_estimates = true;

		TEST_FAIL_MESSAGE("print_enrollment_estimates is not implemented.");
	}

	TEST_ASSERT_EQUAL_STRING("2020 enrollment estimate: 29107", trimmedPtr);

	// Free memory
	free(trimmedPtr);
	trimmedPtr = NULL;
}

void test_2i_print_enrollment_estimates_last(void)
{
	// Define filename to use
	char* filename = "test_print_enrollment_estimates_last.txt";

	// Create file to store output
	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);

	// Redirect stdout to file
	int saved_stdout = dup(STDOUT_FILENO);
	int saved_stderr = dup(STDERR_FILENO);
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);

	// Run function directly due to stdout capture issues with helper function
	print_enrollment_estimates(29107, 0.05, 2020, 2035);

	// Flush output
	fflush(stdout);
	fflush(stderr);

	// Redirect output to original destinations
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stderr, STDERR_FILENO);

	// Close file
	close(fd);

	// Open file for reading
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		// Remove file
		unlink(filename);

		TEST_FAIL_MESSAGE("Failed to open file for reading");
	}

	// Read all lines until last line
	char buffer[100];
	while (fgets(buffer, 100, file) != NULL)
	{
		// Do nothing - keep looping until final line
	}

	// Close file
	fclose(file);

	// Remove file
	unlink(filename);

	// Get trimmed string
	char* trimmedPtr = testsupport_trim(buffer);

	// Check that the unimplemented message is not returned
	if (strcmp(trimmedPtr, "print_enrollment_estimates is not implemented") == 0)
	{
		// Record as not implemented
		not_implemented_print_enrollment_estimates = true;

		TEST_FAIL_MESSAGE("print_enrollment_estimates is not implemented.");
	}

	TEST_ASSERT_EQUAL_STRING("2035 enrollment estimate: 60511", trimmedPtr);

	// Free memory
	free(trimmedPtr);
	trimmedPtr = NULL;
}

void test_2g_print_growth_rate(void)
{
	// Define filename to use
	char* filename = "test_print_growth_rate.txt";

	// Create file to store output
	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);

	// Redirect stdout to file
	int saved_stdout = dup(STDOUT_FILENO);
	int saved_stderr = dup(STDERR_FILENO);
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);

	// Run function directly due to stdout capture issues with helper function
	print_growth_rate(0.025);

	// Flush output
	fflush(stdout);
	fflush(stderr);

	// Redirect output to original destinations
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stderr, STDERR_FILENO);

	// Close file
	close(fd);

	// Open file for reading
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		// Remove file
		unlink(filename);

		TEST_FAIL_MESSAGE("Failed to open file for reading");
	}

	// Read first line
	char buffer[100];
	fgets(buffer, 100, file);

	// Close file
	fclose(file);

	// Remove file
	unlink(filename);

	// Get trimmed string
	char* trimmedPtr = testsupport_trim(buffer);

	// Check that the unimplemented message is not returned
	if (strcmp(trimmedPtr, "print_growth_rate is not implemented") == 0)
	{
		// Record as not implemented
		not_implemented_print_growth_rate = true;

		TEST_FAIL_MESSAGE("print_growth_rate is not implemented.");
	}

	TEST_ASSERT_EQUAL_STRING("The required annual rate of growth, 2.5%, is high.", trimmedPtr);

	// Free memory
	free(trimmedPtr);
	trimmedPtr = NULL;
}
void test_2d_prompt_target_enrollment_prompt(void)
{
	// Ensure function has been implemented
	TEST_ASSERT_FALSE_MESSAGE(not_implemented_prompt_target_enrollment, "prompt_target_enrollment has not been implemented.");

	// Define filenames to use
	char* filename = "test_prompt_target_enrollment_prompt.txt";

	// Create file to store output
	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);

	// Fork child process
	pid_t pid = fork();
	if (pid < 0)
	{
		TEST_FAIL_MESSAGE("Failed to fork child process");
	}
	else if (pid == 0)
	{
		// Redirect stdout to file
		int saved_stdout = dup(STDOUT_FILENO);
		int saved_stderr = dup(STDERR_FILENO);
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);

		// Run function
		helper_prompt_target_enrollment(2035);

		// Flush output
		fflush(stdout);
		fflush(stderr);

		// Redirect output to original destinations
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stderr, STDERR_FILENO);

		// Close file
		close(fd);

		// Remove files
		unlink(filename);

		// Exit child process
		exit(0);
	}
	else
	{
		// Sleep for 100 millieseconds
		struct timespec sleep_time = { 0, 100000000 };
		nanosleep(&sleep_time, NULL);

		// Attempt to kill child in case it is still running
		kill(pid, SIGKILL);

		// Wait for child process to complete
		int status;
		waitpid(pid, &status, 0);

		// Open file for reading
		FILE* output_file = fopen(filename, "r");
		if (output_file == NULL)
		{
			// Remove file
			unlink(filename);

			TEST_FAIL_MESSAGE("Failed to open file for reading.");
		}

		// Read first line
		char buffer[100];
		fgets(buffer, 100, output_file);

		// Close file
		fclose(output_file);
		output_file = NULL;

		// Remove file
		unlink(filename);

		// Get trimmed string
		char* trimmedPtr = testsupport_trim(buffer);

		// Check that the unimplemented message is not returned
		if (strcmp(trimmedPtr, "prompt_target_enrollment is not implemented") == 0)
		{
			// Record as not implemented
			not_implemented_prompt_target_enrollment = true;

			TEST_FAIL_MESSAGE("prompt_target_enrollment is not implemented.");
		}

		TEST_ASSERT_EQUAL_STRING("Enter the enrollment target for the year 2035:", trimmedPtr);

		// Free memory
		free(trimmedPtr);
		trimmedPtr = NULL;
	}
}

void test_2d_prompt_target_enrollment_negative(void)
{
	// Ensure function has been implemented
	TEST_ASSERT_FALSE_MESSAGE(not_implemented_prompt_target_enrollment, "prompt_target_enrollment has not been implemented.");

	// Specify test values
	int year = 2022;
	int enrollment = 17287;

	// Define filenames to use
	char* input_filename = "test_prompt_target_enrollment_negative_input.txt";
	char* output_filename = "test_prompt_target_enrollment_negative_output.txt";

	// Define shared key
	int key = 1863;

	// Write input file
	FILE* input_file = fopen(input_filename, "w");
	if (input_file == NULL)
	{
		// Remove file
		unlink(input_filename);

		TEST_FAIL_MESSAGE("Failed to open file for writing");
	}

	// Write input to file
	fprintf(input_file, "-5\n");
	fprintf(input_file, "-97\n");
	fprintf(input_file, "%d\n", enrollment);

	// Close input file
	fclose(input_file);
	input_file = NULL;

	// Create file to store output
	int output_fd = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	int input_fd = open(input_filename, O_RDONLY, 0666);

	// Setup shared memory for getting results from child process
	int shm_id = shmget(key, sizeof(int), SHM_R | SHM_W | IPC_CREAT);
	int* sharedPtr = shmat(shm_id, NULL, 0);
	*sharedPtr = 0;

	// Fork child process
	pid_t pid = fork();
	if (pid < 0)
	{
		// Remove files
		unlink(input_filename);
		unlink(output_filename);

		TEST_FAIL_MESSAGE("Failed to fork child process");
	}
	else if (pid == 0)
	{
		// Redirect stdout to file
		int saved_stdout = dup(STDOUT_FILENO);
		int saved_stderr = dup(STDERR_FILENO);
		int saved_stdin = dup(STDIN_FILENO);
		dup2(output_fd, STDOUT_FILENO);
		dup2(output_fd, STDERR_FILENO);
		dup2(input_fd, STDIN_FILENO);

		// Get result from function
		*sharedPtr = helper_prompt_target_enrollment(year);

		// Flush output
		fflush(stdout);
		fflush(stderr);

		// Redirect output to original destinations
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stderr, STDERR_FILENO);
		dup2(saved_stdin, STDIN_FILENO);

		// Close file
		close(output_fd);
		close(input_fd);

		// Remove files
		unlink(output_filename);
		unlink(input_filename);

		// Clean up shared memory
		shmdt(sharedPtr);
		shmctl(shm_id, IPC_RMID, NULL);

		// Exit child process
		exit(0);
	}
	else
	{
		// Sleep for 100 millieseconds
		struct timespec sleep_time = { 0, 100000000 };
		nanosleep(&sleep_time, NULL);

		// Attempt to kill child in case it is still running
		kill(pid, SIGKILL);

		// Wait for child process to complete
		int status;
		waitpid(pid, &status, 0);

		// Fail test if return value was not 0
		if (status != 0)
		{
			TEST_FAIL_MESSAGE("Did not properly handle negative input.");
		}

		// Ensure correct value was received
		TEST_ASSERT_EQUAL(enrollment, *sharedPtr);
	}
}

void test_2d_prompt_target_enrollment_zero(void)
{
	// Ensure function has been implemented
	TEST_ASSERT_FALSE_MESSAGE(not_implemented_prompt_target_enrollment, "prompt_target_enrollment has not been implemented.");

	// Specify test values
	int year = 2032;
	int enrollment = 26359;

	// Define filenames to use
	char* input_filename = "test_prompt_target_enrollment_zero_input.txt";
	char* output_filename = "test_prompt_target_enrollment_zero_output.txt";

	// Define shared key
	int key = 1863;

	// Write input file
	FILE* input_file = fopen(input_filename, "w");
	if (input_file == NULL)
	{
		// Remove file
		unlink(input_filename);

		TEST_FAIL_MESSAGE("Failed to open file for writing.");
	}

	// Write input to file
	fprintf(input_file, "0\n");
	fprintf(input_file, "0\n");
	fprintf(input_file, "%d\n", enrollment);

	// Close input file
	fclose(input_file);
	input_file = NULL;

	// Create file to store output
	int output_fd = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	int input_fd = open(input_filename, O_RDONLY, 0666);

	// Setup shared memory for getting results from child process
	int shm_id = shmget(key, sizeof(int), SHM_R | SHM_W | IPC_CREAT);
	int* sharedPtr = shmat(shm_id, NULL, 0);
	*sharedPtr = 0;

	// Fork child process
	pid_t pid = fork();
	if (pid < 0)
	{
		// Remove files
		unlink(input_filename);
		unlink(output_filename);

		TEST_FAIL_MESSAGE("Failed to fork child process.");
	}
	else if (pid == 0)
	{
		// Redirect stdout to file
		int saved_stdout = dup(STDOUT_FILENO);
		int saved_stderr = dup(STDERR_FILENO);
		int saved_stdin = dup(STDIN_FILENO);
		dup2(output_fd, STDOUT_FILENO);
		dup2(output_fd, STDERR_FILENO);
		dup2(input_fd, STDIN_FILENO);

		// Get result from function
		*sharedPtr = helper_prompt_target_enrollment(year);

		// Flush output
		fflush(stdout);
		fflush(stderr);

		// Redirect output to original destinations
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stderr, STDERR_FILENO);
		dup2(saved_stdin, STDIN_FILENO);

		// Close file
		close(output_fd);
		close(input_fd);

		// Remove files
		unlink(output_filename);
		unlink(input_filename);

		// Clean up shared memory
		shmdt(sharedPtr);
		shmctl(shm_id, IPC_RMID, NULL);

		// Exit child process
		exit(0);
	}
	else
	{
		// Sleep for 100 millieseconds
		struct timespec sleep_time = { 0, 100000000 };
		nanosleep(&sleep_time, NULL);

		// Attempt to kill child in case it is still running
		kill(pid, SIGKILL);

		// Wait for child process to complete
		int status;
		waitpid(pid, &status, 0);

		// Fail test if return value was not 0
		if (status != 0)
		{
			TEST_FAIL_MESSAGE("Did not properly handle zero-valued input.");
		}

		// Ensure correct value was received
		TEST_ASSERT_EQUAL(enrollment, *sharedPtr);
	}
}

void test_2d_prompt_target_enrollment_positive(void)
{
	// Ensure function has been implemented
	TEST_ASSERT_FALSE_MESSAGE(not_implemented_prompt_target_enrollment, "prompt_target_enrollment has not been implemented.");

	// Specify test values
	int year = 2037;
	int enrollment = 18630;

	// Define filenames to use
	char* input_filename = "test_prompt_target_enrollment_positive_input.txt";
	char* output_filename = "test_prompt_target_enrollment_positive_output.txt";

	// Define shared key
	int key = 1863;

	// Write input file
	FILE* input_file = fopen(input_filename, "w");
	if (input_file == NULL)
	{
		// Remove file
		unlink(input_filename);

		TEST_FAIL_MESSAGE("Failed to open file for writing.");
	}

	// Write input to file
	fprintf(input_file, "%d\n", enrollment);

	// Close input file
	fclose(input_file);
	input_file = NULL;

	// Create file to store output
	int output_fd = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	int input_fd = open(input_filename, O_RDONLY, 0666);

	// Setup shared memory for getting results from child process
	int shm_id = shmget(key, sizeof(int), SHM_R | SHM_W | IPC_CREAT);
	int* sharedPtr = shmat(shm_id, NULL, 0);
	*sharedPtr = 0;

	// Fork child process
	pid_t pid = fork();
	if (pid < 0)
	{
		// Remove files
		unlink(input_filename);
		unlink(output_filename);

		TEST_FAIL_MESSAGE("Failed to fork child process.");
	}
	else if (pid == 0)
	{

		// Redirect stdout to file
		int saved_stdout = dup(STDOUT_FILENO);
		int saved_stderr = dup(STDERR_FILENO);
		int saved_stdin = dup(STDIN_FILENO);
		dup2(output_fd, STDOUT_FILENO);
		dup2(output_fd, STDERR_FILENO);
		dup2(input_fd, STDIN_FILENO);

		// Get result from function
		*sharedPtr = helper_prompt_target_enrollment(year);

		// Flush output
		fflush(stdout);
		fflush(stderr);

		// Redirect output to original destinations
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stderr, STDERR_FILENO);
		dup2(saved_stdin, STDIN_FILENO);

		// Close file
		close(output_fd);
		close(input_fd);

		// Remove files
		unlink(output_filename);
		unlink(input_filename);

		// Clean up shared memory
		shmdt(sharedPtr);
		shmctl(shm_id, IPC_RMID, NULL);

		// Exit child process
		exit(0);
	}
	else
	{
		// Sleep for 100 millieseconds
		struct timespec sleep_time = { 0, 100000000 };
		nanosleep(&sleep_time, NULL);

		// Attempt to kill child in case it is still running
		kill(pid, SIGKILL);

		// Wait for child process to complete
		int status;
		waitpid(pid, &status, 0);

		// Fail test if return value was not 0
		if (status != 0)
		{
			TEST_FAIL_MESSAGE("Did not properly handle positive input.");
		}

		// Ensure correct value was received
		TEST_ASSERT_EQUAL(enrollment, *sharedPtr);
	}
}

void test_2d_prompt_target_enrollment_alphabetic(void)
{
	// Ensure function has been implemented
	TEST_ASSERT_FALSE_MESSAGE(not_implemented_prompt_target_enrollment, "prompt_target_enrollment has not been implemented.");

	// Specify test values
	int year = 2024;
	int enrollment = 29862;

	// Define filenames to use
	char* input_filename = "test_prompt_target_enrollment_alphabetic_input.txt";
	char* output_filename = "test_prompt_target_enrollment_alphabetic_output.txt";

	// Define shared key
	int key = 1863;

	// Write input file
	FILE* input_file = fopen(input_filename, "w");
	if (input_file == NULL)
	{
		TEST_FAIL_MESSAGE("Failed to open file for writing.");
	}

	// Write input to file
	fprintf(input_file, "abc\n");
	fprintf(input_file, "def\n");
	fprintf(input_file, "%d\n", enrollment);

	// Close input file
	fclose(input_file);
	input_file = NULL;

	// Create file to store output
	int output_fd = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	int input_fd = open(input_filename, O_RDONLY, 0666);

	// Setup shared memory for getting results from child process
	int shm_id = shmget(key, sizeof(int), SHM_R | SHM_W | IPC_CREAT);
	int* sharedPtr = shmat(shm_id, NULL, 0);
	*sharedPtr = 0;

	// Fork child process
	pid_t pid = fork();
	if (pid < 0)
	{
		TEST_FAIL_MESSAGE("Failed to fork child process.");
	}
	else if (pid == 0)
	{
		// Redirect stdout to file
		int saved_stdout = dup(STDOUT_FILENO);
		int saved_stderr = dup(STDERR_FILENO);
		int saved_stdin = dup(STDIN_FILENO);
		dup2(output_fd, STDOUT_FILENO);
		dup2(output_fd, STDERR_FILENO);
		dup2(input_fd, STDIN_FILENO);

		// Get result from function
		*sharedPtr = helper_prompt_target_enrollment(year);

		// Flush output
		fflush(stdout);
		fflush(stderr);

		// Redirect output to original destinations
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stderr, STDERR_FILENO);
		dup2(saved_stdin, STDIN_FILENO);

		// Close file
		close(output_fd);
		close(input_fd);

		// Remove files
		unlink(output_filename);
		unlink(input_filename);

		// Clean up shared memory
		shmdt(sharedPtr);
		shmctl(shm_id, IPC_RMID, NULL);

		// Exit child process
		exit(0);
	}
	else
	{
		// Sleep for 100 millieseconds
		struct timespec sleep_time = { 0, 100000000 };
		nanosleep(&sleep_time, NULL);

		// Attempt to kill child in case it is still running
		kill(pid, SIGKILL);

		// Wait for child process to complete
		int status;
		waitpid(pid, &status, 0);

		// Fail test if return value was not 0
		if (status != 0)
		{
			TEST_FAIL_MESSAGE("Did not properly handle alphabetic input.");
		}

		// Ensure correct value was received
		TEST_ASSERT_EQUAL(enrollment, *sharedPtr);
	}
}

const char* helper_get_programmer_name(void)
{
	// Check if function works in forked process
	CALL_FUNCTION_STRING(get_programmer_name);

	// Return programmer name
	return get_programmer_name();

}

int helper_prompt_target_enrollment(int target_year)
{
	// Do not call function in a forked process because of corruption of input stream

	// Assume that we don't crash
	crashes_prompt_target_enrollment = false;

	// Prompt for target enrollment
	return prompt_target_enrollment(target_year);
}

double helper_calculate_growth_rate(int initial_enrollment, int target_enrollment, int initial_year, int target_year)
{
	// Check if function works in forked process
	CALL_FUNCTION_DOUBLE(calculate_growth_rate, initial_enrollment, target_enrollment, initial_year, target_year);

	// Return growth rate
	return calculate_growth_rate(initial_enrollment, target_enrollment, initial_year, target_year);
}

const char* helper_get_growth_rate_description(double growth_rate)
{
	// Check if function works in forked process
	CALL_FUNCTION_STRING(get_growth_rate_description, growth_rate);

	// Return growth rate description
	return get_growth_rate_description(growth_rate);
}

void helper_print_growth_rate(double growth_rate)
{
	// Check if function works in forked process
	CALL_FUNCTION_VOID(print_growth_rate, growth_rate);

	// Print growth rate
	print_growth_rate(growth_rate);
}

int helper_calculate_enrollment_estimate(int initial_enrollment, double growth_rate, int initial_year, int estimate_year)
{
	// Check if function works in forked process
	CALL_FUNCTION_INT(calculate_enrollment_estimate, initial_enrollment, growth_rate, initial_year, estimate_year);

	// Return enrollment estimate
	return calculate_enrollment_estimate(initial_enrollment, growth_rate, initial_year, estimate_year);
}

void helper_print_enrollment_estimates(int initial_enrollment, double growth_rate, int initial_year, int end_year)
{
	// Check if function works in forked process
	CALL_FUNCTION_VOID(print_enrollment_estimates, initial_enrollment, growth_rate, initial_year, end_year);

	// Print enrollment estimates
	print_enrollment_estimates(initial_enrollment, growth_rate, initial_year, end_year);
}

char* testsupport_trim(const char* string)
{
	// Start at beginning of string and find first non-space character
	size_t first_nonspace = 0;
	while ((first_nonspace < strlen(string)) && (isspace(string[first_nonspace])))
	{
		// Increment position
		first_nonspace++;
	}

	// Determine if there is anything non-whitespace left in the string
	if (first_nonspace == strlen(string))
	{
		// String is all whitespace, so return null-terminated string
		char* emptyPtr = malloc(sizeof(char) * 1);
		if (emptyPtr == NULL) {
			return NULL;
		}

		// Null terminate string
		emptyPtr[0] = '\0';

		return emptyPtr;
	}

	// Start at end of string and find last non-space character
	size_t last_nonspace = strlen(string) - 1;
	while ((last_nonspace >= first_nonspace) && isspace(string[last_nonspace]))
	{
		// Decrement position
		last_nonspace--;
	}

	// Determine size of trimmed string, not including null terminator
	size_t trimmed_length = last_nonspace - first_nonspace + 1;

	// Allocate new string
	char* trimmedPtr = malloc(sizeof(char) * (trimmed_length + 1));
	if (trimmedPtr == NULL) {
		return NULL;
	}

	// Copy trimmed string into new memory
	memcpy(trimmedPtr, &string[first_nonspace], trimmed_length);

	// Null terminate last position
	trimmedPtr[trimmed_length] = '\0';

	return trimmedPtr;
}