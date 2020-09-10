#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <memory.h>

#define TRUE  1
#define FALSE 0

#define LIMITSEL1 80
#define LIMITSEL2 100

/* ����ڵ�ṹ */
typedef struct Node 
{
    void* data;
    struct Node* next;
}Node;

/* �������� */
Node* listCreate() 
{
    Node* ptr = (Node*)malloc(sizeof(Node));
    ptr->data = NULL;
    ptr->next = NULL;
    return ptr;
}

/* �������Ԫ�� */
void listAppend(Node* head, void* data) 
{
    Node* p = head;
    while (p->next != NULL) 
	{
        p = p->next;
    }

    Node* newPtr = listCreate();
    newPtr->data = data;
    p->next = newPtr;
}

/* ��ȡ����Ԫ�صĸ��� */
int listCount(Node* head) 
{
    int count = 0;
    Node* tPtr = head;
    while (tPtr->next != NULL) 
	{
        tPtr = tPtr->next;
        count++;
    }
    return count;
}

/* ͨ��������ȡ�����е�Ԫ�� */
void* listItemAt(Node* head, int index) //indexָԪ���������е���� 
{
    if (index < 0) 
		return NULL;
    if (index > listCount(head)) 
		return NULL;

    Node* tPtr = head->next;
    while (index--) 
	{
        tPtr = tPtr->next;
    }
    return tPtr->data;
}

/* ��������Ԫ�� */
void listInsert(Node* head, void* data, int n) 
{
    Node* newPtr = listCreate();
    newPtr->data = data;

    int count = listCount(head);
    if (n == 0) 
	{
        newPtr->next = head->next;
        head->next = newPtr;
    } 
	else if (n <= count) 
	{
        Node* pre = head;
        for (int i = 0; i < n; i++) 
		{
            pre = pre->next;
        }
        newPtr->next = pre->next;
        pre->next = newPtr;
    } 
	else 
	{
        Node* tail = head;
        while (tail->next) 
		{
            tail = tail->next;
        }
        tail->next = newPtr;
    }
}

/* �������Ƴ�ĳ��Ԫ�� */
void listRemoveByData(Node* head, void* data) 
{
    Node* tPtr = head;
    while (tPtr != NULL && tPtr->next != NULL
        && tPtr->next->data != data) 
		{
        	tPtr = tPtr->next;
    	}
    if (tPtr && tPtr->next && tPtr->next->data == data) 
	{
        Node* ptr = tPtr->next;
        tPtr->next = tPtr->next->next;
        free(ptr);
    }
}

/* �������Ƴ�ĳ��Ԫ�� */
void listRemoveByIndex(Node* head, int index) 
{
    listRemoveByData(head, listItemAt(head, index));
}

typedef int(*SORTFUN)(void* a, void* b);
/* �������� */
void listSort(Node* head, SORTFUN fun) 
{
    int count = listCount(head);
    void** pArr = (void**)malloc(sizeof(void*) * count);
    // ������ת�������������
    for (int i = 0; i < count; i++) 
	{
        pArr[i] = listItemAt(head, i);
    }
    // ����
    for (int i = 0; i < count; i++) 
	{
        for (int j = i + 1; j < count; j++) 
		{
            if (fun(pArr[i], pArr[j]) == TRUE) 
			{
                void* t = pArr[i];
                pArr[i] = pArr[j];
                pArr[j] = t;
            }
        }
    }
    // �������
    for (int i = 0; i < count; i++) 
	{
        listRemoveByData(head, pArr[i]);
    }
    // ������õ�������ӵ�����
    for (int i = 0; i < count; i++) 
	{
        listAppend(head, pArr[i]);
    }
    free(pArr);
}

/* �ͷ����� */
void listFree(Node* head) 
{
    Node* tPtr = head;
    while (tPtr) 
	{
        Node* nextPtr = tPtr->next;
        free(tPtr->data);
        free(tPtr);
        tPtr = nextPtr;
    }
}

/* ѧ���ṹ */
typedef struct Student 
{
    char number[20];
    char faculty[20];
    char science[20];
    char name[20];
    char sex[10];
    char phone[20];
    char email[20];
    char password[20];
}Student;

/* ��ʦ�ṹ */
typedef struct Teacher 
{
    char number[20];
    char faculty[20];
    char name[20];
    char email[20];
    char password[20];
}Teacher;

/* �Ͽ�ʱ��� */
char g_timeSegments[11][20] = 
{
    "",
    "8:00-8:50",
    "9:00-9:50",
    "10:00-10:50",
    "11:00-11:50",
    "13:30-14:20",
    "14:30-15:20",
    "15:30-16:20",
    "16:30-17:20",
    "18:30-19:20",
    "19:30-20:20",
};

/* �γ̽ṹ */
typedef struct Course 
{
    char number[20];
    char name[20];
    int credit;
    int hours;
    char nature[20];
    char teacher[20];
    char location[20];
    int timeSegments;
    int limit;
    char introduction[100];
    char teachingMaterial[100];
}Course;

/* ѡ����Ϣ�ṹ */
typedef struct CourseSel 
{
    char studentNumber[20];
    char CourseNumber[20];
}CourseSel;

/* ����ѧ���ṹ */
Student* createStudent() 
{
    Student* ptr = (Student*)malloc(sizeof(Student));
    memset(ptr, 0, sizeof(Student));
    return ptr;
}

/* ����ѧ���ṹ */
Student* cloneStudent(Student* stu) 
{
    Student* nstu = createStudent();
    /*char number[20];
    char faculty[20];
    char science[20];
    char name[20];
    char sex[10];
    char phone[20];
    char email[20];
    char password[20];*/
    strcpy(nstu->number, stu->number);
    strcpy(nstu->faculty, stu->faculty);
    strcpy(nstu->science, stu->science);
    strcpy(nstu->name, stu->name);
    strcpy(nstu->sex, stu->sex);
    strcpy(nstu->phone, stu->phone);
    strcpy(nstu->email, stu->email);
    strcpy(nstu->password, stu->password);
    return nstu;
}

/* ������ʦ�ṹ */
Teacher* createTeacher() 
{
    Teacher* ptr = (Teacher*)malloc(sizeof(Teacher));
    memset(ptr, 0, sizeof(Teacher));
    return ptr;
}

/* ���ƽ�ʦ�ṹ */
Teacher* cloneTeacher(Teacher* tea) 
{
    Teacher* ntea = createTeacher();
    /*char number[20];
    char faculty[20];
    char name[20];
    char email[20];
    char password[20];*/
    strcpy(ntea->number, tea->number);
    strcpy(ntea->faculty, tea->faculty);
    strcpy(ntea->name, tea->name);
    strcpy(ntea->email, tea->email);
    strcpy(ntea->password, tea->password);
    return ntea;
}

/* �����γ� */
Course* createCourse() 
{
    Course* ptr = (Course*)malloc(sizeof(Course));
    memset(ptr, 0, sizeof(Course));
    return ptr;
}

/* ��¡�γ� */
Course* cloneCourse(Course* cr) 
{
    Course* ncr = createCourse();
    /*char number[20];
    char name[20];
    int credit;
    int hours;
    char nature[20];
    char teacher[20];
    char location[20];
    char timeScope[50];
    int timeSegments;
    int limit;
    char introduction[100];
    char teachingMaterial[100];*/

    strcpy(ncr->number, cr->number);
    strcpy(ncr->name, cr->name);
    strcpy(ncr->nature, cr->nature);
    strcpy(ncr->teacher, cr->teacher);
    strcpy(ncr->location, cr->location);
    strcpy(ncr->introduction, cr->introduction);
    strcpy(ncr->teachingMaterial, cr->teachingMaterial);

    ncr->credit = cr->credit;
    ncr->hours = cr->hours;
    ncr->timeSegments = cr->timeSegments;
    ncr->limit = cr->limit;
    return ncr;
}

/* ����ѡ�νṹ */
CourseSel* createCourseSel() 
{
    CourseSel* ptr = (CourseSel*)malloc(sizeof(CourseSel));
    memset(ptr, 0, sizeof(CourseSel));
    return ptr;
}

