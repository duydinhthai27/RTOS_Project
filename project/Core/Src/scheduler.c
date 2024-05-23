///*
// * scheduler.c
// *
// *  Created on: May 23, 2024
// *      Author: Duy Dinh
// */
//
//
//#include "scheduler.h"
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//static sTask SCH_tasks_G[SCH_MAX_TASKS];
//static uint8_t array_Of_Task_ID[SCH_MAX_TASKS];
//static uint32_t newTaskID = 0;
//static uint32_t rearQueue = 0;
//static uint32_t count_SCH_Update = 0;
//
//
//static uint32_t Get_New_Task_ID(void);
//static void TIMER_Init();
//
//
//void SCH_Init(void){
//	TIMER_Init();
//}
//
//void SCH_Update(void){
//	// Check if there is a task at this location
//	count_SCH_Update ++;
//	if (SCH_tasks_G[0].pTask && SCH_tasks_G[0].RunMe == 0) {
//		if(SCH_tasks_G[0].Delay > 0){
//			SCH_tasks_G[0].Delay = SCH_tasks_G[0].Delay - 1;
//		}
//		if (SCH_tasks_G[0].Delay == 0) {
//			SCH_tasks_G[0].RunMe = 1;
//		}
//	}
//}
//uint32_t SCH_Add_Task(void (* pFunction)(), uint32_t DELAY, uint32_t PERIOD){
//	uint8_t newTaskIndex = 0;
//	uint32_t sumDelay = 0;
//	uint32_t newDelay = 0;
//
//	for(newTaskIndex = 0; newTaskIndex < SCH_MAX_TASKS; newTaskIndex ++){
//		sumDelay = sumDelay + SCH_tasks_G[newTaskIndex].Delay;
//		if(sumDelay > DELAY){
//			newDelay = DELAY - (sumDelay - SCH_tasks_G[newTaskIndex].Delay);
//			SCH_tasks_G[newTaskIndex].Delay = sumDelay - DELAY;
//			for(uint8_t i = SCH_MAX_TASKS - 1; i > newTaskIndex; i --){
//				if(SCH_tasks_G[i - 1].pTask != 0)
//				{
//					SCH_tasks_G[i].pTask = SCH_tasks_G[i - 1].pTask;
//					SCH_tasks_G[i].Period = SCH_tasks_G[i - 1].Period;
//					SCH_tasks_G[i].Delay = SCH_tasks_G[i - 1].Delay;
//					SCH_tasks_G[i].RunMe = SCH_tasks_G[i - 1].RunMe;
//					SCH_tasks_G[i].TaskID = SCH_tasks_G[i - 1].TaskID;
//				}
//			}
//			SCH_tasks_G[newTaskIndex].pTask = pFunction;
//			SCH_tasks_G[newTaskIndex].Delay = newDelay;
//			SCH_tasks_G[newTaskIndex].Period = PERIOD;
//			if(SCH_tasks_G[newTaskIndex].Delay == 0){
//				SCH_tasks_G[newTaskIndex].RunMe = 1;
//			} else {
//				SCH_tasks_G[newTaskIndex].RunMe = 0;
//			}
//			SCH_tasks_G[newTaskIndex].TaskID = Get_New_Task_ID();
//			return SCH_tasks_G[newTaskIndex].TaskID;
//		} else {
//			if(SCH_tasks_G[newTaskIndex].pTask == 0x0000){
//				SCH_tasks_G[newTaskIndex].pTask = pFunction;
//				SCH_tasks_G[newTaskIndex].Delay = DELAY - sumDelay;
//				SCH_tasks_G[newTaskIndex].Period = PERIOD;
//				if(SCH_tasks_G[newTaskIndex].Delay == 0){
//					SCH_tasks_G[newTaskIndex].RunMe = 1;
//				} else {
//					SCH_tasks_G[newTaskIndex].RunMe = 0;
//				}
//				SCH_tasks_G[newTaskIndex].TaskID = Get_New_Task_ID();
//				return SCH_tasks_G[newTaskIndex].TaskID;
//			}
//		}
//	}
//	return SCH_tasks_G[newTaskIndex].TaskID;
//}
//
//
//uint8_t SCH_Delete_Task(uint32_t taskID){
//	uint8_t Return_code  = 0;
//	uint8_t taskIndex;
//	uint8_t j;
//	if(taskID != NO_TASK_ID){
//		for(taskIndex = 0; taskIndex < SCH_MAX_TASKS; taskIndex ++){
//			if(SCH_tasks_G[taskIndex].TaskID == taskID){
//				Return_code = 1;
//				if(taskIndex != 0 && taskIndex < SCH_MAX_TASKS - 1){
//					if(SCH_tasks_G[taskIndex+1].pTask != 0x0000){
//						SCH_tasks_G[taskIndex+1].Delay += SCH_tasks_G[taskIndex].Delay;
//					}
//				}
//
//				for( j = taskIndex; j < SCH_MAX_TASKS - 1; j ++){
//					SCH_tasks_G[j].pTask = SCH_tasks_G[j+1].pTask;
//					SCH_tasks_G[j].Period = SCH_tasks_G[j+1].Period;
//					SCH_tasks_G[j].Delay = SCH_tasks_G[j+1].Delay;
//					SCH_tasks_G[j].RunMe = SCH_tasks_G[j+1].RunMe;
//					SCH_tasks_G[j].TaskID = SCH_tasks_G[j+1].TaskID;
//				}
//				SCH_tasks_G[j].pTask = 0;
//				SCH_tasks_G[j].Period = 0;
//				SCH_tasks_G[j].Delay = 0;
//				SCH_tasks_G[j].RunMe = 0;
//				SCH_tasks_G[j].TaskID = 0;
//				return Return_code;
//			}
//		}
//	}
//	return Return_code; // return status
//}
//
//void SCH_Dispatch_Tasks(void){
//	if(SCH_tasks_G[0].RunMe > 0) {
//		(*SCH_tasks_G[0].pTask)(); // Run the task
//		SCH_tasks_G[0].RunMe = 0; // Reset / reduce RunMe flag
//		sTask temtask = SCH_tasks_G[0];
//		SCH_Delete_Task(temtask.TaskID);
//		if (temtask.Period != 0) {
//			SCH_Add_Task(temtask.pTask, temtask.Period, temtask.Period);
//		}
//	}
//}
//
//static uint32_t Get_New_Task_ID(void){
//	newTaskID++;
//	if(newTaskID == NO_TASK_ID){
//		newTaskID++;
//	}
//	return newTaskID;
//}
//
//#ifdef __cplusplus
//}
//#endif

