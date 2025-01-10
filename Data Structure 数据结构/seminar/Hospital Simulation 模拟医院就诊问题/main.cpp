#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 常量定义
#define NUM_DEPARTMENTS 15
#define NUM_DOCTORS_PER_DEPT 3
#define NUM_BULTRASOUND_MACHINES 3

// 患者结构体
typedef struct Patient {
    int id;
    char name[50];
    int department_id;
    int doctor_id; // -1 表示未指定医生
    int needs_b_ultrasound;
    int registration_order; // 挂号顺序
    struct Patient* next;
} Patient;

// 医生的患者记录结构体
typedef struct DoctorPatient {
    Patient* patient;
    int listen_time; // 听诊时间，单位秒
    struct DoctorPatient* next;
} DoctorPatient;

// 医生结构体
typedef struct Doctor {
    int id;
    char name[50];
    DoctorPatient* patients_head;
    DoctorPatient* patients_tail;
} Doctor;

// 科室结构体
typedef struct Department {
    int id;
    char name[50];
    // 三个指定医生的队列
    Patient* specified_queues_head[NUM_DOCTORS_PER_DEPT];
    Patient* specified_queues_tail[NUM_DOCTORS_PER_DEPT];
    // 一个通用队列
    Patient* general_queue_head;
    Patient* general_queue_tail;
    Doctor doctors[NUM_DOCTORS_PER_DEPT];
} Department;

// B超室的患者记录结构体
typedef struct BUltrasoundPatient {
    Patient* patient;
    struct BUltrasoundPatient* next;
} BUltrasoundPatient;

// B超室结构体
typedef struct BUltrasoundRoom {
    int id;
    BUltrasoundPatient* queue_head;
    BUltrasoundPatient* queue_tail;
} BUltrasoundRoom;

// 全局变量
Department departments[NUM_DEPARTMENTS];
BUltrasoundRoom b_ultrasound_room;
int patient_id_counter = 1;
int registration_order_counter = 1;

// 函数声明
void initialize_system();
void register_patient();
void process_consultations();
void process_b_ultrasound();
void display_queues();
void view_doctors_patients();
int get_department_index_by_id(int id);
int get_doctor_index_by_id(Department* dept, int doctor_id);
void clear_input_buffer();

