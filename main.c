#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <memory.h>

#define TRUE  1
#define FALSE 0

#define LIMITSEL1 80
#define LIMITSEL2 100

/* 链表节点结构 */
typedef struct Node 
{
    void* data;
    struct Node* next;
}Node;

/* 创建链表 */
Node* listCreate() 
{
    Node* ptr = (Node*)malloc(sizeof(Node));
    ptr->data = NULL;
    ptr->next = NULL;
    return ptr;
}

/* 链表添加元素 */
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

/* 获取链表元素的个数 */
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

/* 通过索引获取链表中的元素 */
void* listItemAt(Node* head, int index) //index指元素在链表中的序号 
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

/* 插入链表元素 */
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

/* 从链表移除某个元素 */
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

/* 从链表移除某个元素 */
void listRemoveByIndex(Node* head, int index) 
{
    listRemoveByData(head, listItemAt(head, index));
}

typedef int(*SORTFUN)(void* a, void* b);
/* 链表排序 */
void listSort(Node* head, SORTFUN fun) 
{
    int count = listCount(head);
    void** pArr = (void**)malloc(sizeof(void*) * count);
    // 将链表转到数组进行排序
    for (int i = 0; i < count; i++) 
	{
        pArr[i] = listItemAt(head, i);
    }
    // 排序
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
    // 清空链表
    for (int i = 0; i < count; i++) 
	{
        listRemoveByData(head, pArr[i]);
    }
    // 将排序好的数组添加到链表
    for (int i = 0; i < count; i++) 
	{
        listAppend(head, pArr[i]);
    }
    free(pArr);
}

/* 释放链表 */
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

/* 学生结构 */
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

/* 教师结构 */
typedef struct Teacher 
{
    char number[20];
    char faculty[20];
    char name[20];
    char email[20];
    char password[20];
}Teacher;

/* 上课时间段 */
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

/* 课程结构 */
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

/* 选课信息结构 */
typedef struct CourseSel 
{
    char studentNumber[20];
    char CourseNumber[20];
}CourseSel;

/* 创建学生结构 */
Student* createStudent() 
{
    Student* ptr = (Student*)malloc(sizeof(Student));
    memset(ptr, 0, sizeof(Student));
    return ptr;
}

/* 复制学生结构 */
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

/* 创建教师结构 */
Teacher* createTeacher() 
{
    Teacher* ptr = (Teacher*)malloc(sizeof(Teacher));
    memset(ptr, 0, sizeof(Teacher));
    return ptr;
}

/* 复制教师结构 */
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

/* 创建课程 */
Course* createCourse() 
{
    Course* ptr = (Course*)malloc(sizeof(Course));
    memset(ptr, 0, sizeof(Course));
    return ptr;
}

/* 克隆课程 */
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

/* 创建选课结构 */
CourseSel* createCourseSel() 
{
    CourseSel* ptr = (CourseSel*)malloc(sizeof(CourseSel));
    memset(ptr, 0, sizeof(CourseSel));
    return ptr;
}

/* 克隆选课结构 */
CourseSel* cloneCourseSel(CourseSel* crs) 
{
    /*char studentNumber[20];
    char CourseNumber[20];*/

    CourseSel* ncrs = createCourseSel();
    strcpy(ncrs->studentNumber, crs->studentNumber);
    strcpy(ncrs->CourseNumber, crs->CourseNumber);
    return ncrs;
}

/* 全局变量声明 */
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

/* 初始化全局链表 */
void initLists() 
{
    g_studentHead = listCreate();
    g_teacherHead = listCreate();
    g_courseHead = listCreate();
    g_courseSelHead = listCreate();
    g_courseHistoryHead = listCreate();
    g_courseSelHistoryHead = listCreate();
}

/* 释放全局链表 */
void freeLists() 
{
    listFree(g_studentHead); g_studentHead = NULL;
    listFree(g_teacherHead); g_teacherHead = NULL;
    listFree(g_courseHead); g_courseHead = NULL;
    listFree(g_courseSelHead); g_courseSelHead = NULL;
}

typedef void(*FileOpt)(FILE* fp, Node* head);
/* 读取文件 */
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

/* 写入文件 */
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

/* 学生数据读取 */
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

/* 学生数据写入 */
void studentDataWrite(FILE* fp, Node* head) 
{
    for (int i = 0; i < listCount(g_studentHead); i++) 
	{ 
        Student* stu = (Student*)listItemAt(g_studentHead, i);
        fprintf(fp, "%s %s %s %s %s %s %s %s\n", stu->number, stu->faculty,
            stu->science, stu->name, stu->sex, stu->phone, stu->email, stu->password);
    }
}