/* ��¡ѡ�νṹ */
CourseSel* cloneCourseSel(CourseSel* crs) 
{
    /*char studentNumber[20];
    char CourseNumber[20];*/

    CourseSel* ncrs = createCourseSel();
    strcpy(ncrs->studentNumber, crs->studentNumber);
    strcpy(ncrs->CourseNumber, crs->CourseNumber);
    return ncrs;
}

/* ȫ�ֱ������� */
enum MyEnum { T_NOT, T_STARTSEL, T_ENDSEL, T_STARTCLASS };
int g_courseSelStatus = T_NOT;
Node* g_studentHead;
Node* g_teacherHead;
Node* g_courseHead;
Node* g_courseSelHead;
Node* g_courseHistoryHead;
Node* g_courseSelHistoryHead;
Student* g_curStudent;// 
Teacher* g_curTeacher;
enum { T_NONE, T_STUDENT, T_TEACHER };
int g_userType = T_NONE;

/* ��ʼ��ȫ������ */
void initLists() 
{
    g_studentHead = listCreate();
    g_teacherHead = listCreate();
    g_courseHead = listCreate();
    g_courseSelHead = listCreate();
    g_courseHistoryHead = listCreate();
    g_courseSelHistoryHead = listCreate();
}

/* �ͷ�ȫ������ */
void freeLists() 
{
    listFree(g_studentHead); g_studentHead = NULL;
    listFree(g_teacherHead); g_teacherHead = NULL;
    listFree(g_courseHead); g_courseHead = NULL;
    listFree(g_courseSelHead); g_courseSelHead = NULL;
}

typedef void(*FileOpt)(FILE* fp, Node* head);
/* ��ȡ�ļ� */
int readFile(const char* fileName, Node* head, FileOpt callback) 
{
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) 
	{ 
		return FALSE; 
	}
    callback(fp, head);
    fclose(fp);
    return TRUE;
}

/* д���ļ� */
int writeFile(const char* fileName, Node* head, FileOpt callback) 
{
    FILE* fp = fopen(fileName, "w");
    if (fp == NULL) 
	{ 
		return FALSE; 
	}
    callback(fp, head);
    fclose(fp);
    return TRUE;
}

/* ѧ�����ݶ�ȡ */
void studentDataRead(FILE* fp, Node* head) 
{
    char number[20];
    char faculty[20];
    char science[20];
    char name[20];
    char sex[10];
    char phone[20];
    char email[20];
    char password[20];

    while (fscanf(fp, "%s %s %s %s %s %s %s %s\n", number, faculty,
        science, name, sex, phone, email, password) != EOF) 
		{
        	Student* stu = createStudent();
        	strcpy(stu->number, number);
        	strcpy(stu->faculty, faculty);
        	strcpy(stu->science, science);
        	strcpy(stu->name, name);
        	strcpy(stu->sex, sex);
        	strcpy(stu->phone, phone);
        	strcpy(stu->email, email);
        	strcpy(stu->password, password);
        	listAppend(g_studentHead, stu);
    	}
}

/* ѧ������д�� */
void studentDataWrite(FILE* fp, Node* head) 
{
    for (int i = 0; i < listCount(g_studentHead); i++) 
	{ 
        Student* stu = (Student*)listItemAt(g_studentHead, i);
        fprintf(fp, "%s %s %s %s %s %s %s %s\n", stu->number, stu->faculty,
            stu->science, stu->name, stu->sex, stu->phone, stu->email, stu->password);
    }
}

/* ����ѧ������ */
void loadStudentData(const char* name, Node* head) 
{
    readFile(name, head, studentDataRead);
}

/* ����ѧ������ */
void saveStudentData(const char* name, Node* head)
{
    writeFile(name, head, studentDataWrite);
}

/* ��ʦ���ݶ�ȡ */
void teacherDataRead(FILE* fp, Node* head) 
{
    char number[20];
    char faculty[20];
    char name[20];
    char email[20];
    char password[20];

    while (fscanf(fp, "%s %s %s %s %s\n", number,
        faculty, name, email, password) != EOF) 
		{
        	Teacher* ptr = createTeacher();
        	strcpy(ptr->number, number);
        	strcpy(ptr->faculty, faculty);
        	strcpy(ptr->name, name);
        	strcpy(ptr->email, email);
        	strcpy(ptr->password, password);
        	listAppend(head, ptr);
    	}
}

/* ��ʦ����д�� */
void teacherDataWrite(FILE* fp, Node* head) 
{
    for (int i = 0; i < listCount(g_teacherHead); i++) 
	{
        Teacher* ptr = (Teacher*)listItemAt(head, i);
        fprintf(fp, "%s %s %s %s %s\n", ptr->number,
            ptr->faculty, ptr->name, ptr->email, ptr->password);
    }
}

/* �����ʦ���� */
void loadTeacherData(const char* name, Node* head) 
{ 
    readFile(name, head, teacherDataRead);
}

/* �����ʦ���� */
void saveTeacherData(const char* name, Node* head) 
{
    writeFile(name, head, teacherDataWrite);
}

/* �γ����ݶ�ȡ */
void courseDataRead(FILE* fp, Node* head) 
{
    char number[20];
    char name[20];
    int credit;
    int hours;
    char nature[20];
    char teacher[20];
    char location[20];
    int timeSegments;
    int limit;
    char introduction[100];
    char teachingMaterial[100];

    while (fscanf(fp, "%s %s %s %s %s %s %s %d %d %d %d\n", number, name,
        nature, teacher, location, introduction, teachingMaterial,
        &credit, &hours, &timeSegments, &limit) != EOF) 
		{
        	Course* ptr = createCourse();
        	strcpy(ptr->number, number);
        	strcpy(ptr->name, name);
        	strcpy(ptr->nature, nature);
        	strcpy(ptr->teacher, teacher);
        	strcpy(ptr->location, location);
        	strcpy(ptr->introduction, introduction);
        	strcpy(ptr->teachingMaterial, teachingMaterial);
        	ptr->credit = credit;
        	ptr->hours = hours;
        	ptr->timeSegments = timeSegments;
        	ptr->limit = limit;
        	listAppend(head, ptr);
    	}
}

/* �γ�����д�� */
void courseDataWrite(FILE* fp, Node* head) 
{
    for (int i = 0; i < listCount(g_courseHead); i++) 
	{
        Course* ptr = (Course*)listItemAt(g_courseHead, i);
        fprintf(fp, "%s %s %s %s %s %s %s %d %d %d %d\n", ptr->number, ptr->name,
            ptr->nature, ptr->teacher, ptr->location, ptr->introduction,
            ptr->teachingMaterial, ptr->credit, ptr->hours, ptr->timeSegments, ptr->limit);
    }
}

/* ����γ����� */
void loadCourseData(const char* name, Node* head) 
{
    readFile(name, head, courseDataRead);
}

/* ����γ����� */
void saveCourseData(const char* name, Node* head) 
{
    writeFile(name, head, courseDataWrite);
}

/* ѡ�����ݶ�ȡ */
void courseSelDataRead(FILE* fp, Node* head) 
{
    char studentNumber[20];
    char CourseNumber[20];

    while (fscanf(fp, "%s %s\n", studentNumber, CourseNumber) != EOF) 
	{
        CourseSel* ptr = createCourseSel();
        strcpy(ptr->studentNumber, studentNumber);
        strcpy(ptr->CourseNumber, CourseNumber);
        listAppend(head, ptr);
    }
}

/* ѡ���������� */
void courseSelDataWrite(FILE* fp, Node* head) 
{
    for (int i = 0; i < listCount(head); i++) 
	{
        CourseSel* ptr = (CourseSel*)listItemAt(head, i);
        fprintf(fp, "%s %s\n", ptr->studentNumber, ptr->CourseNumber);
    }
}

/* ����ѡ������ */
void loadCourseSelData(const char* name, Node* head) 
{
    readFile(name, head, courseSelDataRead);
}

/* ����ѡ������ */
void saveCourseSelData(const char* name, Node* head) 
{
    writeFile(name, head, courseSelDataWrite);
}

// global
/* ����ȫ��ѧ������ */
void saveGlobalStudentData()
{
    saveStudentData("student.txt", g_studentHead);
}

/* ����ȫ��ѧ������ */
void loadGlobalStudentData() 
{
    loadStudentData("student.txt", g_studentHead);
}

