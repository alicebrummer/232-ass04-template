#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif
#include <stdlib.h>

// ============================================================
// Forward declarations — implemented in code.c
// ============================================================

typedef struct Node {
    int value;
    struct Node *nextPtr;
} Node;

void  initNode    (Node *nodePtr, int value);
Node* createNode  (int value);
void  destroyNode (Node **nodePtrPtr);
void  destroyList (Node **headPtrPtr);
int   addFirst    (Node **headPtrPtr, Node *newNodePtr);
int   addLast     (Node **headPtrPtr, Node *newNodePtr);
Node* detachFirst (Node **headPtrPtr);
Node* detachLast  (Node **headPtrPtr);
Node* detachValue (Node **headPtrPtr, int value);
int   deleteFirst (Node **headPtrPtr);
int   deleteLast  (Node **headPtrPtr);
int   deleteValue (Node **headPtrPtr, int value);
void  destroyList (Node **headPtrPtr);
int   printList   (Node *headPtr);
int   listLength  (Node *headPtr);


// ============================================================
//  UNIT TESTS
//
//  Rules:
//  - Use TEST_ASSERT_TRUE_MESSAGE for every assertion.
//  - Do NOT use TEST_ASSERT_EQUAL — it reveals expected values.
//  - Heap tests: use createNode / destroyList.
//  - Stack tests: declare Node variables on the stack.
//  - Do NOT modify function names or signatures.
// ============================================================


// ============================================================
// test_initNode_sets_value
//
// Declare a Node on the stack.
// Call initNode with a known value.
// Verify that the value field contains that value.
// ============================================================

void test_initNode_sets_value(void)
{
    Node a;
    initNode(&a, 5);
    TEST_ASSERT_EQUAL(5, a.value);
    
}


// ============================================================
// test_initNode_sets_next_null
//
// Declare a Node on the stack.
// Call initNode.
// Verify that nextPtr is NULL after the call.
// ============================================================

void test_initNode_sets_next_null(void)
{
    Node a;
    initNode(&a,5);
    TEST_ASSERT_NULL(a.nextPtr);
}


// ============================================================
// test_initNode_null_guard
//
// Call initNode with NULL as the nodePtr.
// Verify the program does not crash.
// ============================================================

void test_initNode_null_guard(void)
{
    // TODO
    initNode(NULL, 42);
    TEST_ASSERT_TRUE_MESSAGE(1 == 1,
        "Error: initNode must handle NULL without crashing.");
}


// ============================================================
// test_createNode_not_null
//
// Call createNode with a known value.
// Verify the returned pointer is NOT NULL.
// Remember to free memory after the test using destroyNode.
// ============================================================

void test_createNode_not_null(void)
{
    Node *nodePtr = createNode(42);
    TEST_ASSERT_TRUE_MESSAGE(nodePtr != NULL,
        "return a non-NULL pointer.");
    destroyNode(&nodePtr);
}


// ============================================================
// test_createNode_value
//
// Call createNode with a known value.
// Verify that the value field of the returned node
// contains the correct value.
// Remember to free memory after the test using destroyNode.
// ============================================================

void test_createNode_value(void)
{
    Node *nodePtr = createNode(42);
    TEST_ASSERT_TRUE_MESSAGE(nodePtr != NULL,
        "createNode non-NULL pointer.");

    int hasExpectedValue = nodePtr->value == 42;
    destroyNode(&nodePtr);
    TEST_ASSERT_TRUE_MESSAGE(hasExpectedValue,
        "createNode node's value.");
}


// ============================================================
// test_createNode_next_null
//
// Call createNode.
// Verify that nextPtr of the returned node is NULL.
// Remember to free memory after the test using destroyNode.
// ============================================================

void test_createNode_next_null(void)
{
    Node *nodePtr = createNode(42);
    TEST_ASSERT_TRUE_MESSAGE(nodePtr != NULL,
        "return a non-NULL pointer.");

    int nextIsNull = nodePtr->nextPtr == NULL;
    destroyNode(&nodePtr);
    TEST_ASSERT_TRUE_MESSAGE(nextIsNull,
        "nextPtr to NULL.");
}


// ============================================================
// test_destroyNode_sets_null
//
// Call createNode to allocate a node.
// Call destroyNode.
// Verify that the pointer is NULL after the call.
// ============================================================