/* 载入学生数据 */
void loadStudentData(const char* name, Node* head) 
{
    readFile(name, head, studentDataRead);
}

/* 保存学生数据 */
void saveStudentData(const char* name, Node* head)
{
    writeFile(name, head, studentDataWrite);
}

/* 教师数据读取 */
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

/* 教师数据写入 */
void teacherDataWrite(FILE* fp, Node* head) 
{
    for (int i = 0; i < listCount(g_teacherHead); i++) 
	{
        Teacher* ptr = (Teacher*)listItemAt(head, i);
        fprintf(fp, "%s %s %s %s %s\n", ptr->number,
            ptr->faculty, ptr->name, ptr->email, ptr->password);
    }
}

/* 载入教师数据 */
void loadTeacherData(const char* name, Node* head) 
{ 
    readFile(name, head, teacherDataRead);
}

/* 保存教师数据 */
void saveTeacherData(const char* name, Node* head) 
{
    writeFile(name, head, teacherDataWrite);
}

/* 课程数据读取 */
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

/* 课程数据写入 */
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

/* 载入课程数据 */
void loadCourseData(const char* name, Node* head) 
{
    readFile(name, head, courseDataRead);
}

/* 保存课程数据 */
void saveCourseData(const char* name, Node* head) 
{
    writeFile(name, head, courseDataWrite);
}

/* 选课数据读取 */
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

/* 选课数据吸入 */
void courseSelDataWrite(FILE* fp, Node* head) 
{
    for (int i = 0; i < listCount(head); i++) 
	{
        CourseSel* ptr = (CourseSel*)listItemAt(head, i);
        fprintf(fp, "%s %s\n", ptr->studentNumber, ptr->CourseNumber);
    }
}

/* 载入选课数据 */
void loadCourseSelData(const char* name, Node* head) 
{
    readFile(name, head, courseSelDataRead);
}

/* 保存选课数据 */
void saveCourseSelData(const char* name, Node* head) 
{
    writeFile(name, head, courseSelDataWrite);
}

// global
/* 保存全局学生数据 */
void saveGlobalStudentData()
{
    saveStudentData("student.txt", g_studentHead);
}

/* 载入全局学生数据 */
void loadGlobalStudentData() 
{
    loadStudentData("student.txt", g_studentHead);
}

/* 保存全局教师数据 */
void saveGlobalTeacherData() 
{
    saveTeacherData("teacher.txt", g_teacherHead);
}

/* 载入全局教师数据 */
void loadGlobalTeacherData() 
{
    loadTeacherData("teacher.txt", g_teacherHead);
}

/* 保存全局课程数据 */
void saveGlobalCourseData() 
{
    saveCourseData("course.txt", g_courseHead);
}

/* 载入全局课程数据 */
void loadGlobalCourseData() 
{
    loadCourseData("course.txt", g_courseHead);
}

/* 保存全局课程数据 */
void saveGlobalCourseSelData() 
{
    saveCourseSelData("courseSel.txt", g_courseSelHead);
}

/* 载入全局课程数据 */
void loadGlobalCourseSelData() 
{
    loadCourseSelData("courseSel.txt", g_courseSelHead);
}

/* 载入全局历史课程数据 */
void loadGlobalCourseHistoryData() 
{
    loadCourseData("courseHistory.txt", g_courseHistoryHead);
}

/* 载入全局历史选课数据 */
void loadGlobalCourseSelHistoryData() 
{
    loadCourseSelData("courseSelHistory.txt", g_courseSelHistoryHead);
}

// student
/* 查找学生 */
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

/* 学生账号密码校验 */
int studentCheck(const char* number, const char* password) 
{
    Student* ptr = findStudent(number);
    if (ptr == NULL) 
		return FALSE;
    return strcmp(ptr->password, password) == 0;
}

// teacher
/* 查找教师 */
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

/* 查找教师 */
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

/* 教师账号密码校验 */
int teacherCheck(const char* number, const char* password) 
{
    Teacher* ptr = findTeacher(number);
    if (ptr == NULL) 
		return FALSE;
    return strcmp(ptr->password, password) == 0;
}

// course
/* 查找课程 */
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

/* 查找课程 */
Course* findCourseByNameByCurTeacher(const char* name) 
{
    Course* cr = findCourseByName(name);
    if (cr == NULL) 
		return NULL;
    if (strcmp(cr->teacher, g_curTeacher->name) != 0) 
		return NULL;
    return cr;
}

/* 查找课程 */
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

/* 获取课程列表 */
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

/* 是否已经有课程 */
int hasCourseByNumber(const char* number) 
{
    return findCourseByNumber(number) != NULL;
}