/* ����ȫ�ֽ�ʦ���� */
void saveGlobalTeacherData() 
{
    saveTeacherData("teacher.txt", g_teacherHead);
}

/* ����ȫ�ֽ�ʦ���� */
void loadGlobalTeacherData() 
{
    loadTeacherData("teacher.txt", g_teacherHead);
}

/* ����ȫ�ֿγ����� */
void saveGlobalCourseData() 
{
    saveCourseData("course.txt", g_courseHead);
}

/* ����ȫ�ֿγ����� */
void loadGlobalCourseData() 
{
    loadCourseData("course.txt", g_courseHead);
}

/* ����ȫ�ֿγ����� */
void saveGlobalCourseSelData() 
{
    saveCourseSelData("courseSel.txt", g_courseSelHead);
}

/* ����ȫ�ֿγ����� */
void loadGlobalCourseSelData() 
{
    loadCourseSelData("courseSel.txt", g_courseSelHead);
}

/* ����ȫ����ʷ�γ����� */
void loadGlobalCourseHistoryData() 
{
    loadCourseData("courseHistory.txt", g_courseHistoryHead);
}

/* ����ȫ����ʷѡ������ */
void loadGlobalCourseSelHistoryData() 
{
    loadCourseSelData("courseSelHistory.txt", g_courseSelHistoryHead);
}

// student
/* ����ѧ�� */
Student* findStudent(const char* number) 
{
    for (int i = 0; i < listCount(g_studentHead); i++) 
	{
        Student* ptr = (Student*)listItemAt(g_studentHead, i);
        if (strcmp(ptr->number, number) == 0)
            return ptr;
    }
    return NULL;
}

/* ѧ���˺�����У�� */
int studentCheck(const char* number, const char* password) 
{
    Student* ptr = findStudent(number);
    if (ptr == NULL) 
		return FALSE;
    return strcmp(ptr->password, password) == 0;
}

// teacher
/* ���ҽ�ʦ */
Teacher* findTeacher(const char* number) 
{
    for (int i = 0; i < listCount(g_teacherHead); i++) 
	{
        Teacher* ptr = (Teacher*)listItemAt(g_teacherHead, i);
        if (strcmp(ptr->number, number) == 0)
            return ptr;
    }
    return NULL;
}

/* ���ҽ�ʦ */
Teacher* findTeacherByName(const char* name) 
{
    for (int i = 0; i < listCount(g_teacherHead); i++) 
	{
        Teacher* ptr = (Teacher*)listItemAt(g_teacherHead, i);
        if (strcmp(ptr->name, name) == 0)
            return ptr;
    }
    return NULL;
}

/* ��ʦ�˺�����У�� */
int teacherCheck(const char* number, const char* password) 
{
    Teacher* ptr = findTeacher(number);
    if (ptr == NULL) 
		return FALSE;
    return strcmp(ptr->password, password) == 0;
}

// course
/* ���ҿγ� */
Course* findCourseByName(const char* name) 
{
    for (int i = 0; i < listCount(g_courseHead); i++) 
	{
        Course* ptr = (Course*)listItemAt(g_courseHead, i);
        if (strcmp(ptr->name, name) == 0) 
			return ptr;
    }
    return NULL;
}

/* ���ҿγ� */
Course* findCourseByNameByCurTeacher(const char* name) 
{
    Course* cr = findCourseByName(name);
    if (cr == NULL) 
		return NULL;
    if (strcmp(cr->teacher, g_curTeacher->name) != 0) 
		return NULL;
    return cr;
}

/* ���ҿγ� */
Course* findCourseByNumber(const char* number) 
{
    for (int i = 0; i < listCount(g_courseHead); i++) 
	{
        Course* ptr = (Course*)listItemAt(g_courseHead, i);
        if (strcmp(ptr->number, number) == 0) 
			return ptr;
    }
    return NULL;
}

/* ��ȡ�γ��б� */
Node* getCoursesByCurTeacher() 
{
    Node* list = listCreate();
    for (int i = 0; i < listCount(g_courseHead); i++) 
	{
        Course* ptr = (Course*)listItemAt(g_courseHead, i);
        if (strcmp(ptr->teacher, g_curTeacher->name) == 0) 
		{
            listAppend(list, cloneCourse(ptr));
        }
    }
    return list;
}

/* �Ƿ��Ѿ��пγ� */
int hasCourseByNumber(const char* number) 
{
    return findCourseByNumber(number) != NULL;
}

/* �Ƿ��Ѿ��пγ� */
int hasCourseByName(const char* name) 
{
    return findCourseByName(name) != NULL;
}

/* ��ȡ��ʦ�γ��б� */
Node* getTeacherCourses(const char* name) 
{
    Node* list = listCreate();
    for (int i = 0; i < listCount(g_courseHead); i++) 
	{
        Course* ptr = (Course*)listItemAt(g_courseHead, i);
        if (strcmp(ptr->teacher, name) == 0) 
			listAppend(list, cloneCourse(ptr));
    }
    return list;
}

/* ��ȡ��ʦ��ʷ�γ��б� */
Node* getTeacherHistoryCourses(const char* name) 
{
    Node* list = listCreate();
    for (int i = 0; i < listCount(g_courseHistoryHead); i++) 
	{
        Course* ptr = (Course*)listItemAt(g_courseHistoryHead, i);
        if (strcmp(ptr->teacher, name) == 0) 
			listAppend(list, cloneCourse(ptr));
    }
    return list;
}

/* ��ȡԺϵ�γ��б� */
Node* getCourseByFaculty(const char* faculty) 
{
    Node* list = listCreate();
    for (int i = 0; i < listCount(g_courseHead); i++) 
	{
        Course* ptr = (Course*)listItemAt(g_courseHead, i);
        // find taecher
        Teacher* tea = findTeacherByName(ptr->teacher);
        if (strcmp(tea->faculty, faculty) == 0) 
			listAppend(list, cloneCourse(ptr));
    }
    return list;
}

/* ��ȡ��ʦ�γ����� */
int getTeacherCourseCount(const char* name) 
{
    Node* list = getTeacherCourses(name);
    int count = listCount(list);
    listFree(list);
    return count;
}

/* ��ȡѡ�иÿγ̵����� */
int getCourseSelectCount(const char* name) 
{
    Course* cr = findCourseByName(name);
    if (cr == NULL) 
		return 0;
    int count = 0;
    for (int i = 0; i < listCount(g_courseSelHead); i++) 
	{
        CourseSel* crs = (CourseSel*)listItemAt(g_courseSelHead, i);
        if (strcmp(cr->number, crs->CourseNumber) == 0) 
			count++;
    }
    return count;
}

/* ��ȡ��ǰѧ��ѡ��Ŀγ��� */
int getSelectCourseCountByCurStu() 
{
    int count = 0;
    for (int i = 0; i < listCount(g_courseSelHead); i++) 
	{
        CourseSel* crs = (CourseSel*)listItemAt(g_courseSelHead, i);
        if (strcmp(crs->studentNumber, g_curStudent->number) == 0) 
			count++;
    }
    return count;
}

/* ��ȡ��ǰѧ���Ŀγ��б� */
Node* getCoursesByCurStu() 
{
    Node* list = listCreate();
    for (int i = 0; i < listCount(g_courseSelHead); i++) 
	{
        CourseSel* crs = (CourseSel*)listItemAt(g_courseSelHead, i);
        if (strcmp(crs->studentNumber, g_curStudent->number) == 0) 
		{
            Course* cr = findCourseByNumber(crs->CourseNumber);
            if (cr) 
				listAppend(list, cloneCourse(cr));
        }
    }
    return list;
}

/* ��ȡ��ǰѧ������ʷ�γ��б� */
Node* getHistoryCoursesByCurStu() 
{
    Node* list = listCreate();
    for (int i = 0; i < listCount(g_courseSelHistoryHead); i++) 
	{
        CourseSel* crs = (CourseSel*)listItemAt(g_courseSelHistoryHead, i);
        if (strcmp(crs->studentNumber, g_curStudent->number) == 0) 
		{
            Course* cr = findCourseByNumber(crs->CourseNumber);
            if (cr) 
			listAppend(list, cloneCourse(cr));
        }
    }
    return list;
}