void test_destroyNode_sets_null(void)
{
    Node *nodePtr = createNode(42);
    TEST_ASSERT_TRUE_MESSAGE(nodePtr != NULL,
        "non-NULL pointer.");

    destroyNode(&nodePtr);
    TEST_ASSERT_TRUE_MESSAGE(nodePtr == NULL,
        "destroyNode NULL.");
}


// ============================================================
// test_addFirst_empty_list
//
// Start with headPtr == NULL.
// Create a node and call addFirst.
// Verify that headPtr now points to the new node.
// Clean up with destroyList.
// ============================================================

void test_addFirst_empty_list(void)
{
    Node *headPtr = NULL;
    Node *newNodePtr = createNode(42);
    TEST_ASSERT_TRUE_MESSAGE(newNodePtr != NULL,
        " non-NULL pointer.");

    int result = addFirst(&headPtr, newNodePtr);
    int insertedAtHead = result == 0 && headPtr == newNodePtr;
    destroyList(&headPtr);
    TEST_ASSERT_TRUE_MESSAGE(insertedAtHead,
        "an empty list.");
}


// ============================================================
// test_addFirst_non_empty
//
// Add two nodes using addFirst.
// Verify that headPtr points to the SECOND node added
// (the most recently added node is at the front).
// Verify the first node is reachable via nextPtr.
// Clean up with destroyList.
// ============================================================

void test_addFirst_non_empty(void)
{
    Node *headPtr = NULL;
    Node *firstPtr = createNode(1);
    Node *secondPtr = createNode(2);
    TEST_ASSERT_TRUE_MESSAGE(firstPtr != NULL && secondPtr != NULL,
        "non-NULL pointers.");

    addFirst(&headPtr, firstPtr);
    addFirst(&headPtr, secondPtr);
    int nodesAreInOrder = headPtr == secondPtr &&
        secondPtr->nextPtr == firstPtr;

    destroyList(&headPtr);
    TEST_ASSERT_TRUE_MESSAGE(nodesAreInOrder,
        "newest node at the front.");
}


// ============================================================
// test_addFirst_null_headptr
//
// Call addFirst with NULL as headPtrPtr.
// Verify the function returns -1.
// ============================================================

void test_addFirst_null_headptr(void)
{
    Node *nodePtr = createNode(42);
    TEST_ASSERT_TRUE_MESSAGE(nodePtr != NULL,
        "non-NULL pointer.");

    int result = addFirst(NULL, nodePtr);
    destroyNode(&nodePtr);
    TEST_ASSERT_TRUE_MESSAGE(result == -1,
        "reject a NULL head pointer.");
}


// ============================================================
// test_addLast_empty_list
//
// Start with headPtr == NULL.
// Create a node and call addLast.
// Verify that headPtr points to the new node.
// Clean up with destroyList.
// ============================================================

void test_addLast_empty_list(void)
{
    Node *headPtr = NULL;
    Node *nodePtr = createNode(42);
    TEST_ASSERT_TRUE_MESSAGE(nodePtr != NULL,
        "createNode should return a non-NULL pointer.");

    int result = addLast(&headPtr, nodePtr);
    int insertedAtHead = result == 0 && headPtr == nodePtr;
    if (result == 0) {
        destroyList(&headPtr);
    } else {
        destroyNode(&nodePtr);
    }

    TEST_ASSERT_TRUE_MESSAGE(insertedAtHead,
        "addLast should set the head of an empty list.");
}


// ============================================================
// test_addLast_non_empty
//
// Add two nodes using addLast.
// Verify that headPtr points to the FIRST node added.
// Verify the second node is reachable via nextPtr.
// Verify the second node's nextPtr is NULL.
// Clean up with destroyList.
// ============================================================

void test_addLast_non_empty(void)
{
    Node *headPtr = NULL;
    Node *firstPtr = createNode(1);
    Node *secondPtr = createNode(2);
    addLast(&headPtr, firstPtr);
    addLast(&headPtr, secondPtr);

    int nodesAreInOrder = firstPtr != NULL && secondPtr != NULL &&
        headPtr == firstPtr && firstPtr->nextPtr == secondPtr &&
        secondPtr->nextPtr == NULL;
    destroyList(&headPtr);

    TEST_ASSERT_TRUE_MESSAGE(nodesAreInOrder,
        "should append");
}