/* 是否已经有课程 */
int hasCourseByName(const char* name) 
{
    return findCourseByName(name) != NULL;
}

/* 获取教师课程列表 */
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

/* 获取教师历史课程列表 */
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

/* 获取院系课程列表 */
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

/* 获取教师课程数量 */
int getTeacherCourseCount(const char* name) 
{
    Node* list = getTeacherCourses(name);
    int count = listCount(list);
    listFree(list);
    return count;
}

/* 获取选中该课程的人数 */
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

/* 获取当前学生选择的课程数 */
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

/* 获取当前学生的课程列表 */
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

/* 获取当前学生的历史课程列表 */
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

/* 获取课程 */
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

/* 通过课时排序课程 */
int sortCourseByHoursFun(void* a, void* b) 
{
    return ((Course*)a)->hours < ((Course*)b)->hours;
}

/* 通过学生数量排序课程 */
int sortCourseBySelectCountFun(void* a, void* b) 
{
    return getCourseSelectCount(((Course*)a)->name)
        < getCourseSelectCount(((Course*)b)->name);
}

/* 通过课时排序课程 */
void sortCourseByHours() 
{
    listSort(g_courseHead, sortCourseByHoursFun);
}

/* 通过学生数量排序课程 */
void sortCourseBySelectCount() 
{
    listSort(g_courseHead, sortCourseBySelectCountFun);
}

// courseSel
/* 获取当前学生的选课数量 */
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

/* 在当前学生用的的选课列表中通过课号查找一个选课 */
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

/* 通过选课名获取学生列表 */
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
/* 打印学生表头 */
void printStudentHead() 
{
    printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n",
        "学号", "院系", "专业", "姓名", "性别", "电话", "邮箱");
}

/* 打印学生数据 */
void printStudentLine(Student* stu) 
{
    printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n", stu->number,
        stu->faculty, stu->science, stu->name, stu->sex, stu->phone, stu->email);
}

/* 打印教师表头 */
void printTeacherHead() 
{
    printf("%-15s%-15s%-15s%-15s\n", "工号", "院系", "姓名", "邮箱");
}

/* 打印教师数据 */
void printTeacherLine(Teacher* tea) 
{
    printf("%-15s%-15s%-15s%-15s\n", tea->number, tea->faculty, tea->name, tea->email);
}

/* 打印课程表头 */
void printCourseHead() 
{
    // 太长, 打印不下
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

/* 打印课程数据 */
void printCourseLine(Course* cr) 
{
    printf("\n");
    printf("课程编号:%s\n", cr->number);
    printf("课程名称:%s\n", cr->name);
    printf("课程学分:%d\n", cr->credit);
    printf("课程学时:%d\n", cr->hours);
    printf("课程性质:%s\n", cr->nature);
    printf("任课教师:%s\n", cr->teacher);
    printf("上课地点:%s\n", cr->location);
    printf("限制人数:%d\n", cr->limit);
    printf("课程简介:%s\n", cr->introduction);
    printf("教材信息:%s\n", cr->teachingMaterial);
    printf("\n");
}

/* 打印课程数据并打印选课人数 */
void printCourseLineAppendSelectCount(Course* cr) 
{
    printf("\n");
    printf("课程编号:%s\n", cr->number);
    printf("课程名称:%s\n", cr->name);
    printf("课程学分:%d\n", cr->credit);
    printf("课程学时:%d\n", cr->hours);
    printf("课程性质:%s\n", cr->nature);
    printf("任课教师:%s\n", cr->teacher);
    printf("上课地点:%s\n", cr->location);
    printf("限制人数:%d\n", cr->limit);
    printf("课程简介:%s\n", cr->introduction);
    printf("教材信息:%s\n", cr->teachingMaterial);
    printf("当前选课人数:%d\n", getCourseSelectCount(cr->name));
    printf("\n");
}

/* 打印选课表头 */
void printfCourseSelHead() 
{
    /*char studentNumber[20];
    char CourseNumber[20];*/
    printf("%-15s%-15s\n", "姓名", "课程");
}

/* 打印选课数据 */
void printfCourseSelLine(CourseSel* crs) 
{
    Student* stu = findStudent(crs->studentNumber);
    Course* cr = findCourseByNumber(crs->CourseNumber);
    if (stu == NULL || cr == NULL) 
		return;
    printf("%-15s%-15s\n", stu->name, cr->name);
}

/* 在字符串str查找字符c */
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
/* 字符串的是否是否都是数字 */
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

/* 获取长度为len的整数字符串 */
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
            printf("输入错误,请输入一个长度为%d的整数:", len);
        else
            printf("输入错误,请输入一个整数:");
    }
    return NULL;
}