/* ��ȡ�γ� */
Course* getCourseByCurStu(const char* name) 
{
    for (int i = 0; i < listCount(g_courseSelHead); i++) 
	{
        CourseSel* crs = (CourseSel*)listItemAt(g_courseSelHead, i);
        if (strcmp(crs->studentNumber, g_curStudent->number) == 0) 
		{
            Course* cr = findCourseByNumber(crs->CourseNumber);
            if (cr == NULL) 
				continue;
            if (strcmp(cr->name, name) == 0) 
				return cr;
        }
    }
    return NULL;
}

/* ͨ����ʱ����γ� */
int sortCourseByHoursFun(void* a, void* b) 
{
    return ((Course*)a)->hours < ((Course*)b)->hours;
}

/* ͨ��ѧ����������γ� */
int sortCourseBySelectCountFun(void* a, void* b) 
{
    return getCourseSelectCount(((Course*)a)->name)
        < getCourseSelectCount(((Course*)b)->name);
}

/* ͨ����ʱ����γ� */
void sortCourseByHours() 
{
    listSort(g_courseHead, sortCourseByHoursFun);
}

/* ͨ��ѧ����������γ� */
void sortCourseBySelectCount() 
{
    listSort(g_courseHead, sortCourseBySelectCountFun);
}

// courseSel
/* ��ȡ��ǰѧ����ѡ������ */
int getSelectedCountByCurStu() 
{
    int count = 0;
    for (int i = 0; i < listCount(g_courseSelHead); i++) 
	{
        CourseSel* crs = (CourseSel*)listItemAt(g_courseSelHead, i);
        if (strcmp(crs->studentNumber, g_curStudent->number) == 0) 
		count++;
    }
    return count;
}

/* �ڵ�ǰѧ���õĵ�ѡ���б���ͨ���κŲ���һ��ѡ�� */
CourseSel* findOneCourseSelByNumberByCurStu(const char* number) 
{
    for (int i = 0; i < listCount(g_courseSelHead); i++) 
	{
        CourseSel* crs = (CourseSel*)listItemAt(g_courseSelHead, i);
        if (strcmp(crs->studentNumber, g_curStudent->number) == 0
            && strcmp(crs->CourseNumber, number) == 0)
            return crs;
    }
    return NULL;
}

/* ͨ��ѡ������ȡѧ���б� */
Node* getStudentsByCourseName(const char* name) 
{
    Node* list = listCreate();
    for (int i = 0; i < listCount(g_courseSelHead); i++) 
	{
        CourseSel* crs = (CourseSel*)listItemAt(g_courseSelHead, i);
        Course* cr = findCourseByNumber(crs->CourseNumber);
        if (strcmp(cr->name, name) == 0) 
		{
            Student* stu = findStudent(crs->studentNumber);
            if (stu) 
			listAppend(list, cloneStudent(stu));
        }
    }
    return list;
}

// print
/* ��ӡѧ����ͷ */
void printStudentHead() 
{
    printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n",
        "ѧ��", "Ժϵ", "רҵ", "����", "�Ա�", "�绰", "����");
}

/* ��ӡѧ������ */
void printStudentLine(Student* stu) 
{
    printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n", stu->number,
        stu->faculty, stu->science, stu->name, stu->sex, stu->phone, stu->email);
}

/* ��ӡ��ʦ��ͷ */
void printTeacherHead() 
{
    printf("%-15s%-15s%-15s%-15s\n", "����", "Ժϵ", "����", "����");
}

/* ��ӡ��ʦ���� */
void printTeacherLine(Teacher* tea) 
{
    printf("%-15s%-15s%-15s%-15s\n", tea->number, tea->faculty, tea->name, tea->email);
}

/* ��ӡ�γ̱�ͷ */
void printCourseHead() 
{
    // ̫��, ��ӡ����
    /*char number[20];
    char name[20];
    int credit;
    int hours;
    char nature[20];
    char teacher[20];
    char location[20];
    char timeScope[50];
    int timeSegments;
    int limit;
    char introduction[100];
    char teachingMaterial[100];*/
}

/* ��ӡ�γ����� */
void printCourseLine(Course* cr) 
{
    printf("\n");
    printf("�γ̱��:%s\n", cr->number);
    printf("�γ�����:%s\n", cr->name);
    printf("�γ�ѧ��:%d\n", cr->credit);
    printf("�γ�ѧʱ:%d\n", cr->hours);
    printf("�γ�����:%s\n", cr->nature);
    printf("�ον�ʦ:%s\n", cr->teacher);
    printf("�Ͽεص�:%s\n", cr->location);
    printf("��������:%d\n", cr->limit);
    printf("�γ̼��:%s\n", cr->introduction);
    printf("�̲���Ϣ:%s\n", cr->teachingMaterial);
    printf("\n");
}

/* ��ӡ�γ����ݲ���ӡѡ������ */
void printCourseLineAppendSelectCount(Course* cr) 
{
    printf("\n");
    printf("�γ̱��:%s\n", cr->number);
    printf("�γ�����:%s\n", cr->name);
    printf("�γ�ѧ��:%d\n", cr->credit);
    printf("�γ�ѧʱ:%d\n", cr->hours);
    printf("�γ�����:%s\n", cr->nature);
    printf("�ον�ʦ:%s\n", cr->teacher);
    printf("�Ͽεص�:%s\n", cr->location);
    printf("��������:%d\n", cr->limit);
    printf("�γ̼��:%s\n", cr->introduction);
    printf("�̲���Ϣ:%s\n", cr->teachingMaterial);
    printf("��ǰѡ������:%d\n", getCourseSelectCount(cr->name));
    printf("\n");
}

/* ��ӡѡ�α�ͷ */
void printfCourseSelHead() 
{
    /*char studentNumber[20];
    char CourseNumber[20];*/
    printf("%-15s%-15s\n", "����", "�γ�");
}

/* ��ӡѡ������ */
void printfCourseSelLine(CourseSel* crs) 
{
    Student* stu = findStudent(crs->studentNumber);
    Course* cr = findCourseByNumber(crs->CourseNumber);
    if (stu == NULL || cr == NULL) 
		return;
    printf("%-15s%-15s\n", stu->name, cr->name);
}

/* ���ַ���str�����ַ�c */
int findStr(const char* str, char c) 
{
    int i = 0;
    while (*str) 
	{
        if (*str == c)
            return i;
        i++;
        str++;
    }
    return -1;
}

// data check
char g_buffer[100];
/* �ַ������Ƿ��Ƿ������� */
int isIntStr(const char* str) 
{
    while (*str) 
	{
        if (*str < '0' || *str > '9') 
		{
            return FALSE;
        }
        str++;
    }
    return TRUE;
}

/* ��ȡ����Ϊlen�������ַ��� */
char* getIntStr(int len) 
{
    while (TRUE) 
	{
        scanf("%s", g_buffer);
        if (isIntStr(g_buffer) && (len == 0 || strlen(g_buffer) == len)) 
		{
            return g_buffer;
        }
        if (len > 0)
            printf("�������,������һ������Ϊ%d������:", len);
        else
            printf("�������,������һ������:");
    }
    return NULL;
}

/* ��ȡѧ��ѧ�Ż��߽�ʦ��� */
char* getNumber() 
{
    return getIntStr(10);
}

/* ��ȡ�绰���� */
char* getPhoneNumber() 
{
    return getIntStr(11);
}

/* ��ȡ�κ� */
char* getCourseNumber() 
{
    return getIntStr(6);
}

/* ��ȡ�������� */
int getLimit() 
{
    int n;
    while (TRUE) 
	{
        scanf("%d", &n);
        if (n != LIMITSEL1 && n != LIMITSEL2) 
		{
            printf("�������,����������(%d or %d):", LIMITSEL1, LIMITSEL2);
            continue;
        }
        break;
    }
    getchar();
    return n;
}

/* ��ȡ�Ͽ�λ�� */
char* getLocation() 
{
	return getIntStr(10);
}

/* ��ȡ��ʱ */
int getHours() 
{
    int n;
    while (TRUE) 
	{
        scanf("%d", &n);
        if (n <= 0) 
		{
            printf("������>0������:");
            continue;
        }
        break;
    }
    return n;
}

