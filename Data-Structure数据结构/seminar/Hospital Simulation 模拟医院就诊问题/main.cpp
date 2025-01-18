#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ��������
#define NUM_DEPARTMENTS 15
#define NUM_DOCTORS_PER_DEPT 3
#define NUM_BULTRASOUND_MACHINES 3

// ���߽ṹ��
typedef struct Patient {
    int id;
    char name[50];
    int department_id;
    int doctor_id; // -1 ��ʾδָ��ҽ��
    int needs_b_ultrasound;
    int registration_order; // �Һ�˳��
    struct Patient* next;
} Patient;

// ҽ���Ļ��߼�¼�ṹ��
typedef struct DoctorPatient {
    Patient* patient;
    int listen_time; // ����ʱ�䣬��λ��
    struct DoctorPatient* next;
} DoctorPatient;

// ҽ���ṹ��
typedef struct Doctor {
    int id;
    char name[50];
    DoctorPatient* patients_head;
    DoctorPatient* patients_tail;
} Doctor;

// ���ҽṹ��
typedef struct Department {
    int id;
    char name[50];
    // ����ָ��ҽ���Ķ���
    Patient* specified_queues_head[NUM_DOCTORS_PER_DEPT];
    Patient* specified_queues_tail[NUM_DOCTORS_PER_DEPT];
    // һ��ͨ�ö���
    Patient* general_queue_head;
    Patient* general_queue_tail;
    Doctor doctors[NUM_DOCTORS_PER_DEPT];
} Department;

// B���ҵĻ��߼�¼�ṹ��
typedef struct BUltrasoundPatient {
    Patient* patient;
    struct BUltrasoundPatient* next;
} BUltrasoundPatient;

// B���ҽṹ��
typedef struct BUltrasoundRoom {
    int id;
    BUltrasoundPatient* queue_head;
    BUltrasoundPatient* queue_tail;
} BUltrasoundRoom;

// ȫ�ֱ���
Department departments[NUM_DEPARTMENTS];
BUltrasoundRoom b_ultrasound_room;
int patient_id_counter = 1;
int registration_order_counter = 1;

// ��������
void initialize_system();
void register_patient();
void process_consultations();
void process_b_ultrasound();
void display_queues();
void view_doctors_patients();
int get_department_index_by_id(int id);
int get_doctor_index_by_id(Department* dept, int doctor_id);
void clear_input_buffer();

// ������
int main() {
    srand(time(NULL)); // �����
    int choice;
    initialize_system();
    while (1) {
        printf("\n=== ҽԺ�������ϵͳ ===\n");
        printf("1. �Һ�\n");
        printf("2. �������\n");
        printf("3. ����B�����\n");
        printf("4. ��ʾ�����Ҽ�B�����Ŷ����\n");
        printf("5. �鿴ҽ���ľ����¼\n");
        printf("6. �˳�\n");
        printf("������ѡ��: ");
        if (scanf("%d", &choice) != 1) {
            printf("������Ч�����������롣\n");
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
                printf("�˳�ϵͳ��\n");
                exit(0);
            default:
                printf("ѡ����Ч�����������롣\n");
        }
    }
    return 0;
}

// ��ʼ��ϵͳ���������ҡ�ҽ����B����
void initialize_system() {
    // ��ʼ������
    for (int i = 0; i < NUM_DEPARTMENTS; i++) {
        departments[i].id = i + 1;
        sprintf(departments[i].name, "����%d", i + 1);
        departments[i].general_queue_head = NULL;
        departments[i].general_queue_tail = NULL;
        // ��ʼ��ָ��ҽ������
        for (int j = 0; j < NUM_DOCTORS_PER_DEPT; j++) {
            departments[i].specified_queues_head[j] = NULL;
            departments[i].specified_queues_tail[j] = NULL;
        }
        // ��ʼ��ҽ��
        for (int j = 0; j < NUM_DOCTORS_PER_DEPT; j++) {
            departments[i].doctors[j].id = j + 1;
            sprintf(departments[i].doctors[j].name, "ҽ��%d-%d", i + 1, j + 1);
            departments[i].doctors[j].patients_head = NULL;
            departments[i].doctors[j].patients_tail = NULL;
        }
    }
    // ��ʼ��B����
    b_ultrasound_room.id = 1;
    b_ultrasound_room.queue_head = NULL;
    b_ultrasound_room.queue_tail = NULL;
}