/* 获取学生学号或者教师编号 */
char* getNumber() 
{
    return getIntStr(10);
}

/* 获取电话号码 */
char* getPhoneNumber() 
{
    return getIntStr(11);
}

/* 获取课号 */
char* getCourseNumber() 
{
    return getIntStr(6);
}

/* 获取限制人数 */
int getLimit() 
{
    int n;
    while (TRUE) 
	{
        scanf("%d", &n);
        if (n != LIMITSEL1 && n != LIMITSEL2) 
		{
            printf("输入错误,请重新输入(%d or %d):", LIMITSEL1, LIMITSEL2);
            continue;
        }
        break;
    }
    getchar();
    return n;
}

/* 获取上课位置 */
char* getLocation() 
{
	return getIntStr(10);
}

/* 获取课时 */
int getHours() 
{
    int n;
    while (TRUE) 
	{
        scanf("%d", &n);
        if (n <= 0) 
		{
            printf("请输入>0的整数:");
            continue;
        }
        break;
    }
    return n;
}

/* 获取课程性质 */
char* getNature() 
{
    while (TRUE) 
	{
        scanf("%s", g_buffer);
        if (strcmp(g_buffer, "必修") != 0 && strcmp(g_buffer, "选修") != 0) 
			{
            	printf("请输入(必修 or 选修):");
            	continue;
        	}
        break;
    }
    return g_buffer;
}

/* 获取上课时间段 */
int getTimeSegment() 
{
    printf("\n可选的上课时间段\n");
    for (int i = 1; i <= 10; i++) 
	{
        printf("%d.%s\n", i, g_timeSegments[i]);
    }
    int n;
    while (TRUE) 
	{
        printf("\n请输入:");
        scanf("%d", &n);
        if (n < 1 || n >10) 
		{
            printf("请输入[1,10]范围的值");
            continue;
        }
        break;
    }
    return n;
}

/* 获取邮箱 */
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
            printf("邮箱格式错误,请重新输入(*****@***.***):");
            continue;
        } 
		break;
    }
    return str;
}

/* 获取学分 */
int getCredit() 
{
    int n;
    while (TRUE)
	{
        scanf("%d", &n);
        if (n < 1 || n>4) 
		{
            printf("请输入范围[1,4]的值:");
            continue;
        }
        break;
    }
    return n;
}

/* 学生登录 */
int loginStudent() 
{
    char number[20];
    char passwor[20];
    system("cls");
    printf("学生登录\n");
    printf("请输入账号:");
    scanf("%s", number);
    printf("请输入密码:");
    scanf("%s", passwor);
    if (studentCheck(number, passwor)) 
	{
        g_userType = T_STUDENT;
        g_curStudent = findStudent(number);
        return TRUE;
    } 
	else 
	{
        printf("信息错误,请重新输入.\n");
        system("pause");
        return FALSE;
    }
}

/* 教师登录 */
int loginTeacher() 
{
    char number[20];
    char passwor[20];
    system("cls");
    printf("教师登录\n");
    printf("请输入账号:");
    scanf("%s", number);
    printf("请输入密码:");
    scanf("%s", passwor);
    if (teacherCheck(number, passwor)) 
	{
        g_userType = T_STUDENT;
        g_curTeacher = findTeacher(number);
        return TRUE;
    } 
	else 
	{
        printf("信息错误,请重新输入.\n");
        system("pause");
        return FALSE;
    }
}