/* ��ȡ�γ����� */
char* getNature() 
{
    while (TRUE) 
	{
        scanf("%s", g_buffer);
        if (strcmp(g_buffer, "����") != 0 && strcmp(g_buffer, "ѡ��") != 0) 
			{
            	printf("������(���� or ѡ��):");
            	continue;
        	}
        break;
    }
    return g_buffer;
}

/* ��ȡ�Ͽ�ʱ��� */
int getTimeSegment() 
{
    printf("\n��ѡ���Ͽ�ʱ���\n");
    for (int i = 1; i <= 10; i++) 
	{
        printf("%d.%s\n", i, g_timeSegments[i]);
    }
    int n;
    while (TRUE) 
	{
        printf("\n������:");
        scanf("%d", &n);
        if (n < 1 || n >10) 
		{
            printf("������[1,10]��Χ��ֵ");
            continue;
        }
        break;
    }
    return n;
}

/* ��ȡ���� */
char* getEmail() 
{
    static char str[100];
    while (TRUE) 
	{
        scanf("%s", str);

        int pos1 = findStr(str, '@');
        int pos2 = findStr(str, '.');

        if (pos1 <= 0 || pos2 >= strlen(str) - 1 || pos1 > pos2) 
		{
            printf("�����ʽ����,����������(*****@***.***):");
            continue;
        } 
		break;
    }
    return str;
}

/* ��ȡѧ�� */
int getCredit() 
{
    int n;
    while (TRUE)
	{
        scanf("%d", &n);
        if (n < 1 || n>4) 
		{
            printf("�����뷶Χ[1,4]��ֵ:");
            continue;
        }
        break;
    }
    return n;
}

/* ѧ����¼ */
int loginStudent() 
{
    char number[20];
    char passwor[20];
    system("cls");
    printf("ѧ����¼\n");
    printf("�������˺�:");
    scanf("%s", number);
    printf("����������:");
    scanf("%s", passwor);
    if (studentCheck(number, passwor)) 
	{
        g_userType = T_STUDENT;
        g_curStudent = findStudent(number);
        return TRUE;
    } 
	else 
	{
        printf("��Ϣ����,����������.\n");
        system("pause");
        return FALSE;
    }
}

/* ��ʦ��¼ */
int loginTeacher() 
{
    char number[20];
    char passwor[20];
    system("cls");
    printf("��ʦ��¼\n");
    printf("�������˺�:");
    scanf("%s", number);
    printf("����������:");
    scanf("%s", passwor);
    if (teacherCheck(number, passwor)) 
	{
        g_userType = T_STUDENT;
        g_curTeacher = findTeacher(number);
        return TRUE;
    } 
	else 
	{
        printf("��Ϣ����,����������.\n");
        system("pause");
        return FALSE;
    }
}

/* ѧ��ѡ�� */
void stduentSelectCourse() 
{
    /*ѧ��ѡ�θ���ϵͳ�ṩ�Ŀγ̽����������ѡ���
    ��Ȥ�Ŀγ̡�
    ͬһ��ѧ�������Ż���ſγ�ʱ�䲻�ܳ�ͻ
    �涨һ��ѧ��һ��ѧ�������ѡ3�ſ�
    ÿ�ſγ�ѡ���������ܳ�����������*/

    if (g_courseSelStatus != T_STARTSEL) 
	{
        printf("δ����ѡ��\n");
        system("pause");
        return;
    }

    if (getSelectCourseCountByCurStu() >= 3) 
	{
        printf("ѡ���Ѿ��ﵽ����\n");
        system("pause");
        return;
    }

    printf("������γ���:");
    char name[50]; scanf("%s", name);
    Course* cr = findCourseByName(name);
    if (cr == NULL) 
	{
        printf("�γ̲�����\n");
        system("pause");
        return;
    }

    if (getCourseSelectCount(cr->name) >= cr->limit) 
	{
        printf("ѡ�������Ѿ��ﵽ����\n");
        system("pause");
        return;
    }

    Node* list = getCoursesByCurStu();
    for (int i = 0; i < listCount(list); i++) 
	{
        Course* ptr = (Course*)listItemAt(list, i);
        if (ptr->timeSegments == cr->timeSegments) 
		{
            listFree(list);
            printf("�Ͽ�ʱ���ͻ\n");
            system("pause");
            return;
        }

        if (strcmp(ptr->name, cr->name) == 0) 
		{
            listFree(list);
            printf("�ÿγ��Ѿ�ѡ�����\n");
            system("pause");
            return;
        }
    }

    CourseSel* sel = createCourseSel();
    strcpy(sel->studentNumber, g_curStudent->number);
    strcpy(sel->CourseNumber, cr->number);
    listAppend(g_courseSelHead, sel);
    listFree(list);
    saveGlobalCourseSelData();
    printf("���ѡ�γɹ�\n");
    system("pause");
    return;
}

/* ���ݿγ�����ѯ */
void courseQueryByName() 
{
    printf("������γ���:");
    char name[50]; scanf("%s", name);
    Course* cr = findCourseByName(name);
    if (cr == NULL) 
	{
        printf("û���ҵ��ÿγ�\n");
        system("pause");
        return;
    }

    printCourseLine(cr);
    system("pause");
}

/* ���ݿ���ѧԺ��ѯ */
void courseQueryByFaculty() 
{
    printf("������ѧԺ����:");
    char name[50]; scanf("%s", name);
    Node* list = getCourseByFaculty(name);
    if (listCount(list) == 0) 
	{
        listFree(list);
        printf("��ϢΪ��\n");
        system("pause");
        return;
    }

    for (int i = 0; i < listCount(list); i++) 
	{
        printCourseLine((Course*)listItemAt(list, i));
    }

    system("pause");
}

/* ���ݿ������������пγ� */
void courseQueryByHourse() 
{
    sortCourseByHours();
    for (int i = 0; i < listCount(g_courseHead); i++) 
	{
        printCourseLine((Course*)listItemAt(g_courseHead, i));
    }
    system("pause");
}

/* ����ѡ�������������пγ� */
void courseQueryBySelectCount() 
{
    sortCourseBySelectCount();
    for (int i = 0; i < listCount(g_courseHead); i++) 
	{
        printCourseLineAppendSelectCount((Course*)listItemAt(g_courseHead, i));
    }
    system("pause");
}

/* ��ѯ�γ� */
void studentQueryCourse() 
{
    /*��ѯ�γ�
    ���ݿγ�����ѯ
    ���ݿ���ѧԺ��ѯ
    ���ݿ������������пγ�
    ����ѡ�������������пγ� */
    while (TRUE) 
	{
        system("cls");
        printf("\t|\t��ѯ�γ�\t|\n\n");
        printf("\t|\t1.���ݿγ�����ѯ\t|\n\n");
        printf("\t|\t2.���ݿ���ѧԺ��ѯ\t|\n\n");
        printf("\t|\t3.���ݿ���������γ�\t|\n\n");
        printf("\t|\t4.����ѡ����������γ�\t|\n\n");
        printf("\t|\t0.������һ���˵�\t|\n\n"); 
        printf(" �����빦�����:");

        int sel; 
		scanf("%d", &sel);
        switch (sel) 
		{
        	case 0:
            	return;
        	case 1:
            	courseQueryByName();
            	break;
        	case 2:
            	courseQueryByFaculty();
            	break;
        	case 3:
            	courseQueryByHourse();
            	break;
        	case 4:
            	courseQueryBySelectCount();
            	break;
        }
    }
}

void queryCourseSelHistoryResult() 
{
    Node* list = getHistoryCoursesByCurStu();
    if (listCount(list) == 0) 
	{
        listFree(list);
        printf("��ϢΪ��\n");
        system("pause");
        return;
    }

    printCourseHead();
    for (int i = 0; i < listCount(list); i++) 
	{
        Course* cr = (Course*)listItemAt(list, i);
        printCourseLine(cr);
    }
    listFree(list);
    system("pause");
}

void queryCourseSelResult() 
{
    Node* list = getCoursesByCurStu();
    if (listCount(list) == 0) 
	{
        listFree(list);
        printf("��ϢΪ��\n");
        system("pause");
        return;
    }

    printCourseHead();
    for (int i = 0; i < listCount(list); i++) 
	{
        Course* cr = (Course*)listItemAt(list, i);
        printCourseLine(cr);
    }
    listFree(list);
    system("pause");
}