#include "scheduler.h"
#include <stdlib.h>
#include <stdio.h>
sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;
typedef struct node
{
    sTasks task;
    struct node *next;
} node;

node SCH_tasksNode[SCH_MAX_TASKS];
node *head;

void SCH_Init(void)
{
    current_index_task = 0;
}

void handle_allocating_linked_list(node *newTaskNode)
{
    node *test = head;
    if (head == 0)
    {
        head = newTaskNode;
    }
    else
    {
        node *currentTaskNode;
        node *prevNode;
        currentTaskNode = head;
        // Exit condition is 1 when the newNodeTask find the location in the linkedlist by comparing with other tasks
        // Exit condition is 2 when the currentNodeTask reach end of linked list and cannot reevaluate any task afterward
        int exitCondition = 0;
        while (currentTaskNode->task.Delay <= newTaskNode->task.Delay)
        {
            newTaskNode->task.Delay -= currentTaskNode->task.Delay;
            if (currentTaskNode->next == 0)
            {
                exitCondition = 2;
                break;
            }
            prevNode = currentTaskNode;
            currentTaskNode = currentTaskNode->next;
            exitCondition = 1;
        }

        if (currentTaskNode == head && exitCondition == 1)
        {
            head = newTaskNode;
        }

        if (exitCondition == 1)
        {
            newTaskNode->next = currentTaskNode;
            prevNode->next = newTaskNode;
            currentTaskNode->task.Delay -= newTaskNode->task.Delay;
        }
        else
        {
            currentTaskNode->next = newTaskNode;
        }
    }
}

void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD)
{
    if (current_index_task < SCH_MAX_TASKS)
    {
        SCH_tasksNode[current_index_task].task.pTask = pFunction;
        SCH_tasksNode[current_index_task].task.Delay = DELAY / 10;
        SCH_tasksNode[current_index_task].task.Period = PERIOD / 10;
        SCH_tasksNode[current_index_task].task.RunMe = 0;

        SCH_tasksNode[current_index_task].task.TaskID = current_index_task;

        struct node *newTaskNodePointer = &SCH_tasksNode[current_index_task];
        handle_allocating_linked_list(newTaskNodePointer);
        current_index_task++;
    }
}

void SCH_Update(void)
{
    node *test = head;
    if (head->task.Delay > 0)
    {
        head->task.Delay--;
    }
    else
    {
        head->task.Delay = head->task.Period;
        head->task.RunMe = 1;
    }
}

void SCH_Add_And_Delete_Tasks(void)
{
    node *readdedTaskNode = head;
    head = head->next;
    readdedTaskNode->next = 0;
    handle_allocating_linked_list(readdedTaskNode);
}

void SCH_Dispatch_Tasks(void)
{
    node *currentNode = head;
    while(currentNode != 0 && (currentNode->task.Delay == 0 || currentNode->task.RunMe > 0)) {
        if (currentNode->task.Delay == 0)
        {
            currentNode->task.Delay = currentNode->task.Period;
            currentNode->task.RunMe = 1;
        }

        if (currentNode->task.RunMe > 0)
        {
            currentNode->task.RunMe--;
            (*currentNode->task.pTask)();
            SCH_Add_And_Delete_Tasks();
        }
        currentNode = currentNode->next;
    }
}
