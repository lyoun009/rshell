//this main will be used to implement fork, waitpid and execvp
int main() 
{
    pid_t parent = getpid();
    pid_t pid = fork();

    if (pid == -1)
{

    } 
    else if (pid > 0){
        int status;
        waitpid(pid, &status, 0);
    }
    else {
        execvp(...);
        _exit(0);   
    }
}