/* ��ѯѡ�ν�� */
void querySelectedCourse() 
{
    /*��ѯѡ�ν��
    �鿴ѧ������ѡ���Ŀγ� */ 
    while (TRUE) 
	{
        system("cls");
        printf("\t|\tѡ�ν����ѯ\t|\n\n");
        printf("\t|\t1.��ѯѡ�ν��\t|\n\n");
        printf("\t|\t2.��ѯ��ʷѡ��\t|\n\n");
        printf("\t|\t0.������һ���˵�\t|\n\n"); 
        printf(" �����빦�����:");

        int sel; 
		scanf("%d", &sel);
        switch (sel) 
		{
        	case 0:
            	return;
        	case 1:
            	queryCourseSelResult();
            	break;
        	case 2:
            	queryCourseSelHistoryResult();
            	break;
        }
    }
    
    
    //getHistoryCoursesByCurStu
    
}

/* ɾ��ѡ�� */
void deleteSelectedCourse() 
{
    /* ɾ��ѡ�ν��
    ��δ����ǰѧ������ɾ���Լ���ѡ�ν��*/

    if (g_courseSelStatus == T_STARTCLASS) 
	{
        printf("�γ��Ѿ���ʼ,�޷�����ɾ������\n");
        system("pause");
        return;
    }

    printf("������Ҫɾ����ѡ����:");
    char name[50]; 
	scanf("%s", name);
    Course* cr = getCourseByCurStu(name);
    if (cr == NULL) 
	{
        printf("��û��ѡ��ÿγ�\n");
        system("pause");
        return;
    }

    CourseSel* sel = findOneCourseSelByNumberByCurStu(cr->number);
    listRemoveByData(g_courseSelHead, sel);
    saveGlobalCourseSelData();
    printf("ɾ���ɹ�\n");
    system("pause");
}

/* ѧ���޸����� */
void studentModifyPassword() 
{
    printf("����������:");
    char password[50];
    scanf("%s", password);
    strcpy(g_curStudent->password, password);
    saveGlobalStudentData();
    printf("�޸ĳɹ�\n");
    system("pause");
}

/* ѧ���޸����� */
void studentModifyEmail() 
{
    printf("����������:");
    strcpy(g_curStudent->email, getEmail());
    saveGlobalStudentData();
    printf("�޸ĳɹ�\n");
    system("pause");
}

/* ѧ���޸ĵ绰 */
void studentModifyPhone() 
{
    printf("������绰:");
    strcpy(g_curStudent->phone, getPhoneNumber());
    saveGlobalStudentData();
    printf("�޸ĳɹ�\n");
    system("pause");
}

/* ѧ����Ϣ���� */
void studentInfomanage() 
{
    /*����Ϣ����
    �绰�����롢�����޸�*/
    while (TRUE) 
	{
        system("cls");
        printf("\t|\t������Ϣ����\t|\n\n");
        printf("\t|\t1.�޸�����\t|\n\n");
        printf("\t|\t2.�޸�����\t|\n\n");
        printf("\t|\t3.�޸ĵ绰\t|\n\n");
        printf("\t|\t4.�鿴������Ϣ\t|\n\n");
        printf("\t|\t0.������һ���˵�\t|\n\n"); 
        printf(" �����빦�����:");
        int sel; 
		scanf("%d", &sel);
        switch (sel) 
		{
        	case 0:
            	return;
        	case 1:
            	studentModifyPassword();
            	break;
        	case 2:
            	studentModifyEmail();
            	break;
        	case 3:
            	studentModifyPhone();
        	default:
            	break;
        }
    }
}

/* ѧ���˵� */
void studentLoop() 
{
    while (TRUE) 
	{
        system("cls");
        printf("\t|\tѧ���˵�\t|\n\n");
        printf("\t|\t1.ѧ��ѡ��\t|\n\n");
        printf("\t|\t2.��ѯ�γ�\t|\n\n");
        printf("\t|\t3.��ѯѡ�ν��\t|\n\n");
        printf("\t|\t4.ɾ��ѡ�ν��\t|\n\n");
		printf("\t|\t5.������Ϣ����\t|\n\n"); 
        printf("\t|\t0.�˳���¼\t|\n\n"); 
        printf(" �����빦�����:");

        int sel; 
		scanf("%d", &sel);
        switch (sel) 
		{
        	case 0:
            	return;
        	case 1:
            	stduentSelectCourse();
            	break;
        	case 2:
            	studentQueryCourse();
            	break;
        	case 3:
            	querySelectedCourse();
            	break;
        	case 4:
            	deleteSelectedCourse();
            	break;
        	case 5:
            	studentInfomanage();
            	break;
        }
    }
}

/* ��ѯ��ʦ�Լ�������Ŀγ̵�ѡ����� */
void querySelfCourseSituation() 
{
    /* ��ѯ��ʦ�Լ�������Ŀγ̵�ѡ�����
    (ѡ�������Ϳγ���ϸ��Ϣ)*/

    Node* list = getCoursesByCurTeacher();
    if (listCount(list) == 0) 
	{
        printf("��ϢΪ��\n");
        system("pause");
        return;
    }

    printCourseHead();
    for (int i = 0; i < listCount(list); i++) 
	{
        printCourseLineAppendSelectCount((Course*)listItemAt(list, i));
    }
    system("pause");
    return;
}

/* ����ѧ��������ѯ */
void queryCourseSelStudentInfoByStudentName() 
{
    /* ����ѧ��������ѯ */
    printf("������γ���\n");
    char courseName[50]; scanf("%s", courseName);
    printf("������ѧ������\n");
    char studentName[50]; scanf("%s", studentName);

    Node* list = getStudentsByCourseName(courseName);
    for (int i = 0; i < listCount(list); i++) 
	{
        Student* stu = (Student*)listItemAt(list, i);
        if (strcmp(stu->name, studentName) == 0) 
		{
            printStudentHead();
            printStudentLine(stu);
            listFree(list);
            system("pause");
            return;
        }
    }

    listFree(list);
    printf("û���ҵ���ѧ������Ϣ\n");
    system("pause");
    return;
}

/* ���ݿγ����Ʋ�ѯ */
void queryCourseSelStudentInfoByCourseName() 
{
    /* ���ݿγ����Ʋ�ѯ */
    printf("������γ���\n");
    char name[50]; scanf("%s", name);
    Node* list = getStudentsByCourseName(name);
    if (listCount(list) == 0) 
	{
        listFree(list);
        printf("��ϢΪ��\n");
        system("pause");
        return;
    }

    printStudentHead();
    for (int i = 0; i < listCount(list); i++) 
	{
        Student* stu = (Student*)listItemAt(list, i);
        printStudentLine(stu);
    }
    listFree(list);
    system("pause");
}

/* ��ѯѡ��ĳ�ſγ̵�ѧ����Ϣ */
void queryCourseSelStudentInfo() 
{
    /* ��ѯѡ��ĳ�ſγ̵�ѧ����Ϣ
    (����ѧ��������/�Ϳγ����ƣ�*/
    while (TRUE) 
	{
        system("cls");
        printf("\t|\t��ѯ�γ̵�ѧ����Ϣ\t|\n\n");
        printf("\t|\t1.����ѧ��������ѯ\t|\n\n");
        printf("\t|\t2.���ݿγ����Ʋ�ѯ\t|\n\n"); 
        printf("\t|\t0.������һ���˵�\t|\n\n"); 
        printf(" �����빦�����:");

        int sel; 
		scanf("%d", &sel);
        switch (sel) 
		{
        	case 0:
            	return;
        	case 1:
            	queryCourseSelStudentInfoByStudentName();
            	break;
        	case 2:
            	queryCourseSelStudentInfoByCourseName();
            	break;
        	default:
            	break;
        }

    }
}

/* �鿴ѡ����� */
void queryCourseSituation() 
{
    while (TRUE) 
	{
        system("cls");
        printf("\t|\t�鿴ѡ�����\t|\n\n");
        printf("\t|\t1.��ѯ��ѧ�ڿ���γ�ѡ�����\t|\n\n");
        printf("\t|\t2.��ѯ�γ̵�ѧ����Ϣ\t|\n\n");
        printf("\t|\t0.������һ���˵�\t|\n\n"); 
        printf(" �����빦�����:");

        int sel; 
		scanf("%d", &sel);
        switch (sel) 
		{
        	case 0:
            	return;
        	case 1:
            	querySelfCourseSituation();
            	break;
        	case 2:
            	queryCourseSelStudentInfo();
            	break;
        	default:
            	break;
        }
    }
}