// ============================================================
// test_addLast_null_guard
//
// Call addLast with NULL as headPtrPtr.
// Verify the function returns -1.
// ============================================================

void test_addLast_null_guard(void)
{
    Node *nodePtr = createNode(42);
    int result = addLast(NULL, nodePtr);
    destroyNode(&nodePtr);
    TEST_ASSERT_TRUE_MESSAGE(result == -1,
        "NULL head pointer.");
}


// ============================================================
// test_detachFirst_returns_node
//
// Build a stack chain: a -> b -> NULL
// Call detachFirst.
// Verify the returned pointer equals &a.
// ============================================================

void test_detachFirst_returns_node(void)
{
    Node a, b;
    initNode(&a, 1);
    initNode(&b, 2);
    a.nextPtr = &b;

    Node *headPtr = &a;
    Node *detachedPtr = detachFirst(&headPtr);
    TEST_ASSERT_TRUE_MESSAGE(detachedPtr == &a,
        "return the first node.");
}


// ============================================================
// test_detachFirst_updates_head
//
// Build a stack chain: a -> b -> NULL
// Call detachFirst.
// Verify that headPtr now points to b.
// ============================================================

void test_detachFirst_updates_head(void)
{
    Node a, b;
    initNode(&a, 1);
    initNode(&b, 2);
    a.nextPtr = &b;

    Node *headPtr = &a;
    detachFirst(&headPtr);
    TEST_ASSERT_TRUE_MESSAGE(headPtr == &b,
        "detachFirst should update the head to the second node.");
}


// ============================================================
// test_detachFirst_empty_list
//
// Call detachFirst on an empty list (headPtr == NULL).
// Verify the function returns NULL without crashing.
// ============================================================

void test_detachFirst_empty_list(void)
{
    Node *headPtr = NULL;
    Node *detachedPtr = detachFirst(&headPtr);
    TEST_ASSERT_TRUE_MESSAGE(detachedPtr == NULL,
        "an empty list.");
}


// ============================================================
// test_detachValue_found
//
// Build a stack chain: a(1) -> b(2) -> c(3) -> NULL
// Call detachValue for value 2 (middle node).
// Verify the returned pointer equals &b.
// Verify a->nextPtr now points to c.
// Verify b->nextPtr is NULL after detach.
// ============================================================

void test_detachValue_found(void)
{
    Node a, b, c;
    initNode(&a, 1);
    initNode(&b, 2);
    initNode(&c, 3);
    a.nextPtr = &b;
    b.nextPtr = &c;

    Node *headPtr = &a;
    Node *detachedPtr = detachValue(&headPtr, 2);
    TEST_ASSERT_TRUE_MESSAGE(detachedPtr == &b &&
        a.nextPtr == &c && b.nextPtr == NULL,
        "remove and return");
}


// ============================================================
// test_detachValue_head
//
// Build a stack chain: a(1) -> b(2) -> NULL
// Call detachValue for value 1 (head node).
// Verify the returned pointer equals &a.
// Verify headPtr now points to b.
// ============================================================

void test_detachValue_head(void)
{
    Node a, b;
    initNode(&a, 1);
    initNode(&b, 2);
    a.nextPtr = &b;

    Node *headPtr = &a;
    Node *detachedPtr = detachValue(&headPtr, 1);
    TEST_ASSERT_TRUE_MESSAGE(detachedPtr == &a && headPtr == &b,
        "detachValue should remove and return the head node.");
}


// ============================================================
// test_detachValue_not_found
//
// Build a stack chain: a(1) -> b(2) -> NULL
// Call detachValue for a value that does not exist (e.g. 99).
// Verify the function returns NULL.
// ============================================================

void test_detachValue_not_found(void)
{
    Node a, b;
    initNode(&a, 1);
    initNode(&b, 2);
    a.nextPtr = &b;

    Node *headPtr = &a;
    Node *detachedPtr = detachValue(&headPtr, 99);
    TEST_ASSERT_TRUE_MESSAGE(detachedPtr == NULL,
        "detachValue should return NULL for a non-existent value.");
}


// ============================================================
// test_deleteFirst_removes_node
//
// Create two heap nodes and build a list.
// Call deleteFirst.
// Verify the function returns 0.
// Verify headPtr now points to the second node.
// Clean up with destroyList.
// ============================================================

