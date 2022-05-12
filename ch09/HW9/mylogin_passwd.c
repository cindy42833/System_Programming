#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <sys/types.h>
#include <assert.h>
#include <wait.h>
#include <crypt.h>
#include <shadow.h>

int main(int argc, char *argv[]) {
    char username[1024], buf[1024];
    char *namePtr = NULL, *password = NULL, *crypt_passwd = NULL;
    struct passwd passwd_ent;
    struct passwd *result = NULL;
    struct spwd *pwd = NULL;
    struct group *grp = NULL;
    gid_t gid;
    gid_t groups[sysconf(_SC_NGROUPS_MAX)];
    int numGrp = sysconf(_SC_NGROUPS_MAX), ret = 0, pid;

    while(1) {
        printf("Please enter username to login: ");
        namePtr = fgets(username, 1024, stdin);   // wait to type username
        username[strlen(username) - 1] = '\0';
        printf("You enter %s\n", namePtr);
        ret = getpwnam_r(namePtr, &passwd_ent, buf, 1024, &result);     // search user data from /etc/passwd
        
        if(ret != 0) {  // error handle
            perror("Error");
        }
        else if(result == NULL) {
            fprintf(stderr, "No username match!\n");
        }
        else {
            password = getpass("Passeord: ");
            pwd = getspnam(username);
            crypt_passwd = crypt(password, pwd->sp_pwdp);
            if(strcmp(crypt_passwd, pwd->sp_pwdp) == 0) {
                    pid = fork();
                if(pid > 0) {
                    int status;
                    wait(&status);
                }
                else if(pid == 0) {
                    ret = getgrouplist(namePtr, passwd_ent.pw_gid, groups, &numGrp);
                    printf("grouplist: %d\n", ret);
                    printf("Username: %s\n", passwd_ent.pw_name);
                    printf("User uid: %d\n", passwd_ent.pw_uid);
                    printf("User groupid: %d\n", passwd_ent.pw_gid);
                    printf("User group: %d\n", numGrp);
                    struct group *ggid;
                    for(int i=0; i<numGrp; i++) {
                        ggid = getgrgid(groups[i]);
                        printf("%s, ", ggid->gr_name);
                    }
                    printf("\n");
                    printf("User home directory: %s\n", passwd_ent.pw_dir);
                    printf("User information: %s\n", passwd_ent.pw_gecos);

                    assert(setgid(passwd_ent.pw_gid) == 0);
                    assert(chdir(passwd_ent.pw_dir) == 0);
                    setenv("HOME", passwd_ent.pw_dir, 1);

                    setgroups(0, NULL);     // drop all group
                    setgroups(numGrp, groups);  // set user group id
                    assert(setuid(passwd_ent.pw_uid) == 0);
                    char *child_argv[] = {"/usr/bin/bash", NULL};
                    char *filename = "/usr/bin/bash";
                    ret = execvp(filename, child_argv);
                }
            }
            else
                printf("Authentication fail!\n");
        }
    }
    return 0;
}