/* ѡ�ν��������ĳ�ſγ̵�ѡ����������3��ɾ�� */
void deleteSubstandardCourseSel() 
{
    /* ѡ�ν��������ĳ�ſγ̵�ѡ����������3��ɾ��
    �ÿγ�����ѡ��ÿγ̵�ѧ��ѡ����Ϣɾ��  */
    if (g_courseSelStatus <= T_STARTSEL) 
	{
        printf("ѡ��δ����\n");
        system("pause");
        return;
    }
    // �����γ�
    for (int i = 0; i < listCount(g_courseHead); i++) 
	{
        Course* cr = (Course*)listItemAt(g_courseHead, i);
        // �������С��3
        if (getCourseSelectCount(cr->name) < 3) 
		{
            // ����ѡ�μ�¼
            for (int j = 0; j < listCount(g_courseSelHead); j++) 
			{
                CourseSel* crs = (CourseSel*)listItemAt(g_courseSelHead, i);
                if (strcmp(cr->number, crs->CourseNumber) == 0) 
				{
                    listRemoveByIndex(g_courseSelHead, j--);
                }
            }
            listRemoveByIndex(g_courseHead, i--);
        }
    }
    saveGlobalCourseData();
    saveGlobalCourseSelData();
    printf("ɾ���ɹ�\n");
    system("pause");
}

/* ��ѯ��ʦ�Լ�����Ŀγ��� */
void statisticsSelfCourseCount() 
{
    system("cls");
    int count = getTeacherCourseCount(g_curTeacher->name);
    printf("��������%d���γ�.\n", count);
    system("pause");
}

/* ��ѡ�������������п�����Ŀγ� */
void statisticsCourseSortBySelectCount() 
{
    sortCourseBySelectCount();
    Node* list = getCoursesByCurTeacher();
    if (listCount(list) == 0) 
	{
        listFree(list);
        printf("��û�п���γ�\n");
        system("pause");
        return;
    }

    printCourseHead();
    for (int i = 0; i < listCount(list); i++) 
	{
        Course* cr = (Course*)listItemAt(list, i);
        printCourseLineAppendSelectCount(cr);
    }
    listFree(list);
    system("pause");
}

/* ͳ��ѡ����Ϣ */
void courseSelStatistics() 
{
    while (TRUE) 
	{
        system("cls");
        printf("\t|\tͳ��ѡ����Ϣ\t|\n\n");
        printf("1.ͳ�ƽ�ʦ�Լ�������Ŀγ���Ŀ\n");
        printf("2.��ѡ�������������п�����Ŀγ�\n");
        printf("0.������һ���˵�\n");
        printf("�����빦�����:");

        int sel; 
		scanf("%d", &sel);
        switch (sel) 
		{
        	case 0:
            	return;
        	case 1:
            	statisticsSelfCourseCount();
            	break;
        	case 2:
            	statisticsCourseSortBySelectCount();
            	break;
        }
    }
}

/* ѡ�ι��� */
void courseSelManage() 
{
    while (TRUE) 
	{
        system("cls");
        printf("\t|\tѡ�ι���\t|\n\n");
        printf("\t|\t1.�鿴ѡ�����\t|\n\n");
        printf("\t|\t2.ɾ��ѡ��\t|\n\n");
        printf("\t|\t3.ͳ��ѡ����Ϣ\t|\n\n");
        printf("\t|\t0.������һ���˵�\t|\n\n"); 
        printf(" �����빦�����:");

        int sel; 
		scanf("%d", &sel);
        switch (sel) 
		{
        	case 0:
            	return;
        	case 1:
            	queryCourseSituation();
            	break;
        	case 2:
            	deleteSubstandardCourseSel();
            	break;
        	case 3:
            	courseSelStatistics();
            	break;
        	default:
            	break;
        }
    }
}

/* ��ѯ���п���Ŀγ� */
void printAllCourse() 
{
    /* ��ѯ���п���Ŀγ� */
    // printCourseHead();
    Node* list = getTeacherCourses(g_curTeacher->name);
    if (listCount(list) == 0) 
	{
        listFree(list);
        printf("δ��ѯ���ÿγ���Ϣ\n");
        system("pause");
        return;
    }

    for (int i = 0; i < listCount(list); i++) 
	{
        Course* cr = (Course*)listItemAt(list, i);
        printCourseLine(cr);
    }

    listFree(list);
    system("pause");
}

/* ��ѯ������ʷ����Ŀγ� */
void printAllHistoryCourse() 
{
    /* ��ѯ���п���Ŀγ� */
    // printCourseHead();
    Node* list = getTeacherHistoryCourses(g_curTeacher->name);
    if (listCount(list) == 0) 
	{
        listFree(list);
        printf("δ��ѯ���ÿγ���Ϣ\n");
        system("pause");
        return;
    }

    for (int i = 0; i < listCount(list); i++) 
	{
        Course* cr = (Course*)listItemAt(list, i);
        printCourseLine(cr);
    }

    listFree(list);
    system("pause");
}

/* ���ݿγ�����ѯ�γ� */
void queryCourseByName() 
{
    /* ���ݿγ�����ѯ�γ� */
    char name[50];
    printf("������γ�����:");
    scanf("%s", name);

    Course* cr = findCourseByNameByCurTeacher(name);
    if (cr == NULL) 
	{
        printf("��δ������ſγ�\n");
        system("pause");
        return;
    }

    printCourseLine(cr);
    system("pause");
}

/* �γ̲�ѯ */
void queryCourse() 
{
    while (TRUE) 
	{
        system("cls");
        printf("\t|\t�γ̲�ѯ\t|\n\n");
        printf("\t|\t1.��ѯ��ѧ�ڿ���Ŀγ�\t|\n\n");
        printf("\t|\t2.��ѯ��ʷ����Ŀγ�\t|\n\n");
        printf("\t|\t3.���ݿγ�����ѯ�γ�\t|\n\n"); 
        printf("\t|\t0.������һ���˵�\t|\n\n"); 
        printf(" �����빦�����:");

        int sel; 
		scanf("%d", &sel);
        switch (sel) 
		{
        	case 0:
            	return;
        	case 1:
            	printAllCourse();
            	break;
       		case 2:
            	printAllHistoryCourse();
            	break;
        	case 3:
            	queryCourseByName();
            	break;
        	default:
            	break;
        }
    }
}

/* ����γ���Ϣ */
Course* inputCourse() 
{
    Course* course = createCourse();
    printf("������γ̱��:");
    strcpy(course->number, getNumber());
    printf("�γ�����:");
    scanf("%s", course->name);
    printf("ѧ��(1-4):");
    course->credit = getCredit();
    printf("ѧʱ:");
    course->hours = getHours();
    printf("�γ�����:");
    strcpy(course->nature, getNature());
    printf("��ѡ���Ͽ�ʱ���:");
    course->timeSegments = getTimeSegment();
    printf("�������Ͽεص�:");
    strcpy(course->location, getLocation());
    printf("��������:");
    course->limit = getLimit();
    printf("�γ̼��:");
    gets(course->introduction);
    printf("�̲���Ϣ:");
    gets(course->teachingMaterial);
    strcpy(course->teacher, g_curTeacher->name);
    return course;
}

/* ��ӿγ� */
void addCourse() 
{
    /*
    ��ӿγ�
    ͬһ����ʦ���Ͽ�ʱ�䲻�ܳ�ͻ
    �γ������γ̺Ų����ظ�
    ͬһ����ʦһѧ�����ֻ�ܿ�����ѡ��
    �γ̵���������������ѡ��80�˺�100��
    */

    Course* course = inputCourse();

    if (hasCourseByName(course->name) == TRUE) 
	{
        free(course);
        printf("�γ������ظ�\n");
        system("pause");
        return;
    }

    if (hasCourseByNumber(course->name) == TRUE) 
	{
        free(course);
        printf("�γ̺ų��ظ�\n");
        system("pause");
        return;
    }

    if (getTeacherCourseCount(g_curTeacher->name) >= 2) 
	{
        free(course);
        printf("��ʦһѧ�����ֻ�ܿ�����ѡ��\n");
        system("pause");
        return;
    }

    listAppend(g_courseHead, course);
    saveCourseData("course.txt", g_courseHead);
    printf("��ӿγ̳ɹ�\n");
    system("pause");
}

