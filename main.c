#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define N 5 // количество философов / стульев / вилок
#define THINK_TIME 3 // время, которое философ проводит, размышляя
#define EAT_TIME 2 // время, которое философ поглощает пищу

pthread_t philosophers[N]; // потоки для философов
sem_t forks[N]; // семафоры для вилок
sem_t chairs[N]; // семафоры для стульев
sem_t table; // семафор для стола

void *philosopher(void *arg) {
    int i = *(int*)arg; // номер философа
    int left_fork = i; // номер левой вилки
    int right_fork = (i + 1) % N; // номер правой вилки

    int i_print = i + 1, left_fork_print = left_fork + 1, right_fork_print = right_fork + 1;
    printf("Философ %d сел за стол на место %d\n", i_print, i_print);

    while (1) {
        printf("Философ %d размышляет...\n", i_print);
        sleep(THINK_TIME);

        sem_wait(&table); // философ хочет сесть за стол
        sem_wait(&forks[left_fork]); // философ берет левую вилку
        printf("Философ %d взял левую вилку %d\n", i_print, left_fork_print);
        sem_wait(&forks[right_fork]); // философ берет правую вилку
        printf("Философ %d взял правую вилку %d\n", i_print, right_fork_print);

        printf("Философ %d ест...\n", i_print);
        sleep(EAT_TIME);

        sem_post(&forks[left_fork]); // философ кладет левую вилку на стол
        printf("Философ %d кладет левую вилку %d\n", i_print, left_fork_print);
        sem_post(&forks[right_fork]); // философ кладет правую вилку на стол
        printf("Философ %d кладет правую вилку %d\n", i_print, right_fork_print);
        sem_post(&table); // философ уходит от стола
    }
}

int main() {
    srand(time(0)); // для генерации случайных чисел

    sem_init(&table, 0, N-1); // инициализация семафора для стола
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1); // инициализация семафоров для вилок
    }

    int ids[N]; // номера философов
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]); // создание потока для каждого философа
    }

    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL); // ожидание завершения работы потоков
    }

    sem_destroy(&table); // уничтожение семафора для стола
    for (int i = 0; i < N; i++) {
        sem_destroy(&forks[i]); // уничтожение семафоров для вилок
    }

    return 0;
}