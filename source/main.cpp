/*
	Hello World example made by Aurelio Mannara for libctru
	This code was modified for the last time on: 12/12/2014 21:00 UTC+1
*/

#include <3ds.h>
#include <stdio.h>
#include "Todo.h"
#include "TodoList.h"

#define SECONDS_TO_NS(s) ((s64)(s) * 1000000000LL)
#define MS_TO_NS(ms) ((s64)(ms) * 1000000LL)

int main(int argc, char **argv)
{
	gfxInitDefault();

	// Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
	consoleInit(GFX_TOP, NULL);

	TodoList todoList;
	todoList.addTodo("Buy groceries");
	todoList.addTodo("Walk the dog");
	todoList.addTodo("Read a book");
	svcSleepThread(SECONDS_TO_NS(5));
	todoList.toggleTodo(2);
	printf("Todo List:\n%s\n", todoList.toString().c_str());

	svcSleepThread(SECONDS_TO_NS(5));
	// save to file
	if (todoList.saveToFile("save"))
	{
		consoleClear();
		printf("Todo list saved successfully.\n");
	}
	else
	{
		printf("Failed to save todo list.\n");
	}

	svcSleepThread(SECONDS_TO_NS(5));
	consoleClear();
	printf("Attempting to load saved file...\n");
	svcSleepThread(SECONDS_TO_NS(2));
	TodoList loadedTodoList;
	if (loadedTodoList.loadFromFile("save"))
	{
		consoleClear();
		printf("Loaded Todo List:\n%s\n", loadedTodoList.toString().c_str());
	}
	else
	{
		printf("Failed to load todo list.\n");
	}
	svcSleepThread(SECONDS_TO_NS(5));
	consoleClear();
	printf("Original Todo List:\n%s\n", todoList.toString().c_str());

	// ========== TEST 1: Save Override ==========
	svcSleepThread(SECONDS_TO_NS(5));
	consoleClear();
	printf("TEST 1: Save Override\n");
	printf("Adding new item and saving again...\n");
	todoList.addTodo("New item after first save");
	if (todoList.saveToFile("save"))
	{
		printf("Second save successful.\n");
	}

	svcSleepThread(SECONDS_TO_NS(5));
	TodoList reloadedList;
	if (reloadedList.loadFromFile("save"))
	{
		consoleClear();
		printf("TEST 1 Result - Reloaded after second save:\n%s\n", reloadedList.toString().c_str());
	}

	// ========== TEST 2: Empty List ==========
	svcSleepThread(SECONDS_TO_NS(5));
	consoleClear();
	printf("TEST 2: Empty Todo List\n");
	TodoList emptyList;
	if (emptyList.saveToFile("empty"))
	{
		printf("Empty list saved.\n");
	}
	
	svcSleepThread(SECONDS_TO_NS(5));
	TodoList loadedEmpty;
	if (loadedEmpty.loadFromFile("empty"))
	{
		consoleClear();
		printf("TEST 2 Result - Loaded empty list:\n%s\n", loadedEmpty.toString().c_str());
		printf("(Should be empty)\n");
	}

	// ========== TEST 3: Special Characters ==========
	svcSleepThread(SECONDS_TO_NS(5));
	consoleClear();
	printf("TEST 3: Special Characters\n");
	TodoList specialList;
	specialList.addTodo("Buy milk, eggs, bread");
	specialList.addTodo("Task with \"quotes\"");
	specialList.addTodo("Path: C:\\Users\\folder");
	if (specialList.saveToFile("special"))
	{
		printf("Special chars saved.\n");
	}

	svcSleepThread(SECONDS_TO_NS(5));
	TodoList loadedSpecial;
	if (loadedSpecial.loadFromFile("special"))
	{
		consoleClear();
		printf("TEST 3 Result - Loaded special chars:\n%s\n", loadedSpecial.toString().c_str());
	}

	// ========== TEST 4: Completion State ==========
	svcSleepThread(SECONDS_TO_NS(5));
	consoleClear();
	printf("TEST 4: Completion State Persistence\n");
	TodoList completionList;
	completionList.addTodo("Task 1");
	completionList.addTodo("Task 2");
	completionList.addTodo("Task 3");
	completionList.toggleTodo(1);  // Complete first
	completionList.toggleTodo(3);  // Complete third
	printf("Before save:\n%s\n", completionList.toString().c_str());
	completionList.saveToFile("completion");

	svcSleepThread(SECONDS_TO_NS(5));
	TodoList loadedCompletion;
	if (loadedCompletion.loadFromFile("completion"))
	{
		consoleClear();
		printf("TEST 4 Result - After load:\n%s\n", loadedCompletion.toString().c_str());
		printf("(Tasks 1 and 3 should be complete)\n");
	}

	// ========== All Tests Complete ==========
	svcSleepThread(SECONDS_TO_NS(5));
	consoleClear();
	printf("=== ALL TESTS COMPLETE ===\n");
	printf("\x1b[30;16HPress Start to exit.");

	// Main loop
	while (aptMainLoop())
	{
		// Scan all the inputs. This should be done once for each frame
		hidScanInput();

		// hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		// Wait for VBlank
		gspWaitForVBlank();
	}

	gfxExit();
	return 0;
}