// �ҺŹ���
void register_patient() {
    Patient* new_patient = (Patient*)malloc(sizeof(Patient));
    if (!new_patient) {
        printf("�ڴ����ʧ�ܡ�\n");
        return;
    }
    new_patient->id = patient_id_counter++;
    printf("�����뻼������: ");
    fgets(new_patient->name, sizeof(new_patient->name), stdin);
    new_patient->name[strcspn(new_patient->name, "\n")] = '\0'; // ȥ�����з�
    printf("��ѡ����ң�1-%d��:\n", NUM_DEPARTMENTS);
    for (int i = 0; i < NUM_DEPARTMENTS; i++) {
        printf("%d. %s\n", departments[i].id, departments[i].name);
    }
    int dept_id;
    printf("������ұ��: ");
    if (scanf("%d", &dept_id) != 1 || dept_id < 1 || dept_id > NUM_DEPARTMENTS) {
        printf("���ұ����Ч��\n");
        free(new_patient);
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    new_patient->department_id = dept_id;
    new_patient->doctor_id = -1; // Ĭ�ϲ�ָ��ҽ��
    printf("�Ƿ�ָ��ҽ������1. ��  2. ��: ");
    int specify;
    if (scanf("%d", &specify) != 1) {
        printf("������Ч��\n");
        free(new_patient);
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    if (specify == 1) {
        printf("��ѡ��ҽ��:\n");
        Department* dept = &departments[get_department_index_by_id(dept_id)];
        for (int i = 0; i < NUM_DOCTORS_PER_DEPT; i++) {
            printf("%d. %s\n", dept->doctors[i].id, dept->doctors[i].name);
        }
        int doctor_id;
        printf("����ҽ�����: ");
        if (scanf("%d", &doctor_id) != 1 || doctor_id < 1 || doctor_id > NUM_DOCTORS_PER_DEPT) {
            printf("ҽ�������Ч��\n");
            free(new_patient);
            clear_input_buffer();
            return;
        }
        clear_input_buffer();
        new_patient->doctor_id = doctor_id;
    }
    printf("�Ƿ���ҪB����飿��1. ��  2. ��: ");
    int b_ultrasound;
    if (scanf("%d", &b_ultrasound) != 1) {
        printf("������Ч��\n");
        free(new_patient);
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    new_patient->needs_b_ultrasound = (b_ultrasound == 1) ? 1 : 0;
    new_patient->registration_order = registration_order_counter++;
    new_patient->next = NULL;
    // ��ӵ���Ӧ���ҵĶ���
    Department* dept = &departments[get_department_index_by_id(dept_id)];
    if (new_patient->doctor_id != -1) {
        // ��ӵ�ָ��ҽ���Ķ���
        int doc_index = get_doctor_index_by_id(dept, new_patient->doctor_id);
        if (doc_index == -1) {
            printf("ҽ�������Ч��\n");
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
        // ��ӵ�ͨ�ö���
        if (dept->general_queue_tail == NULL) {
            dept->general_queue_head = dept->general_queue_tail = new_patient;
        }
        else {
            dept->general_queue_tail->next = new_patient;
            dept->general_queue_tail = new_patient;
        }
    }
    printf("�Һųɹ������ĹҺź�Ϊ %d��\n", new_patient->id);
}

// ����������
void process_consultations() {
    for (int i = 0; i < NUM_DEPARTMENTS; i++) {
        Department* dept = &departments[i];
        // �ҵ���ǰ�����ĸ������йҺ�˳������Ļ���
        Patient* earliest_patient = NULL;
        int earliest_queue = -1; // 0-2: ָ��ҽ�����У�3: ͨ�ö���
        for (int j = 0; j < NUM_DOCTORS_PER_DEPT; j++) {
            if (dept->specified_queues_head[j] != NULL) {
                if (earliest_patient == NULL || dept->specified_queues_head[j]->registration_order < earliest_patient->registration_order) {
                    earliest_patient = dept->specified_queues_head[j];
                    earliest_queue = j;
                }
            }
        }
        // ���ͨ�ö���
        if (dept->general_queue_head != NULL) {
            if (earliest_patient == NULL || dept->general_queue_head->registration_order < earliest_patient->registration_order) {
                earliest_patient = dept->general_queue_head;
                earliest_queue = NUM_DOCTORS_PER_DEPT; // ͨ�ö��б��
            }
        }
        if (earliest_patient != NULL) {
            if (earliest_queue < NUM_DOCTORS_PER_DEPT) {
                // ָ��ҽ������
                int doc_index = earliest_queue;
                // �Ƴ�����
                dept->specified_queues_head[doc_index] = dept->specified_queues_head[doc_index]->next;
                if (dept->specified_queues_head[doc_index] == NULL) {
                    dept->specified_queues_tail[doc_index] = NULL;
                }
                // ��¼��ҽ���Ļ����б�
                Doctor* doc = &dept->doctors[doc_index];
                DoctorPatient* doc_patient = (DoctorPatient*)malloc(sizeof(DoctorPatient));
                if (!doc_patient) {
                    printf("�ڴ����ʧ�ܡ�\n");
                    return;
                }
                doc_patient->patient = earliest_patient;
                // ģ������ʱ��Ϊ5-15��
                doc_patient->listen_time = 5 + rand() % 11;
                doc_patient->next = NULL;
                if (doc->patients_tail == NULL) {
                    doc->patients_head = doc->patients_tail = doc_patient;
                }
                else {
                    doc->patients_tail->next = doc_patient;
                    doc->patients_tail = doc_patient;
                }
                printf("����%s��%s�����˻���%s��ID: %d��������ʱ��: %d �롣\n",
                    dept->name, doc->name, earliest_patient->name, earliest_patient->id, doc_patient->listen_time);
                // �����ҪB������ӵ�B���Ҷ���
                if (earliest_patient->needs_b_ultrasound) {
                    BUltrasoundPatient* bu_patient = (BUltrasoundPatient*)malloc(sizeof(BUltrasoundPatient));
                    if (!bu_patient) {
                        printf("�ڴ����ʧ�ܡ�\n");
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
                    printf("����%s��ID: %d���ѱ���ӵ�B���Ҷ��С�\n", earliest_patient->name, earliest_patient->id);
                }
            }
            else {
                // ҽ���ǲ���ȫ������ѽ��һֱ�ɻ����Ҫ������Ϣ��ʱ�䣿
                // ������谴ҽ�����˳�����
                int assigned = 0;
                for (int j = 0; j < NUM_DOCTORS_PER_DEPT; j++) {
                    Doctor* doc = &dept->doctors[j];
                    // ��ҽ���Ƿ���æµ���������һֱ�ɻ�Ҫ���⿼�ǣ������Ϊʼ�տ��ã�����ֱ�ӷ���
                    // �Ƴ�����
                    Patient* patient = dept->general_queue_head;
                    dept->general_queue_head = dept->general_queue_head->next;
                    if (dept->general_queue_head == NULL) {
                        dept->general_queue_tail = NULL;
                    }
                    // ��¼��ҽ���Ļ����б�
                    DoctorPatient* doc_patient = (DoctorPatient*)malloc(sizeof(DoctorPatient));
                    if (!doc_patient) {
                        printf("�ڴ����ʧ�ܡ�\n");
                        return;
                    }
                    doc_patient->patient = patient;
                    // ģ������ʱ��Ϊ5-15��
                    doc_patient->listen_time = 5 + rand() % 11;
                    doc_patient->next = NULL;
                    if (doc->patients_tail == NULL) {
                        doc->patients_head = doc->patients_tail = doc_patient;
                    }
                    else {
                        doc->patients_tail->next = doc_patient;
                        doc->patients_tail = doc_patient;
                    }
                    printf("����%s��%s�����˻���%s��ID: %d��������ʱ��: %d �롣\n",
                        dept->name, doc->name, patient->name, patient->id, doc_patient->listen_time);
                    // �����ҪB������ӵ�B���Ҷ���
                    if (patient->needs_b_ultrasound) {
                        BUltrasoundPatient* bu_patient = (BUltrasoundPatient*)malloc(sizeof(BUltrasoundPatient));
                        if (!bu_patient) {
                            printf("�ڴ����ʧ�ܡ�\n");
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
                        printf("����%s��ID: %d���ѱ���ӵ�B���Ҷ��С�\n", patient->name, patient->id);
                    }
                    assigned = 1;
                    break; // ֻ�����һ��ҽ��
                }
                if (!assigned) {
                    printf("����%s������ҽ������æµ���޷����ﻼ��%s��ID: %d����\n",
                        dept->name, earliest_patient->name, earliest_patient->id);
                }
            }
        }
    }
}

// ����B��������
void process_b_ultrasound() {
    for (int i = 0; i < NUM_BULTRASOUND_MACHINES; i++) {
        if (b_ultrasound_room.queue_head != NULL) {
            BUltrasoundPatient* bu_patient = b_ultrasound_room.queue_head;
            b_ultrasound_room.queue_head = b_ultrasound_room.queue_head->next;
            if (b_ultrasound_room.queue_head == NULL) {
                b_ultrasound_room.queue_tail = NULL;
            }
            printf("B����%d���ڴ�����%s��ID: %d����\n", i + 1,
                bu_patient->patient->name, bu_patient->patient->id);
            free(bu_patient);
        }
    }
    printf("B��������ɡ�\n");
}

// ��ʾ�����Ҽ�B���ҵ��Ŷ����
void display_queues() {
    printf("\n=== �������Ŷ���� ===\n");
    for (int i = 0; i < NUM_DEPARTMENTS; i++) {
        Department* dept = &departments[i];
        printf("����%s��ID: %d������:\n", dept->name, dept->id);
        // ��ʾָ��ҽ������
        for (int j = 0; j < NUM_DOCTORS_PER_DEPT; j++) {
            printf("  %s����:\n", dept->doctors[j].name);
            if (dept->specified_queues_head[j] == NULL) {
                printf("    �޻����Ŷӡ�\n");
            }
            else {
                Patient* current = dept->specified_queues_head[j];
                while (current != NULL) {
                    printf("    ����ID: %d, ����: %s, ��ҪB��: %s, �Һ�˳��: %d\n",
                        current->id, current->name,
                        current->needs_b_ultrasound ? "��" : "��",
                        current->registration_order);
                    current = current->next;
                }
            }
        }
        // ��ʾͨ�ö���
        printf("  ͨ�ö���:\n");
        if (dept->general_queue_head == NULL) {
            printf("    �޻����Ŷӡ�\n");
        }
        else {
            Patient* current = dept->general_queue_head;
            while (current != NULL) {
                printf("    ����ID: %d, ����: %s, ��ҪB��: %s, �Һ�˳��: %d\n",
                    current->id, current->name,
                    current->needs_b_ultrasound ? "��" : "��",
                    current->registration_order);
                current = current->next;
            }
        }
    }
    // ��ʾB���Ҷ���
    printf("\n=== B���Ҷ��� ===\n");
    if (b_ultrasound_room.queue_head == NULL) {
        printf("  �޻����Ŷӡ�\n");
    }
    else {
        BUltrasoundPatient* current = b_ultrasound_room.queue_head;
        while (current != NULL) {
            printf("  ����ID: %d, ����: %s\n",
                current->patient->id, current->patient->name);
            current = current->next;
        }
    }
}

// �鿴ҽ���ľ����¼
void view_doctors_patients() {
    printf("\n��ѡ����ң�1-%d��: ", NUM_DEPARTMENTS);
    int dept_id;
    if (scanf("%d", &dept_id) != 1 || dept_id < 1 || dept_id > NUM_DEPARTMENTS) {
        printf("���ұ����Ч��\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    Department* dept = &departments[get_department_index_by_id(dept_id)];
    printf("����%s��ҽ����������¼:\n", dept->name);
    for (int i = 0; i < NUM_DOCTORS_PER_DEPT; i++) {
        Doctor* doc = &dept->doctors[i];
        printf("ҽ��%s��ID: %d������Ļ���:\n", doc->name, doc->id);
        if (doc->patients_head == NULL) {
            printf("  �޻��߼�¼��\n");
        }
        else {
            DoctorPatient* current = doc->patients_head;
            while (current != NULL) {
                printf("  ����ID: %d, ����: %s, ����ʱ��: %d ��\n",
                    current->patient->id, current->patient->name,
                    current->listen_time);
                current = current->next;
            }
        }
    }
}

// ���ݿ���ID��ȡ����
int get_department_index_by_id(int id) {
    return id - 1;
}

// ����ҽ��ID��ȡ����
int get_doctor_index_by_id(Department* dept, int doctor_id) {
    if (doctor_id < 1 || doctor_id > NUM_DOCTORS_PER_DEPT) {
        return -1;
    }
    return doctor_id - 1;
}

// ������뻺����
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
