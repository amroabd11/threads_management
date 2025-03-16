#include "philo.h"

int error_message(char *msg)
{
    write(2, msg, ft_strlen(msg));
    return (1);//TODO ft_strlen
}