#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

/* ----------------------- Structures & Utilities ----------------------- */

/* Structure representing a philosopher */
typedef struct s_philo {
    int             id;
    int             number_philos;
    int             t_die;
    int             t_eat;
    int             t_sleep;
    int             n_meals;       // -1 if not specified
    int             meals_eaten;
    unsigned long   start_time;
    unsigned long   last_meal_time;
    pthread_mutex_t *forks;        // Array of mutexes (one per fork)
    int             left_fork;
    int             right_fork;
} t_philo;

/* Error message function: prints error and returns non-zero for exit */
int error_message(const char *msg)
{
    printf("%s", msg);
    return (1);
}

/* Convert a string to an unsigned integer */
unsigned int ft_atoi(const char *str)
{
    unsigned int sign = 1;
    unsigned int result = 0;
    unsigned int next_digit;

    while (*str == ' ')
        str++;
    if ((*str == '-' || *str == '+') && *(str + 1))
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        /* A simple bound check (adjust as needed) */
        if ((result * sign) > 10000 || (result * sign) <= 0)
            return (-1);
        next_digit = *str - '0';
        result = result * 10 + next_digit;
        str++;
    }
    return (result * sign);
}

/* Check if the given argument contains only digits */
int content(char *argument)
{
    int i = 0;
    while (argument[i])
    {
        if (argument[i] < '0' || argument[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

/* Validate command-line arguments */
void args_validity(char **argv)
{
    if (ft_atoi(argv[1]) <= 0 || !content(argv[1]))
        exit(error_message("Invalid number of philosophers\n"));
    if (ft_atoi(argv[2]) <= 0 || !content(argv[2]))
        exit(error_message("Invalid time for die\n"));
    if (ft_atoi(argv[3]) <= 0 || !content(argv[3]))
        exit(error_message("Invalid time to eat\n"));
    if (ft_atoi(argv[4]) <= 0 || !content(argv[4]))
        exit(error_message("Invalid time to sleep\n"));
    if (argv[5] && (ft_atoi(argv[5]) <= 0 || !content(argv[5])))
        exit(error_message("Invalid number of times each philo must eat\n"));
}

/* Initialize philosopher parameters from arguments */
void init_philo_stuff(t_philo *philo, char **argv, int argc)
{
    philo->number_philos = ft_atoi(argv[1]);
    philo->t_die = ft_atoi(argv[2]);
    philo->t_eat = ft_atoi(argv[3]);
    philo->t_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        philo->n_meals = ft_atoi(argv[5]); // Optional argument
    else
        philo->n_meals = -1;
}

/* ----------------------- Time & Mutex Management ----------------------- */

/* Get current time in milliseconds */
unsigned long get_time_in_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/* Print a philosopher's action with a timestamp */
void print_action(t_philo *philo, const char *action)
{
    unsigned long timestamp = get_time_in_ms() - philo->start_time;
    printf("%lu %d %s\n", timestamp, philo->id, action);
}

/* Initialize mutexes for forks */
void threads_and_mutexes(t_philo *philo)
{
    int i = 0;
    philo->forks = malloc(sizeof(pthread_mutex_t) * philo->number_philos);
    if (!philo->forks)
    {
        perror("Malloc error for forks");
        exit(EXIT_FAILURE);
    }
    while (i < philo->number_philos)
    {
        pthread_mutex_init(&philo->forks[i], NULL);
        i++;
    }
}

/* ----------------------- Philosopher Routine & Thread Creation ----------------------- */

/* Routine executed by each philosopher thread */
void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1)
    {
        /* Philosopher is thinking */
        print_action(philo, "is thinking");

        /* Pick up left fork */
        pthread_mutex_lock(&philo->forks[philo->left_fork]);
        print_action(philo, "has taken a fork");

        /* Pick up right fork */
        pthread_mutex_lock(&philo->forks[philo->right_fork]);
        print_action(philo, "has taken a fork");

        /* Eating */
        print_action(philo, "is eating");
        philo->last_meal_time = get_time_in_ms();
        usleep(philo->t_eat * 1000);  // simulate eating time
        philo->meals_eaten++;

        /* Release forks after eating */
        pthread_mutex_unlock(&philo->forks[philo->left_fork]);
        pthread_mutex_unlock(&philo->forks[philo->right_fork]);

        /* Sleeping */
        print_action(philo, "is sleeping");
        usleep(philo->t_sleep * 1000);

        /* Optional: exit if the required number of meals have been eaten */
        if (philo->n_meals != -1 && philo->meals_eaten >= philo->n_meals)
            break;
    }
    return NULL;
}

/* Create philosopher threads, initialize their parameters, and join threads */
int create_threads(t_philo *philo_array)
{
    int         i;
    pthread_t   *threads;

    threads = malloc(sizeof(pthread_t) * philo_array->number_philos);
    if (!threads)
        return error_message("Memory allocation error for threads\n");

    /* Initialize start time for all philosophers (using the first philo's field) */
    unsigned long start = get_time_in_ms();
    for (i = 0; i < philo_array->number_philos; i++)
    {
        philo_array[i].start_time = start;
        philo_array[i].last_meal_time = start;
        philo_array[i].meals_eaten = 0;
        philo_array[i].id = i + 1;
        philo_array[i].left_fork = i;
        philo_array[i].right_fork = (i + 1) % philo_array->number_philos;
        if (pthread_create(&threads[i], NULL, philosopher_routine, &philo_array[i]) != 0)
            return error_message("Error creating thread\n");
    }
    for (i = 0; i < philo_array->number_philos; i++)
        pthread_join(threads[i], NULL);
    free(threads);
    return 0;
}

/* ----------------------- Main Entry Point ----------------------- */

int main(int argc, char **argv)
{
    t_philo *philo_array;
    int     num_philos;

    if (argc != 5 && argc != 6)
        return error_message("Usage: ./philo num_philo t_die t_eat t_sleep [num_meals]\n");
    args_validity(argv);
    num_philos = ft_atoi(argv[1]);
    philo_array = malloc(sizeof(t_philo) * num_philos);
    if (!philo_array)
        return error_message("Memory allocation error for philosophers\n");
    
    /* Initialize parameters (common settings are stored in the first element) */
    init_philo_stuff(&philo_array[0], argv, argc);
    threads_and_mutexes(&philo_array[0]);

    /* Create and run philosopher threads */
    create_threads(philo_array);

    /* Cleanup: Destroy mutexes and free allocated memory */
    for (int i = 0; i < philo_array[0].number_philos; i++)
        pthread_mutex_destroy(&philo_array[0].forks[i]);
    free(philo_array[0].forks);
    free(philo_array);
    return 0;
}