/* �޸Ŀγ� */
void modifyCourse() 
{
    /*�޸Ŀγ�
    ��һ�ſγ���δ��ѧ��ѡ��ʱ�����޸�ѡ�ν̲ġ��γ̼�顢��������
    ��ʼѡ�κ�����޸�����������*/

    printf("������γ�����:");
    char name[50]; scanf("%s", name);
    Course* cr = findCourseByNameByCurTeacher(name);
    if (cr == NULL) 
	{
        printf("û���ҵ��ÿγ�\n");
        system("pause");
        return;
    }

    int selectCount = getCourseSelectCount(name);
    if (selectCount == 0) 
	{
        printf("������̲�:");
        scanf("%s", cr->teachingMaterial);
        printf("������γ̼��:");
        scanf("%s", cr->introduction);
        printf("��������������:");
        scanf("%d", &cr->limit);
    } 
	else 
	{
        printf("��������������:");
        int limit; scanf("%d", &limit);
        if (limit < selectCount) 
		{
            printf("���������С�ڵ�ǰ�Ѿ�ѡ��ÿγ̵�ѧ������\n");
            printf("�޸�ʧ��\n");
            system("pause");
            return;
        }
        cr->limit = limit;
        printf("�޸ĳɹ�\n");
        system("pause");
        return;
    }
}

/* ɾ���γ� */
void deleteCourse() 
{
    /* ɾ���γ�
    δ��ʼѡ�γ̿��Խ���ɾ������ */

    if (g_courseSelStatus != T_NOT) 
	{
        printf("ѡ���Ѿ���ʼ,�޷�����ɾ������.\n");
        system("pause");
        return;
    }

    char name[50];
    printf("������Ҫɾ��ѡ�ε�����:");
    scanf("%s", name);

    Course* cr = findCourseByNameByCurTeacher(name);
    if (cr == NULL || strcmp(cr->teacher, g_curTeacher->name) != 0) 
	{
        printf("û���ҵ����ſγ�.\n");
        system("pause");
        return;
    }

    listRemoveByData(g_courseHead, cr);
    printf("ɾ���ɹ�\n");
}

/* �γ̹��� */
void courseManage() 
{
    while (TRUE) 
	{
        system("cls");
        printf("\t|\t �γ̹���\t|\n\n");
        printf("\t|\t1.�γ̲�ѯ\t|\n\n");
        printf("\t|\t2.��ӿγ�\t|\n\n");
        printf("\t|\t3.�޸Ŀγ�\t|\n\n");
        printf("\t|\t4.ɾ���γ�\t|\n\n"); 
        printf("\t|\t0.������һ���˵�\t|\n\n"); 
        printf(" �����빦�����:");

        int sel; 
		scanf("%d", &sel);
        switch (sel) 
		{
        	case 0:
            	return;
        	case 1:
            	queryCourse();
            	break;
        	case 2:
            	addCourse();
            	break;
        	case 3:
            	modifyCourse();
            	break;
        	case 4:
            	deleteCourse();
            	break;
        	default:
            	break;
        }
    }
}

/* ��ʦ�޸����� */
void teacherModifyEmail() 
{
    printf("����������:");
    strcpy(g_curTeacher->email, getEmail());
    saveGlobalTeacherData();
    printf("�޸ĳɹ�\n");
    system("pause");
}

/* ��ʦ�޸����� */
void teacherModifyPassword() 
{
    printf("����������:");
    char password[50];
    scanf("%s", password);
    strcpy(g_curTeacher->password, password);
    saveGlobalTeacherData();
    printf("�޸ĳɹ�\n");
    system("pause");
}

/* ��ʦ������Ϣ���� */
void teacherInfoManage() 
{
    while (TRUE) 
	{
        system("cls");
        printf("\t|\t ������Ϣ����\t|\n\n");
        printf("\t|\t1.�޸�����\t|\n\n");
        printf("\t|\t2.�޸�����\t|\n\n");
        printf("\t|\t3.�鿴������Ϣ\t|\n\n");
        printf("\t|\t0.������һ���˵�\t|\n\n");
        printf(" �����빦�����:");

        int sel; 
		scanf("%d", &sel);
        switch (sel) 
		{
        	case 0:
            	return;
        	case 1:
            	teacherModifyPassword();
            	break;
        	case 2:
            	teacherModifyEmail();
            	break;
            case 3:
            	//teacherPrintInformation();
            	break;
        	default:
            	break;
        }
    }
}

/* ��ʦ�˵� */
void teacherLoop() 
{
    while (TRUE) 
	{
        system("cls");
        printf("\t|\t ��ʦ�˵�\t|\n\n");
        printf("\t|\t1.ѡ�ι���\t|\n\n");
        printf("\t|\t2.�γ̹���\t|\n\n");
        printf("\t|\t3.������Ϣ����\t|\n\n");
        printf("\t|\t0.�˳���¼\t|\n\n");
        printf(" �����빦�����:");

        int sel; 
		scanf("%d", &sel);
        switch (sel) 
		{
        	case 0:
            	return;
        	case 1:
            	courseSelManage();
            	break;
        	case 2:
            	courseManage();
            	break;
        	case 3:
            	teacherInfoManage();
            	break;
        	default:
            	break;
        }
    }
}

/* ��¼�˳����� */
void loginOut() 
{
    g_curStudent = NULL;
    g_curTeacher = NULL;
    g_userType = T_NONE;
}

/* �����ļ����� */
void loadFileDatas() 
{
    loadGlobalStudentData();
    loadGlobalTeacherData();
    loadGlobalCourseData();
    loadGlobalCourseSelData();
    loadGlobalCourseHistoryData();
    loadGlobalCourseSelHistoryData();
}

/* ѡ��״̬ */
void courseSelSet() 
{
    system("cls");
    printf("\t|\t ѡ��״̬\t|\n\n");
    printf("\t|\t1.δ��ʼѡ��\t|\n\n");
    printf("\t|\t2.��ʼѡ��\t|\n\n");
    printf("\t|\t3.����ѡ��\t|\n\n");
    printf("\t|\t4.����\t|\n\n");
    printf("\t|\t0.�˳�ϵͳ\t|\t\n\n");
    printf(" �����빦�����:");

    int sel; 
	scanf("%d", &sel);
    switch (sel) 
	{
    	case 1:
        	g_courseSelStatus = T_NOT;
        	break;
    	case 2:
        	g_courseSelStatus = T_STARTSEL;
        	break;
    	case 3:
        	g_courseSelStatus = T_ENDSEL;
        	break;
    	case 4:
        	g_courseSelStatus = T_STARTCLASS;
        	break;
    	default:
        	printf("����Ƿ�\n");
        	system("pause");
        	return;
    }
    printf("�趨�ɹ�\n");
    system("pause");
    return;
}

/* ��ʼ�� */
void init() 
{
    initLists();
    loadFileDatas();
}

int main() 
{
    init();
    while (TRUE) 
	{
        system("cls");
        printf("************��ӭʹ��ѧ��ѡ��ϵͳ*************\n\n");
        printf("\t|\t �û���¼\t|\n\n");
        printf("\t|\t1.ѧ����¼\t|\n\n");
        printf("\t|\t2.��ʦ��¼\t|\n\n");
        printf("\t|\t3.ѡ��״̬\t|\n\n");
        printf("\t|\t0.�˳�ϵͳ\t|\n\n");
        printf(" �����빦�����:");

        int sel; 
		scanf("%d", &sel);
        switch (sel) 
		{
        	case 0:
            	return 0; 
        	case 1:
            	if (loginStudent() == TRUE) 
				{
                	studentLoop();
                	loginOut();
            	}
            break;
        case 2:
            if (loginTeacher() == TRUE) 
			{
                teacherLoop();
                loginOut();
            }
            break;
        case 3:
            courseSelSet();
            break;
        }
    }

    return 0;
}