void test_deleteFirst_removes_node(void)
{
    Node *headPtr = createNode(1);
    Node *secondPtr = createNode(2);
    headPtr->nextPtr = secondPtr;

    int result = deleteFirst(&headPtr);
    int removedFirst = result == 0 && headPtr == secondPtr;
    destroyList(&headPtr);
    TEST_ASSERT_TRUE_MESSAGE(removedFirst,
        "remove the head node.");
}


// ============================================================
// test_deleteFirst_empty_list
//
// Call deleteFirst on an empty list.
// Verify the function returns -1 without crashing.
// ============================================================

void test_deleteFirst_empty_list(void)
{
    Node *headPtr = NULL;
    int result = deleteFirst(&headPtr);
    TEST_ASSERT_TRUE_MESSAGE(result == -1,
        "return -1");
}


// ============================================================
// test_deleteValue_found
//
// Create three heap nodes: 10 -> 20 -> 30
// Call deleteValue for 20.
// Verify the function returns 0.
// Verify listLength is now 2.
// Verify 20 is no longer in the list.
// Clean up with destroyList.
// ============================================================

void test_deleteValue_found(void)
{
    Node *headPtr = createNode(10);
    Node *middlePtr = createNode(20);
    Node *lastPtr = createNode(30);
    headPtr->nextPtr = middlePtr;
    middlePtr->nextPtr = lastPtr;

    int result = deleteValue(&headPtr, 20);
    int listIsCorrect = result == 0 && listLength(headPtr) == 2 &&
        headPtr->value == 10 && headPtr->nextPtr->value == 30;
    destroyList(&headPtr);
    TEST_ASSERT_TRUE_MESSAGE(listIsCorrect,
        "remove the matching node.");
}


// ============================================================
// test_deleteValue_not_found
//
// Create two heap nodes: 10 -> 20
// Call deleteValue for 99.
// Verify the function returns -1.
// Verify the list is unchanged (length still 2).
// Clean up with destroyList.
// ============================================================

void test_deleteValue_not_found(void)
{
    Node *headPtr = createNode(10);
    Node *secondPtr = createNode(20);
    headPtr->nextPtr = secondPtr;

    int result = deleteValue(&headPtr, 99);
    int listIsUnchanged = result == -1 && listLength(headPtr) == 2 &&
        headPtr->value == 10 && headPtr->nextPtr->value == 20;
    destroyList(&headPtr);
    TEST_ASSERT_TRUE_MESSAGE(listIsUnchanged,
        "return -1.");
}


// ============================================================
// test_destroyList_empties_list
//
// Create three heap nodes and build a list.
// Call destroyList.
// Verify headPtr is NULL after the call.
// ============================================================

void test_destroyList_empties_list(void)
{
    Node *headPtr = createNode(1);
    Node *secondPtr = createNode(2);
    Node *thirdPtr = createNode(3);
    headPtr->nextPtr = secondPtr;
    secondPtr->nextPtr = thirdPtr;

    destroyList(&headPtr);
    TEST_ASSERT_TRUE_MESSAGE(headPtr == NULL,
        "head pointer to NULL.");
}


// ============================================================
// test_listLength_empty
//
// Call listLength with NULL.
// Verify the function returns 0.
// ============================================================

void test_listLength_empty(void)
{
    int length = listLength(NULL);
    TEST_ASSERT_TRUE_MESSAGE(length == 0,
        "return zero");
}


// ============================================================
// test_listLength_three
//
// Create three heap nodes and build a list.
// Call listLength.
// Verify the function returns 3.
// Clean up with destroyList.
// ============================================================

void test_listLength_three(void)
{
    Node *headPtr = createNode(1);
    Node *secondPtr = createNode(2);
    Node *thirdPtr = createNode(3);
    headPtr->nextPtr = secondPtr;
    secondPtr->nextPtr = thirdPtr;

    int length = listLength(headPtr);
    destroyList(&headPtr);
    TEST_ASSERT_TRUE_MESSAGE(length == 3,
        "should count");
}


// ============================================================
// test_printList_empty
//
// Call printList with NULL.
// Verify the function returns -1 without crashing.
// ============================================================

void test_printList_empty(void)
{
    int result = printList(NULL);
    TEST_ASSERT_TRUE_MESSAGE(result == -1,
        "printList should return -1 for an empty list.");
}