// 主函数
int main() {
    srand(time(NULL)); // 随机数
    int choice;
    initialize_system();
    while (1) {
        printf("\n=== 医院就诊管理系统 ===\n");
        printf("1. 挂号\n");
        printf("2. 处理就诊\n");
        printf("3. 处理B超检查\n");
        printf("4. 显示各科室及B超室排队情况\n");
        printf("5. 查看医生的就诊记录\n");
        printf("6. 退出\n");
        printf("请输入选择: ");
        if (scanf("%d", &choice) != 1) {
            printf("输入无效，请重新输入。\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        switch (choice) {
            case 1:
                register_patient();
                break;
            case 2:
                process_consultations();
                break;
            case 3:
                process_b_ultrasound();
                break;
            case 4:
                display_queues();
                break;
            case 5:
                view_doctors_patients();
                break;
            case 6:
                printf("退出系统。\n");
                exit(0);
            default:
                printf("选择无效，请重新输入。\n");
        }
    }
    return 0;
}

// 初始化系统，包括科室、医生和B超室
void initialize_system() {
    // 初始化科室
    for (int i = 0; i < NUM_DEPARTMENTS; i++) {
        departments[i].id = i + 1;
        sprintf(departments[i].name, "科室%d", i + 1);
        departments[i].general_queue_head = NULL;
        departments[i].general_queue_tail = NULL;
        // 初始化指定医生队列
        for (int j = 0; j < NUM_DOCTORS_PER_DEPT; j++) {
            departments[i].specified_queues_head[j] = NULL;
            departments[i].specified_queues_tail[j] = NULL;
        }
        // 初始化医生
        for (int j = 0; j < NUM_DOCTORS_PER_DEPT; j++) {
            departments[i].doctors[j].id = j + 1;
            sprintf(departments[i].doctors[j].name, "医生%d-%d", i + 1, j + 1);
            departments[i].doctors[j].patients_head = NULL;
            departments[i].doctors[j].patients_tail = NULL;
        }
    }
    // 初始化B超室
    b_ultrasound_room.id = 1;
    b_ultrasound_room.queue_head = NULL;
    b_ultrasound_room.queue_tail = NULL;
}

// 挂号过程
void register_patient() {
    Patient* new_patient = (Patient*)malloc(sizeof(Patient));
    if (!new_patient) {
        printf("内存分配失败。\n");
        return;
    }
    new_patient->id = patient_id_counter++;
    printf("请输入患者姓名: ");
    fgets(new_patient->name, sizeof(new_patient->name), stdin);
    new_patient->name[strcspn(new_patient->name, "\n")] = '\0'; // 去掉换行符
    printf("请选择科室（1-%d）:\n", NUM_DEPARTMENTS);
    for (int i = 0; i < NUM_DEPARTMENTS; i++) {
        printf("%d. %s\n", departments[i].id, departments[i].name);
    }
    int dept_id;
    printf("输入科室编号: ");
    if (scanf("%d", &dept_id) != 1 || dept_id < 1 || dept_id > NUM_DEPARTMENTS) {
        printf("科室编号无效。\n");
        free(new_patient);
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    new_patient->department_id = dept_id;
    new_patient->doctor_id = -1; // 默认不指定医生
    printf("是否指定医生？（1. 是  2. 否）: ");
    int specify;
    if (scanf("%d", &specify) != 1) {
        printf("输入无效。\n");
        free(new_patient);
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    if (specify == 1) {
        printf("请选择医生:\n");
        Department* dept = &departments[get_department_index_by_id(dept_id)];
        for (int i = 0; i < NUM_DOCTORS_PER_DEPT; i++) {
            printf("%d. %s\n", dept->doctors[i].id, dept->doctors[i].name);
        }
        int doctor_id;
        printf("输入医生编号: ");
        if (scanf("%d", &doctor_id) != 1 || doctor_id < 1 || doctor_id > NUM_DOCTORS_PER_DEPT) {
            printf("医生编号无效。\n");
            free(new_patient);
            clear_input_buffer();
            return;
        }
        clear_input_buffer();
        new_patient->doctor_id = doctor_id;
    }
    printf("是否需要B超检查？（1. 是  2. 否）: ");
    int b_ultrasound;
    if (scanf("%d", &b_ultrasound) != 1) {
        printf("输入无效。\n");
        free(new_patient);
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    new_patient->needs_b_ultrasound = (b_ultrasound == 1) ? 1 : 0;
    new_patient->registration_order = registration_order_counter++;
    new_patient->next = NULL;
    // 添加到对应科室的队列
    Department* dept = &departments[get_department_index_by_id(dept_id)];
    if (new_patient->doctor_id != -1) {
        // 添加到指定医生的队列
        int doc_index = get_doctor_index_by_id(dept, new_patient->doctor_id);
        if (doc_index == -1) {
            printf("医生编号无效。\n");
            free(new_patient);
            return;
        }
        if (dept->specified_queues_tail[doc_index] == NULL) {
            dept->specified_queues_head[doc_index] = dept->specified_queues_tail[doc_index] = new_patient;
        }
        else {
            dept->specified_queues_tail[doc_index]->next = new_patient;
            dept->specified_queues_tail[doc_index] = new_patient;
        }
    }
    else {
        // 添加到通用队列
        if (dept->general_queue_tail == NULL) {
            dept->general_queue_head = dept->general_queue_tail = new_patient;
        }
        else {
            dept->general_queue_tail->next = new_patient;
            dept->general_queue_tail = new_patient;
        }
    }
    printf("挂号成功。您的挂号号为 %d。\n", new_patient->id);
}

// 处理就诊过程
void process_consultations() {
    for (int i = 0; i < NUM_DEPARTMENTS; i++) {
        Department* dept = &departments[i];
        // 找到当前科室四个队列中挂号顺序最早的患者
        Patient* earliest_patient = NULL;
        int earliest_queue = -1; // 0-2: 指定医生队列，3: 通用队列
        for (int j = 0; j < NUM_DOCTORS_PER_DEPT; j++) {
            if (dept->specified_queues_head[j] != NULL) {
                if (earliest_patient == NULL || dept->specified_queues_head[j]->registration_order < earliest_patient->registration_order) {
                    earliest_patient = dept->specified_queues_head[j];
                    earliest_queue = j;
                }
            }
        }
        // 检查通用队列
        if (dept->general_queue_head != NULL) {
            if (earliest_patient == NULL || dept->general_queue_head->registration_order < earliest_patient->registration_order) {
                earliest_patient = dept->general_queue_head;
                earliest_queue = NUM_DOCTORS_PER_DEPT; // 通用队列编号
            }
        }
        if (earliest_patient != NULL) {
            if (earliest_queue < NUM_DOCTORS_PER_DEPT) {
                // 指定医生队列
                int doc_index = earliest_queue;
                // 移出患者
                dept->specified_queues_head[doc_index] = dept->specified_queues_head[doc_index]->next;
                if (dept->specified_queues_head[doc_index] == NULL) {
                    dept->specified_queues_tail[doc_index] = NULL;
                }
                // 记录到医生的患者列表
                Doctor* doc = &dept->doctors[doc_index];
                DoctorPatient* doc_patient = (DoctorPatient*)malloc(sizeof(DoctorPatient));
                if (!doc_patient) {
                    printf("内存分配失败。\n");
                    return;
                }
                doc_patient->patient = earliest_patient;
                // 模拟听诊时间为5-15秒
                doc_patient->listen_time = 5 + rand() % 11;
                doc_patient->next = NULL;
                if (doc->patients_tail == NULL) {
                    doc->patients_head = doc->patients_tail = doc_patient;
                }
                else {
                    doc->patients_tail->next = doc_patient;
                    doc->patients_tail = doc_patient;
                }
                printf("科室%s的%s接诊了患者%s（ID: %d），听诊时间: %d 秒。\n",
                    dept->name, doc->name, earliest_patient->name, earliest_patient->id, doc_patient->listen_time);
                // 如果需要B超，添加到B超室队列
                if (earliest_patient->needs_b_ultrasound) {
                    BUltrasoundPatient* bu_patient = (BUltrasoundPatient*)malloc(sizeof(BUltrasoundPatient));
                    if (!bu_patient) {
                        printf("内存分配失败。\n");
                        return;
                    }
                    bu_patient->patient = earliest_patient;
                    bu_patient->next = NULL;
                    if (b_ultrasound_room.queue_tail == NULL) {
                        b_ultrasound_room.queue_head = b_ultrasound_room.queue_tail = bu_patient;
                    }
                    else {
                        b_ultrasound_room.queue_tail->next = bu_patient;
                        b_ultrasound_room.queue_tail = bu_patient;
                    }
                    printf("患者%s（ID: %d）已被添加到B超室队列。\n", earliest_patient->name, earliest_patient->id);
                }
            }
            else {
                // 医生是不是全年无休呀？一直干活？还是要考虑休息的时间？
                // 这里假设按医生编号顺序分配
                int assigned = 0;
                for (int j = 0; j < NUM_DOCTORS_PER_DEPT; j++) {
                    Doctor* doc = &dept->doctors[j];
                    // 看医生是否在忙碌，如果不是一直干活要另外考虑（这里简化为始终可用）这里直接分配
                    // 移出患者
                    Patient* patient = dept->general_queue_head;
                    dept->general_queue_head = dept->general_queue_head->next;
                    if (dept->general_queue_head == NULL) {
                        dept->general_queue_tail = NULL;
                    }
                    // 记录到医生的患者列表
                    DoctorPatient* doc_patient = (DoctorPatient*)malloc(sizeof(DoctorPatient));
                    if (!doc_patient) {
                        printf("内存分配失败。\n");
                        return;
                    }
                    doc_patient->patient = patient;
                    // 模拟听诊时间为5-15秒
                    doc_patient->listen_time = 5 + rand() % 11;
                    doc_patient->next = NULL;
                    if (doc->patients_tail == NULL) {
                        doc->patients_head = doc->patients_tail = doc_patient;
                    }
                    else {
                        doc->patients_tail->next = doc_patient;
                        doc->patients_tail = doc_patient;
                    }
                    printf("科室%s的%s接诊了患者%s（ID: %d），听诊时间: %d 秒。\n",
                        dept->name, doc->name, patient->name, patient->id, doc_patient->listen_time);
                    // 如果需要B超，添加到B超室队列
                    if (patient->needs_b_ultrasound) {
                        BUltrasoundPatient* bu_patient = (BUltrasoundPatient*)malloc(sizeof(BUltrasoundPatient));
                        if (!bu_patient) {
                            printf("内存分配失败。\n");
                            return;
                        }
                        bu_patient->patient = patient;
                        bu_patient->next = NULL;
                        if (b_ultrasound_room.queue_tail == NULL) {
                            b_ultrasound_room.queue_head = b_ultrasound_room.queue_tail = bu_patient;
                        }
                        else {
                            b_ultrasound_room.queue_tail->next = bu_patient;
                            b_ultrasound_room.queue_tail = bu_patient;
                        }
                        printf("患者%s（ID: %d）已被添加到B超室队列。\n", patient->name, patient->id);
                    }
                    assigned = 1;
                    break; // 只分配给一个医生
                }
                if (!assigned) {
                    printf("科室%s的所有医生都在忙碌，无法接诊患者%s（ID: %d）。\n",
                        dept->name, earliest_patient->name, earliest_patient->id);
                }
            }
        }
    }
}

// 处理B超检查过程
void process_b_ultrasound() {
    for (int i = 0; i < NUM_BULTRASOUND_MACHINES; i++) {
        if (b_ultrasound_room.queue_head != NULL) {
            BUltrasoundPatient* bu_patient = b_ultrasound_room.queue_head;
            b_ultrasound_room.queue_head = b_ultrasound_room.queue_head->next;
            if (b_ultrasound_room.queue_head == NULL) {
                b_ultrasound_room.queue_tail = NULL;
            }
            printf("B超机%d正在处理患者%s（ID: %d）。\n", i + 1,
                bu_patient->patient->name, bu_patient->patient->id);
            free(bu_patient);
        }
    }
    printf("B超处理完成。\n");
}

// 显示各科室及B超室的排队情况
void display_queues() {
    printf("\n=== 各科室排队情况 ===\n");
    for (int i = 0; i < NUM_DEPARTMENTS; i++) {
        Department* dept = &departments[i];
        printf("科室%s（ID: %d）队列:\n", dept->name, dept->id);
        // 显示指定医生队列
        for (int j = 0; j < NUM_DOCTORS_PER_DEPT; j++) {
            printf("  %s队列:\n", dept->doctors[j].name);
            if (dept->specified_queues_head[j] == NULL) {
                printf("    无患者排队。\n");
            }
            else {
                Patient* current = dept->specified_queues_head[j];
                while (current != NULL) {
                    printf("    患者ID: %d, 姓名: %s, 需要B超: %s, 挂号顺序: %d\n",
                        current->id, current->name,
                        current->needs_b_ultrasound ? "是" : "否",
                        current->registration_order);
                    current = current->next;
                }
            }
        }
        // 显示通用队列
        printf("  通用队列:\n");
        if (dept->general_queue_head == NULL) {
            printf("    无患者排队。\n");
        }
        else {
            Patient* current = dept->general_queue_head;
            while (current != NULL) {
                printf("    患者ID: %d, 姓名: %s, 需要B超: %s, 挂号顺序: %d\n",
                    current->id, current->name,
                    current->needs_b_ultrasound ? "是" : "否",
                    current->registration_order);
                current = current->next;
            }
        }
    }
    // 显示B超室队列
    printf("\n=== B超室队列 ===\n");
    if (b_ultrasound_room.queue_head == NULL) {
        printf("  无患者排队。\n");
    }
    else {
        BUltrasoundPatient* current = b_ultrasound_room.queue_head;
        while (current != NULL) {
            printf("  患者ID: %d, 姓名: %s\n",
                current->patient->id, current->patient->name);
            current = current->next;
        }
    }
}

// 查看医生的就诊记录
void view_doctors_patients() {
    printf("\n请选择科室（1-%d）: ", NUM_DEPARTMENTS);
    int dept_id;
    if (scanf("%d", &dept_id) != 1 || dept_id < 1 || dept_id > NUM_DEPARTMENTS) {
        printf("科室编号无效。\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    Department* dept = &departments[get_department_index_by_id(dept_id)];
    printf("科室%s的医生及其就诊记录:\n", dept->name);
    for (int i = 0; i < NUM_DOCTORS_PER_DEPT; i++) {
        Doctor* doc = &dept->doctors[i];
        printf("医生%s（ID: %d）看诊的患者:\n", doc->name, doc->id);
        if (doc->patients_head == NULL) {
            printf("  无患者记录。\n");
        }
        else {
            DoctorPatient* current = doc->patients_head;
            while (current != NULL) {
                printf("  患者ID: %d, 姓名: %s, 听诊时间: %d 秒\n",
                    current->patient->id, current->patient->name,
                    current->listen_time);
                current = current->next;
            }
        }
    }
}

// 根据科室ID获取索引
int get_department_index_by_id(int id) {
    return id - 1;
}

// 根据医生ID获取索引
int get_doctor_index_by_id(Department* dept, int doctor_id) {
    if (doctor_id < 1 || doctor_id > NUM_DOCTORS_PER_DEPT) {
        return -1;
    }
    return doctor_id - 1;
}

// 清除输入缓冲区
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