/* 学生选课 */
void stduentSelectCourse() 
{
    /*学生选课根据系统提供的课程进行浏览并可选择感
    兴趣的课程。
    同一名学生的两门或多门课程时间不能冲突
    规定一个学生一个学期最多能选3门课
    每门课程选课人数不能超过限制人数*/

    if (g_courseSelStatus != T_STARTSEL) 
	{
        printf("未开放选课\n");
        system("pause");
        return;
    }

    if (getSelectCourseCountByCurStu() >= 3) 
	{
        printf("选课已经达到上限\n");
        system("pause");
        return;
    }

    printf("请输入课程名:");
    char name[50]; scanf("%s", name);
    Course* cr = findCourseByName(name);
    if (cr == NULL) 
	{
        printf("课程不存在\n");
        system("pause");
        return;
    }

    if (getCourseSelectCount(cr->name) >= cr->limit) 
	{
        printf("选课人数已经达到上限\n");
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
            printf("上课时间冲突\n");
            system("pause");
            return;
        }

        if (strcmp(ptr->name, cr->name) == 0) 
		{
            listFree(list);
            printf("该课程已经选择过了\n");
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
    printf("添加选课成功\n");
    system("pause");
    return;
}

/* 根据课程名查询 */
void courseQueryByName() 
{
    printf("请输入课程名:");
    char name[50]; scanf("%s", name);
    Course* cr = findCourseByName(name);
    if (cr == NULL) 
	{
        printf("没有找到该课程\n");
        system("pause");
        return;
    }

    printCourseLine(cr);
    system("pause");
}

/* 根据开课学院查询 */
void courseQueryByFaculty() 
{
    printf("请输入学院名称:");
    char name[50]; scanf("%s", name);
    Node* list = getCourseByFaculty(name);
    if (listCount(list) == 0) 
	{
        listFree(list);
        printf("信息为空\n");
        system("pause");
        return;
    }

    for (int i = 0; i < listCount(list); i++) 
	{
        printCourseLine((Course*)listItemAt(list, i));
    }

    system("pause");
}

/* 根据课余量排序所有课程 */
void courseQueryByHourse() 
{
    sortCourseByHours();
    for (int i = 0; i < listCount(g_courseHead); i++) 
	{
        printCourseLine((Course*)listItemAt(g_courseHead, i));
    }
    system("pause");
}

/* 根据选课人数排序所有课程 */
void courseQueryBySelectCount() 
{
    sortCourseBySelectCount();
    for (int i = 0; i < listCount(g_courseHead); i++) 
	{
        printCourseLineAppendSelectCount((Course*)listItemAt(g_courseHead, i));
    }
    system("pause");
}

/* 查询课程 */
void studentQueryCourse() 
{
    /*查询课程
    根据课程名查询
    根据开课学院查询
    根据课余量排序所有课程
    根据选课人数排序所有课程 */
    while (TRUE) 
	{
        system("cls");
        printf("\t|\t查询课程\t|\n\n");
        printf("\t|\t1.根据课程名查询\t|\n\n");
        printf("\t|\t2.根据开课学院查询\t|\n\n");
        printf("\t|\t3.根据课余量排序课程\t|\n\n");
        printf("\t|\t4.根据选课人数排序课程\t|\n\n");
        printf("\t|\t0.返回上一级菜单\t|\n\n"); 
        printf(" 请输入功能序号:");

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
        printf("信息为空\n");
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
        printf("信息为空\n");
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

/* 查询选课结果 */
void querySelectedCourse() 
{
    /*查询选课结果
    查看学生曾经选过的课程 */ 
    while (TRUE) 
	{
        system("cls");
        printf("\t|\t选课结果查询\t|\n\n");
        printf("\t|\t1.查询选课结果\t|\n\n");
        printf("\t|\t2.查询历史选课\t|\n\n");
        printf("\t|\t0.返回上一级菜单\t|\n\n"); 
        printf(" 请输入功能序号:");

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

/* 删除选课 */
void deleteSelectedCourse() 
{
    /* 删除选课结果
    在未开课前学生可以删除自己的选课结果*/

    if (g_courseSelStatus == T_STARTCLASS) 
	{
        printf("课程已经开始,无法进行删除操作\n");
        system("pause");
        return;
    }

    printf("请输入要删除的选课名:");
    char name[50]; 
	scanf("%s", name);
    Course* cr = getCourseByCurStu(name);
    if (cr == NULL) 
	{
        printf("您没有选择该课程\n");
        system("pause");
        return;
    }

    CourseSel* sel = findOneCourseSelByNumberByCurStu(cr->number);
    listRemoveByData(g_courseSelHead, sel);
    saveGlobalCourseSelData();
    printf("删除成功\n");
    system("pause");
}

/* 学生修改密码 */
void studentModifyPassword() 
{
    printf("请输入密码:");
    char password[50];
    scanf("%s", password);
    strcpy(g_curStudent->password, password);
    saveGlobalStudentData();
    printf("修改成功\n");
    system("pause");
}

/* 学生修改邮箱 */
void studentModifyEmail() 
{
    printf("请输入邮箱:");
    strcpy(g_curStudent->email, getEmail());
    saveGlobalStudentData();
    printf("修改成功\n");
    system("pause");
}

/* 学生修改电话 */
void studentModifyPhone() 
{
    printf("请输入电话:");
    strcpy(g_curStudent->phone, getPhoneNumber());
    saveGlobalStudentData();
    printf("修改成功\n");
    system("pause");
}

/* 学生信息管理 */
void studentInfomanage() 
{
    /*个人息管理
    电话、密码、邮箱修改*/
    while (TRUE) 
	{
        system("cls");
        printf("\t|\t个人信息管理\t|\n\n");
        printf("\t|\t1.修改密码\t|\n\n");
        printf("\t|\t2.修改邮箱\t|\n\n");
        printf("\t|\t3.修改电话\t|\n\n");
        printf("\t|\t4.查看个人信息\t|\n\n");
        printf("\t|\t0.返回上一级菜单\t|\n\n"); 
        printf(" 请输入功能序号:");
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

/* 学生菜单 */
void studentLoop() 
{
    while (TRUE) 
	{
        system("cls");
        printf("\t|\t学生菜单\t|\n\n");
        printf("\t|\t1.学生选课\t|\n\n");
        printf("\t|\t2.查询课程\t|\n\n");
        printf("\t|\t3.查询选课结果\t|\n\n");
        printf("\t|\t4.删除选课结果\t|\n\n");
		printf("\t|\t5.个人信息管理\t|\n\n"); 
        printf("\t|\t0.退出登录\t|\n\n"); 
        printf(" 请输入功能序号:");

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

/* 查询教师自己开设过的课程的选课情况 */
void querySelfCourseSituation() 
{
    /* 查询教师自己开设过的课程的选课情况
    (选课人数和课程详细信息)*/

    Node* list = getCoursesByCurTeacher();
    if (listCount(list) == 0) 
	{
        printf("信息为空\n");
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

/* 根据学生姓名查询 */
void queryCourseSelStudentInfoByStudentName() 
{
    /* 根据学生姓名查询 */
    printf("请输入课程名\n");
    char courseName[50]; scanf("%s", courseName);
    printf("请输入学生名称\n");
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
    printf("没有找到该学生的信息\n");
    system("pause");
    return;
}

/* 根据课程名称查询 */
void queryCourseSelStudentInfoByCourseName() 
{
    /* 根据课程名称查询 */
    printf("请输入课程名\n");
    char name[50]; scanf("%s", name);
    Node* list = getStudentsByCourseName(name);
    if (listCount(list) == 0) 
	{
        listFree(list);
        printf("信息为空\n");
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

/* 查询选择某门课程的学生信息 */
void queryCourseSelStudentInfo() 
{
    /* 查询选择某门课程的学生信息
    (根据学生姓名或/和课程名称）*/
    while (TRUE) 
	{
        system("cls");
        printf("\t|\t查询课程的学生信息\t|\n\n");
        printf("\t|\t1.根据学生姓名查询\t|\n\n");
        printf("\t|\t2.根据课程名称查询\t|\n\n"); 
        printf("\t|\t0.返回上一级菜单\t|\n\n"); 
        printf(" 请输入功能序号:");

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

/* 查看选课情况 */
void queryCourseSituation() 
{
    while (TRUE) 
	{
        system("cls");
        printf("\t|\t查看选课情况\t|\n\n");
        printf("\t|\t1.查询本学期开设课程选课情况\t|\n\n");
        printf("\t|\t2.查询课程的学生信息\t|\n\n");
        printf("\t|\t0.返回上一级菜单\t|\n\n"); 
        printf(" 请输入功能序号:");

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

/* 选课结束后如果某门课程的选课人数少于3则删除 */
void deleteSubstandardCourseSel() 
{
    /* 选课结束后如果某门课程的选课人数少于3则删除
    该课程所有选择该课程的学生选课信息删除  */
    if (g_courseSelStatus <= T_STARTSEL) 
	{
        printf("选课未结束\n");
        system("pause");
        return;
    }
    // 遍历课程
    for (int i = 0; i < listCount(g_courseHead); i++) 
	{
        Course* cr = (Course*)listItemAt(g_courseHead, i);
        // 如果人数小于3
        if (getCourseSelectCount(cr->name) < 3) 
		{
            // 遍历选课记录
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
    printf("删除成功\n");
    system("pause");
}

/* 查询教师自己开设的课程数 */
void statisticsSelfCourseCount() 
{
    system("cls");
    int count = getTeacherCourseCount(g_curTeacher->name);
    printf("您开设了%d个课程.\n", count);
    system("pause");
}

/* 按选课人数排序所有开设过的课程 */
void statisticsCourseSortBySelectCount() 
{
    sortCourseBySelectCount();
    Node* list = getCoursesByCurTeacher();
    if (listCount(list) == 0) 
	{
        listFree(list);
        printf("您没有开设课程\n");
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

/* 统计选课信息 */
void courseSelStatistics() 
{
    while (TRUE) 
	{
        system("cls");
        printf("\t|\t统计选课信息\t|\n\n");
        printf("1.统计教师自己开设过的课程数目\n");
        printf("2.按选课人数排序所有开设过的课程\n");
        printf("0.返回上一级菜单\n");
        printf("请输入功能序号:");

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

/* 选课管理 */
void courseSelManage() 
{
    while (TRUE) 
	{
        system("cls");
        printf("\t|\t选课管理\t|\n\n");
        printf("\t|\t1.查看选课情况\t|\n\n");
        printf("\t|\t2.删除选课\t|\n\n");
        printf("\t|\t3.统计选课信息\t|\n\n");
        printf("\t|\t0.返回上一级菜单\t|\n\n"); 
        printf(" 请输入功能序号:");

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

/* 查询所有开设的课程 */
void printAllCourse() 
{
    /* 查询所有开设的课程 */
    // printCourseHead();
    Node* list = getTeacherCourses(g_curTeacher->name);
    if (listCount(list) == 0) 
	{
        listFree(list);
        printf("未查询到该课程信息\n");
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

/* 查询所有历史开设的课程 */
void printAllHistoryCourse() 
{
    /* 查询所有开设的课程 */
    // printCourseHead();
    Node* list = getTeacherHistoryCourses(g_curTeacher->name);
    if (listCount(list) == 0) 
	{
        listFree(list);
        printf("未查询到该课程信息\n");
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

/* 根据课程名查询课程 */
void queryCourseByName() 
{
    /* 根据课程名查询课程 */
    char name[50];
    printf("请输入课程名称:");
    scanf("%s", name);

    Course* cr = findCourseByNameByCurTeacher(name);
    if (cr == NULL) 
	{
        printf("您未开设此门课程\n");
        system("pause");
        return;
    }

    printCourseLine(cr);
    system("pause");
}

/* 课程查询 */
void queryCourse() 
{
    while (TRUE) 
	{
        system("cls");
        printf("\t|\t课程查询\t|\n\n");
        printf("\t|\t1.查询本学期开设的课程\t|\n\n");
        printf("\t|\t2.查询历史开设的课程\t|\n\n");
        printf("\t|\t3.根据课程名查询课程\t|\n\n"); 
        printf("\t|\t0.返回上一级菜单\t|\n\n"); 
        printf(" 请输入功能序号:");

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

/* 输入课程信息 */
Course* inputCourse() 
{
    Course* course = createCourse();
    printf("请输入课程编号:");
    strcpy(course->number, getNumber());
    printf("课程名称:");
    scanf("%s", course->name);
    printf("学分(1-4):");
    course->credit = getCredit();
    printf("学时:");
    course->hours = getHours();
    printf("课程性质:");
    strcpy(course->nature, getNature());
    printf("请选择上课时间段:");
    course->timeSegments = getTimeSegment();
    printf("请输入上课地点:");
    strcpy(course->location, getLocation());
    printf("限制人数:");
    course->limit = getLimit();
    printf("课程简介:");
    gets(course->introduction);
    printf("教材信息:");
    gets(course->teachingMaterial);
    strcpy(course->teacher, g_curTeacher->name);
    return course;
}

/* 添加课程 */
void addCourse() 
{
    /*
    添加课程
    同一名教师的上课时间不能冲突
    课程名及课程号不能重复
    同一名教师一学期最多只能开两门选课
    课程的上限人数有两种选择80人和100人
    */

    Course* course = inputCourse();

    if (hasCourseByName(course->name) == TRUE) 
	{
        free(course);
        printf("课程名称重复\n");
        system("pause");
        return;
    }

    if (hasCourseByNumber(course->name) == TRUE) 
	{
        free(course);
        printf("课程号称重复\n");
        system("pause");
        return;
    }

    if (getTeacherCourseCount(g_curTeacher->name) >= 2) 
	{
        free(course);
        printf("教师一学期最多只能开两门选课\n");
        system("pause");
        return;
    }

    listAppend(g_courseHead, course);
    saveCourseData("course.txt", g_courseHead);
    printf("添加课程成功\n");
    system("pause");
}

/* 修改课程 */
void modifyCourse() 
{
    /*修改课程
    在一门课程尚未有学生选择时可以修改选课教材、课程简介、限制人数
    开始选课后可以修改限制人数。*/

    printf("请输入课程名称:");
    char name[50]; scanf("%s", name);
    Course* cr = findCourseByNameByCurTeacher(name);
    if (cr == NULL) 
	{
        printf("没有找到该课程\n");
        system("pause");
        return;
    }

    int selectCount = getCourseSelectCount(name);
    if (selectCount == 0) 
	{
        printf("请输入教材:");
        scanf("%s", cr->teachingMaterial);
        printf("请输入课程简介:");
        scanf("%s", cr->introduction);
        printf("请输入限制人数:");
        scanf("%d", &cr->limit);
    } 
	else 
	{
        printf("请输入限制人数:");
        int limit; scanf("%d", &limit);
        if (limit < selectCount) 
		{
            printf("输入的人数小于当前已经选择该课程的学生人数\n");
            printf("修改失败\n");
            system("pause");
            return;
        }
        cr->limit = limit;
        printf("修改成功\n");
        system("pause");
        return;
    }
}

/* 删除课程 */
void deleteCourse() 
{
    /* 删除课程
    未开始选课程可以进行删除操作 */

    if (g_courseSelStatus != T_NOT) 
	{
        printf("选课已经开始,无法进行删除操作.\n");
        system("pause");
        return;
    }

    char name[50];
    printf("请输入要删除选课的名称:");
    scanf("%s", name);

    Course* cr = findCourseByNameByCurTeacher(name);
    if (cr == NULL || strcmp(cr->teacher, g_curTeacher->name) != 0) 
	{
        printf("没有找到这门课程.\n");
        system("pause");
        return;
    }

    listRemoveByData(g_courseHead, cr);
    printf("删除成功\n");
}

/* 课程管理 */
void courseManage() 
{
    while (TRUE) 
	{
        system("cls");
        printf("\t|\t 课程管理\t|\n\n");
        printf("\t|\t1.课程查询\t|\n\n");
        printf("\t|\t2.添加课程\t|\n\n");
        printf("\t|\t3.修改课程\t|\n\n");
        printf("\t|\t4.删除课程\t|\n\n"); 
        printf("\t|\t0.返回上一级菜单\t|\n\n"); 
        printf(" 请输入功能序号:");

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

/* 教师修改邮箱 */
void teacherModifyEmail() 
{
    printf("请输入邮箱:");
    strcpy(g_curTeacher->email, getEmail());
    saveGlobalTeacherData();
    printf("修改成功\n");
    system("pause");
}

/* 教师修改密码 */
void teacherModifyPassword() 
{
    printf("请输入密码:");
    char password[50];
    scanf("%s", password);
    strcpy(g_curTeacher->password, password);
    saveGlobalTeacherData();
    printf("修改成功\n");
    system("pause");
}

/* 教师个人信息管理 */
void teacherInfoManage() 
{
    while (TRUE) 
	{
        system("cls");
        printf("\t|\t 个人信息管理\t|\n\n");
        printf("\t|\t1.修改密码\t|\n\n");
        printf("\t|\t2.修改邮箱\t|\n\n");
        printf("\t|\t3.查看个人信息\t|\n\n");
        printf("\t|\t0.返回上一级菜单\t|\n\n");
        printf(" 请输入功能序号:");

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

/* 教师菜单 */
void teacherLoop() 
{
    while (TRUE) 
	{
        system("cls");
        printf("\t|\t 教师菜单\t|\n\n");
        printf("\t|\t1.选课管理\t|\n\n");
        printf("\t|\t2.课程管理\t|\n\n");
        printf("\t|\t3.个人信息管理\t|\n\n");
        printf("\t|\t0.退出登录\t|\n\n");
        printf(" 请输入功能序号:");

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

/* 登录退出处理 */
void loginOut() 
{
    g_curStudent = NULL;
    g_curTeacher = NULL;
    g_userType = T_NONE;
}

/* 载入文件数据 */
void loadFileDatas() 
{
    loadGlobalStudentData();
    loadGlobalTeacherData();
    loadGlobalCourseData();
    loadGlobalCourseSelData();
    loadGlobalCourseHistoryData();
    loadGlobalCourseSelHistoryData();
}

/* 选课状态 */
void courseSelSet() 
{
    system("cls");
    printf("\t|\t 选课状态\t|\n\n");
    printf("\t|\t1.未开始选课\t|\n\n");
    printf("\t|\t2.开始选课\t|\n\n");
    printf("\t|\t3.结束选课\t|\n\n");
    printf("\t|\t4.开课\t|\n\n");
    printf("\t|\t0.退出系统\t|\t\n\n");
    printf(" 请输入功能序号:");

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
        	printf("输入非法\n");
        	system("pause");
        	return;
    }
    printf("设定成功\n");
    system("pause");
    return;
}

/* 初始化 */
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
        printf("************欢迎使用学生选课系统*************\n\n");
        printf("\t|\t 用户登录\t|\n\n");
        printf("\t|\t1.学生登录\t|\n\n");
        printf("\t|\t2.教师登录\t|\n\n");
        printf("\t|\t3.选课状态\t|\n\n");
        printf("\t|\t0.退出系统\t|\n\n");
        printf(" 请输入功能序号:");

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
